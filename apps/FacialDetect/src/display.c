/*
 * Copyright (c) 2019 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 * Copyright 2024, NXP
 *
 * Based on ST7789V sample:
 * Copyright (c) 2019 Marc Reilly
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(sample, LOG_LEVEL_INF);

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include "FacialDetect.h"
#include "display_app.h"

#include "ASCII_consolas_3618.h"
uint16_t POINT_COLOR = 0x0 << 11;
uint16_t BACK_COLOR  = 0xFFFFU;
#define  BACK_COLOR8   0xFFU
#define  RECT_COLOR32  0xFFFFFFFFU;

__attribute__ ((aligned (32))) uint16_t g_char_buf[CHAR_SIZE][CHAR_SIZE/2] = {0};
enum corner {
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT
};

typedef struct{
	uint16_t x_start;
	uint16_t y_start;
	uint16_t x_end;
	uint16_t y_end;
} area_lcd_t;

typedef void (*fill_buffer)(enum corner corner, uint8_t grey, uint8_t *buf,
			    size_t buf_size);

static struct display_buffer_descriptor buf_desc;
const uint8_t *buffer_slice;
static uint64_t s_prevTimeStamp = 0;
static int s_RetCntPrev = 0xFFFFFFFF;
static uint32_t s_prevInfUs = 0;

#ifdef CONFIG_APP_DISPLAY_BANNER
	static uint16_t banner_buf[BANNER_SIZE];
#endif

/* Declare const strings to draw on display */
#ifdef CONFIG_BOARD_FRDM_MCXN947
	const uint8_t mcxn9[] = "  MCXN94x  ";
	const struct disp_string_t str_mcxn9 = {
		.str = (uint8_t *) mcxn9,
		.width = 0,
		.height = CHAR_SIZE,
		.x = 80U,
		.y = 250U,
	};

	const uint8_t aidemo[] = "Face Detect";
	const struct disp_string_t str_aidemo = {
		.str = (uint8_t *) aidemo,
		.width = 0,
		.height = CHAR_SIZE,
		.x = 80U,
		.y = 280U,
	};

	const uint8_t npu[] = "NPU:";
	const struct disp_string_t str_npu = {
		.str = (uint8_t *) npu,
		.width = 0,
		.height = CHAR_SIZE,
		.x = 32U,
		.y = 360U,
	};

	struct disp_string_t str_results = {
		.width = 11U,
		.height = CHAR_SIZE,
		.x = 96U,
		.y = 360U,
	};
#elif ((defined CONFIG_BOARD_MIMXRT1060_EVKB) || (defined CONFIG_BOARD_MIMXRT1060_EVK))
	const uint8_t rt1060[] = "RT1060 FaceDct CM7:";
	const struct disp_string_t str_rt1060 = {
		.str = (uint8_t *) rt1060,
		.width = 0,
		.height = CHAR_SIZE,
		.x = 0U,
		.y = 272U - CHAR_SIZE,
	};

	struct disp_string_t str_results = {
		.width = 11U,
		.height = CHAR_SIZE,
		.x = 304U,
		.y = 272U - CHAR_SIZE,
	};
#else
	#error display strings not support for this board
#endif /* CONFIG_BOARD_FRDM_MCXN947 */

