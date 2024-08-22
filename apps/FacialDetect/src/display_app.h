/*
 * Copyright 2024, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#define CHAR_SIZE 32 /* Font size for characters drawn on display */

#ifdef CONFIG_APP_DISPLAY_BANNER
	#define BANNER_WIDTH DT_PROP(DT_CHOSEN(zephyr_display), width)
	#define BANNER_HEIGHT CHAR_SIZE
	#define BANNER_SIZE BANNER_WIDTH * BANNER_HEIGHT
	#define BANNER_X 0U
	#define BANNER_Y DT_PROP(DT_CHOSEN(zephyr_display), height) - CHAR_SIZE
#endif

typedef struct
{
	uint16_t * buf;
	uint8_t frame_idx;
	uint8_t slices_per_frame;
	int width;
	int height;
} rect_buf_params_t;

/* Struct for text strings drawn on display */
struct disp_string_t {
	uint8_t * str;
	uint16_t width;		/* Width of string in characters. 0 means use sizeof() */
	uint16_t height;	/* Height of buffer */
	uint16_t x;		/* x coordinate in buffer to draw string */
	uint16_t y;		/* y coordinate in buffer to draw string */
};

int display_background(const void *disp_buf);
void draw_string(struct disp_string_t * dstr, uint16_t *str_buf,
	struct display_buffer_descriptor * desc);
void display_results(uint16_t *buf);
void display_rectangles(rect_buf_params_t *rect, inf_results_t *infResults);

extern struct display_buffer_descriptor strbuf_desc;
