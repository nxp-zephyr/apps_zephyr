/*
 * Copyright 2024, NXP
 * Copyright (c) 2019 Linaro Limited, for sample:
 *    https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/subsys/video/capture/src/main.c
 *
 * Copyright (c) 2019 Jan Van Winkel <jan.van_winkel@dxplore.eu>, for sample:
 *    https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/drivers/display/src/main.c
 *
 * Based on ST7789V sample:
 *    Copyright (c) 2019 Marc Reilly
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Application Overview:
 * The main thread runs in a loop, dequeuing buffers from the video driver,
 * formatting and writing to the display, then resizing and sending to the
 * inference model for object detection.  If detected, the model returns
 * coordinates of the object, and rectangles are drawn for the display.
 * Inferencing is done in a separate thread, giving priority to updating the
 * display.
 * 
 * on MCX N947:
 * This SOC provides some challenge due to the limited RAM available.  The
 * LCD-PAR-S035 display is oriented in portrait mode to align with the camera.
 * To conserve RAM, the camera frame is shown on the upper half of the display,
 * at 320 x 240.  The lower half displays text, and is only updated with new
 * inference results.
 * 
 * To conserve RAM, the video driver buffers are partial slices of the full frame.
 * This reduces the buffer size required.  The video driver reports the number
 * of slices in a frame in caps.vbuf_per_frame.  And each buffer dequeued
 * provides frame_idx for that slice.  The LCD-PAR-S035 module is a smart
 * display, and partial frames can be written directly to the display.  Then
 * the slice buffer is copied to the input buffer for the model and converted to
 * RGB888.  That input is also resized for the model.  The rectangles are also
 * drawn on the slices, using the same video slice buffers before they are
 * written to the display.  To provide a cleaner look, the rectangle locations
 * are only changed at the start of a new frame.  And the previous rectangles
 * are "erased" completely before drawing new rectangles.
 * 
 * on RT1060:
 * This platform is easier with a large SDRAM, and plenty of room for buffers.
 * The video driver provides full frame buffers.  These are converted using the
 * PXP to flip the image horizontally, like looking in a mirror.  On this display,
 * the text is displayed in a banner at the bottom of the display, and the results
 * are updated from the inference.  The bottom of the full video buffer is
 * excluded when writing to the display, since the banner is drawn there.  After
 * writing to the display, the same buffer is passed to the inference thread. A
 * queue is used when passing this buffer.  The inference thread will get the
 * most recent buffer in that queue, and return any other buffers in that queue
 * to the video driver.  Rectangles are easier on this platform since the video
 * and display driver use a full frame.  If detected, the full rectangles are
 * drawn on each frame, and location updated after a new inference result.
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <zephyr/kernel.h>
#include "FacialDetect.h"

#ifdef CONFIG_LOG
#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app, CONFIG_APP_LOG_LEVEL);
#endif /* CONFIG_LOG */

struct display_buffer_descriptor strbuf_desc;

#include <zephyr/drivers/display.h>
#include <zephyr/drivers/video.h>
#include "display_app.h"
#include "convert.h"

const struct device *display_dev;

volatile static uint32_t __attribute((aligned(4))) vbuf_idx = 0;

#include "model.h"

K_THREAD_STACK_DEFINE(inf_thread_stack_area, THREAD_INF_STACKSIZE);
static struct k_thread inf_thread_data;

struct k_fifo inf_fifo;  /* FIFO for buffers to inference */

