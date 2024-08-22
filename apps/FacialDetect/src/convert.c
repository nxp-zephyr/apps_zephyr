/*
 * Copyright 2024, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "FacialDetect.h"
#include <zephyr/kernel.h>
#include "convert.h"

#ifdef CONFIG_APP_CONVERT_DISPLAY

K_HEAP_DEFINE(convdisp_buf_pool,
	((CONFIG_CONVDISP_BUF_POOL_SZ_MAX + 8U) *
	CONFIG_CONVDISP_BUF_POOL_NUM_MAX) + 128U);

static struct k_fifo convdisp_fifo_in;  /* free buffers for conversion */

#ifdef CONFIG_APP_USE_PXP
	#include <zephyr/drivers/dma.h>
	#include <zephyr/drivers/dma/dma_mcux_pxp.h>
	#include <zephyr/device.h>
	#include <zephyr/devicetree.h>
	#include <zephyr/dt-bindings/display/panel.h>
#ifdef CONFIG_HAS_MCUX_CACHE
	#include <fsl_cache.h>
#endif
	const struct device *pxp_dev;
	static struct dma_config pxp_dma = {0};
	static struct dma_block_config pxp_block = {0};
	static struct k_sem pxp_done;

	static void conv_pxp_callback(const struct device *dma_dev,
				void *user_data, uint32_t channel, int ret)
	{
		struct k_sem *pxp_done_sem = user_data;

		k_sem_give(pxp_done_sem);
	}
#endif /* CONFIG_APP_USE_PXP */

int convdisp_init(uint16_t panelWidth, uint16_t panelHeight) {
	uint8_t i;
	void *buf;

	/* Initialize the conversion FIFOs */
	k_fifo_init(&convdisp_fifo_in);

	for(i=0; i<CONFIG_CONVDISP_BUF_POOL_NUM_MAX; i++) {
		buf = k_heap_alloc(&convdisp_buf_pool,
			CONFIG_CONVDISP_BUF_POOL_SZ_MAX, K_FOREVER);

		if (buf == NULL) {
			return -ENOMEM;
		}

		k_fifo_alloc_put(&convdisp_fifo_in, buf);
	}

#ifdef CONFIG_APP_USE_PXP
	pxp_dev = DEVICE_DT_GET(DT_NODELABEL(pxp));

	k_sem_init(&pxp_done, 0, 1);
	if (!device_is_ready(pxp_dev)) {
		return -ENODEV;
	}

	/* DMA slot sets pixel format and rotation/flip command */
	uint8_t pixel_bytes;
	switch(DT_PROP(DT_CHOSEN(zephyr_display), pixel_format)) {
		case PANEL_PIXEL_FORMAT_BGR_565:
			pxp_dma.dma_slot = DMA_MCUX_PXP_FMT(DMA_MCUX_PXP_FMT_RGB565);
			pixel_bytes = 2;
			break;

		case PANEL_PIXEL_FORMAT_RGB_888:
			pxp_dma.dma_slot = DMA_MCUX_PXP_FMT(DMA_MCUX_PXP_FMT_RGB888);
			pixel_bytes = 4;
			break;

		default:
			/* Does not support */
			return -ENOTSUP;
	}

#ifdef CONFIG_APP_PXP_FLIP_HORIZONTAL
	/* Configure PXP to flip camera image like mirror */
	pxp_dma.linked_channel |= DMA_MCUX_PXP_FLIP(DMA_MCUX_PXP_FLIP_HORIZONTAL);
#endif

	pxp_dma.channel_direction = MEMORY_TO_MEMORY;
	pxp_dma.source_data_size =
		DT_PROP(DT_CHOSEN(zephyr_display), width) * pixel_bytes;
	pxp_dma.dest_data_size = pxp_dma.source_data_size;
	/* Burst lengths are heights of source/dest buffer in pixels */
	pxp_dma.source_burst_length = DT_PROP(DT_CHOSEN(zephyr_display), height);
	pxp_dma.dest_burst_length = pxp_dma.source_burst_length;
	pxp_dma.head_block = &pxp_block;
	pxp_dma.dma_callback = conv_pxp_callback;
	pxp_dma.user_data = &pxp_done;
#endif
	return 0;
}

void convdisp_enqueue(void *buf) {
	k_fifo_alloc_put(&convdisp_fifo_in, buf);
}

int convdisp(uint8_t *pSrc, uint8_t **pDst, uint32_t size, k_timeout_t timeout) {
	if(pSrc == NULL) {
		return -EINVAL;
	}

	/* First check for available buffer in convdisp FIFO */
	*pDst = k_fifo_get(&convdisp_fifo_in, K_NO_WAIT);

	if (*pDst == NULL) {
		/* Buffer available in inf_fifo, and not used yet by inferencing */
		*pDst = k_fifo_get(&inf_fifo, timeout);
		if (*pDst == NULL) {
			return -EAGAIN;
		}
	}
#ifdef CONFIG_APP_USE_PXP
	#ifdef CONFIG_HAS_MCUX_CACHE
		DCACHE_CleanByRange((uint32_t) pSrc, size);
	#endif

	pxp_block.source_address = (uint32_t) pSrc;
	pxp_block.dest_address = (uint32_t) *pDst;
	pxp_block.block_size = size;

	int ret = 0;
	ret = dma_config(pxp_dev, 0, &pxp_dma);
	if (ret < 0) {
		return ret;
	}

	ret = dma_start(pxp_dev, 0);
	if (ret < 0) {
		return ret;
	}
	k_sem_take(&pxp_done, timeout);
#endif /* CONFIG_APP_USE_PXP */
	
	return 0;
}

#else /* CONFIG_APP_CONVERT_DISPLAY=n */

int convdisp_init(uint16_t panelWidth, uint16_t panelHeight) {
	(void) panelHeight;
	(void) panelWidth;

	return 0;
}

void convdisp_enqueue(void *buf) {
	(void) buf;
}

int convdisp(uint8_t *pSrc, uint8_t **pDst, uint32_t size, k_timeout_t timeout) {
	(void) timeout;
	(void) size;

	*pDst = pSrc;
	return 0;
}

#endif /* CONFIG_APP_CONVERT_DISPLAY */