int display_background(const void *disp_buf)
{
#ifdef CONFIG_APP_DISPLAY_BANNER
	/* Fill the buffer with background pixels */
	(void)memset(banner_buf, BACK_COLOR8, sizeof(banner_buf));

	/* Display the banner string */
	draw_string((struct disp_string_t *) &str_rt1060, banner_buf, 
			&strbuf_desc);
	display_write(display_dev, BANNER_X, BANNER_Y, &strbuf_desc, banner_buf);

#else /* CONFIG_APP_DISPLAY_BANNER=n */
	/* Before starting video driver, use video buffers to write strings to
	 * display. */
	display_blanking_off(display_dev);

	size_t buf_size;
	struct display_capabilities capabilities;

	display_get_capabilities(display_dev, &capabilities);

	buf_size = capabilities.x_resolution;

	switch (capabilities.current_pixel_format) {
	case PIXEL_FORMAT_ARGB_8888:
		buf_size *= 4;
		break;
	case PIXEL_FORMAT_RGB_888:
		buf_size *= 3;
		break;
	case PIXEL_FORMAT_RGB_565:
		buf_size *= 2;
		break;
	case PIXEL_FORMAT_BGR_565:
		buf_size *= 2;
		break;
	case PIXEL_FORMAT_MONO01:
	case PIXEL_FORMAT_MONO10:
		buf_size /= 8;
		break;
	default:
		LOG_ERR("Unsupported pixel format. Aborting sample.");
		return 0;
	}

	/* Fill the buffer with background pixels */
	(void)memset((void *) disp_buf, BACK_COLOR8, buf_size);

	buf_desc.buf_size = buf_size;
	buf_desc.pitch = capabilities.x_resolution;
	buf_desc.width = capabilities.x_resolution;
	buf_desc.height = 1;

	/* Write the buffer to the entire display */
	for (int idx = 0; idx < capabilities.y_resolution; idx++) {
		display_write(display_dev, 0, idx, &buf_desc, disp_buf);
	}
	display_blanking_off(display_dev);

	draw_string((struct disp_string_t *) &str_mcxn9,
			(uint16_t *) disp_buf, &strbuf_desc);
	display_write(display_dev, str_mcxn9.x, str_mcxn9.y, &strbuf_desc,
			disp_buf);

	draw_string((struct disp_string_t *) &str_aidemo,
			(uint16_t *) disp_buf, &strbuf_desc);
	display_write(display_dev, str_aidemo.x, str_aidemo.y, &strbuf_desc,
			disp_buf);

	draw_string((struct disp_string_t *) &str_npu,
			(uint16_t *) disp_buf, &strbuf_desc);
	display_write(display_dev, str_npu.x, str_npu.y, &strbuf_desc,
			disp_buf);

	display_blanking_off(display_dev);
#endif /* CONFIG_APP_DISPLAY_BANNER */

	return 1;
}

void display_font_conversion(uint16_t *buf, uint16_t width, uint8_t num,
				uint8_t size, uint8_t mode) {
	uint16_t *pDst;
	uint8_t temp,t1,t,buf_x, buf_y;
	uint8_t csize=(size/8+((size%8)?1:0));

	num -= 32;
	buf_x = 0;
	buf_y = 0;

	for (uint32_t i=0;i<size/2;i++) {
		for (t = 0; t < csize; t++) {
			temp = asc2_2412[num][csize*i + t];
			for (t1 = 0; t1 < 8; t1++) {
				pDst = buf + buf_y * width + buf_x;
				if (temp & 0x80U) {
					*pDst = POINT_COLOR;
				} else if (mode == 0) {
					*pDst = BACK_COLOR;
				}

				temp <<= 1;
				buf_y++;
			}
		}

		buf_y = 0;
		buf_x++;
	}
}

void draw_string(struct disp_string_t * dstr, uint16_t *str_buf,
	struct display_buffer_descriptor * desc)
{
	uint16_t x = 0, y = 0;
	uint16_t *pDst;
	uint8_t *p = dstr->str;
	uint16_t width;
	uint8_t size = CHAR_SIZE;

	if(dstr->width) {
		width = dstr->width * CHAR_SIZE/2;
	} else {
		/* use size of string to calculate width */
		width = strlen(dstr->str) * CHAR_SIZE/2;
	}

	while((*p<='~')&&(*p>=' '))
	{
		if (x >= width) {
			x = 0;
			y += size;
		}
		if (y > dstr->height)
			break;

		pDst = str_buf + y * width + x;
		display_font_conversion(pDst, width, *p, size, 0);

		x += size/2;
		p++;
	}

	/* Config buffer descriptor */
	desc->width = width;
	desc->pitch = width;
	desc->height = dstr->height;
	desc->buf_size = desc->pitch * desc->height;
}

void draw_line(uint16_t x_start, uint16_t y_start, uint8_t size,  uint8_t dir) {
   
	uint8_t *data[size * 5 * 2];
	uint32_t data_len = 0;
	
	(void)memset(data, BACK_COLOR8, size * 5 * 2);

	if (dir == 0) {
		data_len = size * 5 * 2;
		buf_desc.buf_size = data_len;
		buf_desc.pitch = size;
		buf_desc.width = size;
		buf_desc.height = 5;

		display_write(display_dev, x_start, y_start, &buf_desc, data);
	} else if (dir == 1) {
		data_len = size * 5 * 2;
		buf_desc.buf_size = data_len;
		buf_desc.pitch = 5;
		buf_desc.width = 5;
		buf_desc.height = size;

		display_write(display_dev, x_start, y_start, &buf_desc, data);
	}

	display_blanking_off(display_dev);
}