int main(void)
{
	printk("Zephyr Facial Detection Demo\r\n");
	printk("Model: %s\r\n", MODEL_GetModelName());

	struct video_buffer *buffers[CONFIG_VIDEO_BUFFER_POOL_NUM_MAX], *vbuf;
	struct display_buffer_descriptor buf_desc;
	void *convdisp_buf = NULL;
	rect_buf_params_t rect_params;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return -1;
	}

	if (convdisp_init(DT_PROP(DT_CHOSEN(zephyr_display), width),
		DT_PROP(DT_CHOSEN(zephyr_display), height))) {
		LOG_ERR("convdisp_init() failed\n");
		return -1;
	}

	const struct device *const video = DEVICE_DT_GET(DT_CHOSEN(zephyr_camera));

	if (!device_is_ready(video)) {
		LOG_ERR("%s: device not ready.\n", video->name);
		return -1;
	}

	int i = 0;
	unsigned int frame = 0;

	LOG_DBG("- Device name: %s\n", video->name);

	/* Get capabilities */
	struct video_caps caps;
	if (video_get_caps(video, VIDEO_EP_OUT, &caps)) {
		LOG_ERR("Unable to retrieve video capabilities");
		return -1;
	}

	LOG_DBG("- Capabilities:\n");
	while (caps.format_caps[i].pixelformat) {
		const struct video_format_cap *fcap = &caps.format_caps[i];
		/* fourcc to string */
		LOG_DBG("  %c%c%c%c width [%u; %u; %u] height [%u; %u; %u]\n",
		       (char)fcap->pixelformat,
		       (char)(fcap->pixelformat >> 8),
		       (char)(fcap->pixelformat >> 16),
		       (char)(fcap->pixelformat >> 24),
		       fcap->width_min, fcap->width_max, fcap->width_step,
		       fcap->height_min, fcap->height_max, fcap->height_step);
		i++;
	}

	/* Get default/native format */
	struct video_format fmt;
	if (video_get_format(video, VIDEO_EP_OUT, &fmt)) {
		LOG_ERR("Unable to retrieve video format");
		return -1;
	}

	LOG_DBG("- Default format: %c%c%c%c %ux%u\n", (char)fmt.pixelformat,
	       (char)(fmt.pixelformat >> 8),
	       (char)(fmt.pixelformat >> 16),
	       (char)(fmt.pixelformat >> 24),
	       fmt.width, fmt.height);

	/* Size to allocate for each buffer */
	size_t bsize;
	bsize = fmt.pitch * fmt.height / caps.vbuf_per_frame;

	/* Alloc video buffers and enqueue for capture */
	for (i = 0; i < ARRAY_SIZE(buffers); i++) {
		buffers[i] = video_buffer_alloc(bsize);
		if (buffers[i] == NULL) {
			LOG_ERR("Unable to alloc video buffer");
			return -1;
		}

		video_enqueue(video, VIDEO_EP_OUT, buffers[i]);
	}

	/* configure display buffer */
	uint16_t y_step;

	y_step = fmt.height / caps.vbuf_per_frame;
	buf_desc.buf_size = bsize;
	buf_desc.width = fmt.width;
	buf_desc.pitch = fmt.width;
	buf_desc.height = y_step;
	#ifdef CONFIG_APP_DISPLAY_BANNER
		buf_desc.height -= BANNER_HEIGHT;
	#endif

	/* use a video buffer to initially draw the display brackground */
	display_background(buffers[0]->buffer);

	/* Start video capture */
	if (video_stream_start(video)) {
		LOG_ERR("Unable to start capture (interface)");
		return -1;
	}

	LOG_DBG("Capture started\n");

	/* Create inference thread */
	inf_thread_config_t inf_config;

	inf_config.frameWidth = fmt.width;
	inf_config.fullFrameHeight = fmt.height;
	inf_config.singleFrameHeight = buf_desc.height;

	k_fifo_init(&inf_fifo);

	k_thread_create(&inf_thread_data, inf_thread_stack_area,
		K_THREAD_STACK_SIZEOF(inf_thread_stack_area),
		inference_thread, &inf_config, &inf_fifo, NULL,
		THREAD_PRIORITY_INF, 0, K_FOREVER);
	k_thread_name_set(&inf_thread_data, "inference_thread");

	uint8_t inf_frame_count = 0;
	bool inference_enabled = false;

	inf_results_t infResults;
	inf_results_t *frame_infResults;
	if (caps.vbuf_per_frame > 1U) {
		/* Inference results are synced at the start of each full video
		 * frame, to keep rectangles consistent in that frame.  Display
		 * will use the local copy of the results. */
		frame_infResults = &infResults;
	} else {
		/* When video provides full frame, display can use the global
		 * inference results, and avoid copying the results every frame */
		frame_infResults = &g_InfResults;
	}

	rect_params.width = buf_desc.width;
	rect_params.height = buf_desc.height;
	rect_params.slices_per_frame = caps.vbuf_per_frame;

	while (1) {
		int err;

		/* Grab video frames */
		err = video_dequeue(video, VIDEO_EP_OUT, &vbuf, K_FOREVER);
		if (err) {
			LOG_ERR("Unable to dequeue video buf");
			return -1;
		}

		LOG_DBG("\rGot frame %u! size: %u; timestamp %u ms",
		       frame++, vbuf->bytesused, vbuf->timestamp);

		convdisp(vbuf->buffer, (uint8_t **) &convdisp_buf,
			vbuf->bytesused, K_FOREVER);

		if(caps.vbuf_per_frame > 1) {
			if(vbuf->frame_idx == 0) {
				sync_slice_rectangles(frame_infResults);
			}
		#if DT_HAS_CHOSEN(zephyr_modelbuf)
			copy_slice_to_model_input(vbuf->frame_idx,
				(uint32_t) convdisp_buf, fmt.width, y_step,
				caps.vbuf_per_frame);
		#endif /* #if DT_HAS_CHOSEN(zephyr_modelbuf) */
		}

		rect_params.buf = (uint16_t *) convdisp_buf;
		rect_params.frame_idx = vbuf->frame_idx;
		display_rectangles(&rect_params, frame_infResults);

		/* Write the video buffer out to the display */
		display_write(display_dev, 0, y_step * vbuf->frame_idx, &buf_desc, convdisp_buf);

		if(inference_enabled) {
			/* wake inf_thread if it is waiting for buffer */
			k_fifo_alloc_put(&inf_fifo, convdisp_buf);
		} else {
			if(inf_frame_count >= caps.vbuf_per_frame) {
				/* wait for first full frame before starting
				 * inference thread */
				k_fifo_alloc_put(&inf_fifo, convdisp_buf);
				k_thread_start(&inf_thread_data);
				inference_enabled = true;
			} else {
				inf_frame_count++;
				/* free buffer for next conversion */
				convdisp_enqueue(convdisp_buf);
			}
		}

		/* vbuf already used, re-use this buffer to write results to
		 * display, before giving back to video driver. */
		display_results((uint16_t *)vbuf->buffer);

		err = video_enqueue(video, VIDEO_EP_OUT, vbuf);
		if (err) {
			LOG_ERR("Unable to requeue video buf");
			return -1;
		}
	}
}
