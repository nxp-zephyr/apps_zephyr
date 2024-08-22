/*
 * Copyright 2024, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <zephyr/kernel.h>
extern struct k_fifo inf_fifo;  /* FIFO for buffers to inference */

/**
 * @brief Initializes display conversion
 *
 * @param panelWidth width in pixels of display.
 * @param panelHeight height in pixels of display.
 *
 * @retval 0 Is successful.
 * @retval -ENOMEM buffer allocation failed.
 */
int convdisp_init(uint16_t panelWidth, uint16_t panelHeight);

/**
 * @brief enqueues display conversion buffer
 * 
 * Call after buffer written to display, before next conversion
 *
 * @param buf Pointer to buffer.
 */
void convdisp_enqueue(void *buf);

/**
 * @brief Converts source buffer to display buffer
 *
 * @param pSrc Pointer to input source buffer.
 * @param pDst Pointer to output destination buffer.
 * @param timeout when waiting for inf_fifo.
 *
 * @retval 0 Is successful.
 * @retval -EINVAL pSrc address invalid.
 * @retval -EAGAIN k_fifo_get() timed out.
 */
int convdisp(uint8_t *pSrc, uint8_t **pDst, uint32_t size, k_timeout_t timeout);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