void draw_rectangle(uint8_t x_start, uint8_t y_start, uint8_t height, uint8_t width ){

	draw_line(x_start , y_start, width,  0);
	draw_line(x_start , y_start, height ,  1);
	
	draw_line(x_start, y_start + height , width,  0);
	draw_line(x_start + width , y_start, height,  1);
}

void display_results(uint16_t *buf) {
	if(g_InfResults.retsTimeStamp != s_prevTimeStamp) {
		s_prevTimeStamp = g_InfResults.retsTimeStamp;

		/* Print inference results on display if updated*/
		if ((g_InfResults.odRetCnt != s_RetCntPrev) ||
				(g_InfResults.infUs != s_prevInfUs)) {
			str_results.str = (uint8_t *) GetBriefString(&g_InfResults);
			if (str_results.str) {
			#ifdef CONFIG_APP_DISPLAY_BANNER

				draw_string((struct disp_string_t *) &str_results,
					banner_buf, &strbuf_desc);
				display_write(display_dev, str_results.x,
					str_results.y, &strbuf_desc, banner_buf);
			#else /* CONFIG_APP_DISPLAY_BANNER=n */
				draw_string((struct disp_string_t *) &str_results,
					(uint16_t *) buf, &strbuf_desc);
				display_write(display_dev, str_results.x,
					str_results.y, &strbuf_desc, buf);

				display_blanking_off(display_dev);
			#endif /* CONFIG_APP_DISPLAY_BANNER */
			}
		}
	}
}

void draw_rect_on_slice_buffer(uint16_t* pCam, int srcW, int curY, 
	ODResult_t *pODRet, int retCnt, int slice_height) {

	int i = 0;
	int bri;

	for (i = 0; i < retCnt; i++, pODRet++) {
		bri = (int)((pODRet->score - 0.62f) * 100.0f);
		if (bri < 0)
			bri = 0;
		if (bri > 31)
			bri = 31;

		uint32_t color16 = bri | (bri*2<<5) | bri<<11;
		uint32_t color = color16 | color16<<16;
		color = RECT_COLOR32;
		uint16_t *pHorLine = 0;
		int stripeY1 = pODRet->y1 - curY;

		if (stripeY1 >= 0 && stripeY1 < slice_height) {
			for (int j = 0; j<4 && stripeY1 + j < slice_height; j++) {
				pHorLine = pCam + srcW * (j + stripeY1) + pODRet->x1;
				memset(pHorLine, color, (pODRet->x2 - pODRet->x1) * 2);
			}
		}

		int stripeY2 = pODRet->y2 - curY;
		if (stripeY2 >=0 && stripeY2 < slice_height) {
			for (int j = 0; j<4 && stripeY2 + j < slice_height; j++) {
				pHorLine = pCam + srcW * (j + stripeY2) + pODRet->x1;
				memset(pHorLine, color, (pODRet->x2 - pODRet->x1) * 2);
			}
		}

		uint16_t *pVtcLineL = pCam + pODRet->x1;
		uint16_t *pVtcLineR = pCam + pODRet->x2;

		for (int y=curY; y < curY + slice_height; y++) {
			if (y > pODRet->y1 && y < pODRet->y2) {
				memset(pVtcLineL, color, 8);
				memset(pVtcLineR, color, 8);
			}
			pVtcLineL += srcW;
			pVtcLineR += srcW;
		}
	}
}

void display_rectangles(rect_buf_params_t *rect, inf_results_t *infResults) {
	if (rect->slices_per_frame > 1U) {
		/* drawing on a slice, not the full frame */
		draw_rect_on_slice_buffer(rect->buf, rect->width,
			rect->frame_idx * rect->height, (ODResult_t *) infResults->odRets,
			infResults->odRetCnt, rect->height);
	} else {
		/* draw on the full frame */
		for (int i = 0; i < infResults->odRetCnt; i++) {
			ODResult_t* r = &infResults->odRets[i];
			IMAGE_DrawRect(rect->buf, r->x1, r->y1, (r->x2 - r->x1),
				(r->y2 - r->y1), 255, 255, 255, rect->width);
		}
	}
}
