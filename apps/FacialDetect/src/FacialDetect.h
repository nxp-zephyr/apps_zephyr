/*
 * Copyright 2024, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <zephyr/kernel.h>
#include "image_utils.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Inference Thread */
#define THREAD_INF_STACKSIZE	4096
#define THREAD_PRIORITY_INF	2	/* lowest priority */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
typedef struct
{
	int frameWidth;
	int fullFrameHeight;
	int singleFrameHeight;
} inf_thread_config_t;

typedef struct
{
	ODResult_t odRets[MAX_OD_BOX_CNT];
	int odRetCnt;
	uint32_t infUs;
	uint64_t retsTimeStamp;
} inf_results_t;

void inference_thread(void *config, void *fifo, void *dummy3);

extern uint32_t static_image_addr;
extern inf_results_t g_InfResults;
extern 	const struct device *display_dev;

#include "image_utils.h"
extern ODResult_t s_odRets[];

void Model_Resize(uint8_t* srcData, int srcWidth, int srcHeight);
const char * GetBriefString(inf_results_t * results);
void sync_slice_rectangles(inf_results_t *infResults);
void copy_slice_to_model_input(uint32_t idx, uint32_t cam_slice_buffer,
	uint32_t cam_slice_width, uint32_t cam_slice_height, uint32_t max_idx);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
