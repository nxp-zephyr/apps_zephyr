/*
 * Copyright 2024, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "model.h"
#include "FacialDetect.h"
#include "output_postproc.h"
#include "yolo_post_processing.h"
#include "image_utils.h"
#include "convert.h"
#include <zephyr/linker/devicetree_regions.h>
#include <zephyr/kernel.h>
#include <stdio.h>

#ifdef CONFIG_LOG
	#include <zephyr/logging/log.h>
	LOG_MODULE_DECLARE(app);
#endif /* CONFIG_LOG */

extern "C" {

#define WND_X0 0
#define WND_Y0 0

inf_results_t g_InfResults;
static uint8_t* s_inputData;
static tensor_dims_t s_inputDims;
static 	tensor_type_t s_inputType;
static std::vector<yolo::object_detection::DetectionResult> s_results;
static yolo::DetectorPostProcess *sp_postProcess;
static 	TfLiteTensor* outputTensor[3];

#ifdef CONFIG_APP_RESIZE_FOR_MODEL
	static uint8_t extract_buf[CONFIG_APP_EXTRACT_WIDTH *
		CONFIG_APP_EXTRACT_HEIGHT * 3U]; /* in RGB888 format */

void Model_Resize(uint8_t* srcData, int srcWidth, int srcHeight) {
	uint32_t x0, y0;

	/* center extraction in camera frame */
	x0 = (srcWidth - CONFIG_APP_EXTRACT_WIDTH) / 2;
	y0 = (srcHeight - CONFIG_APP_EXTRACT_HEIGHT) / 2;

	IMAGE_ExtractRect(extract_buf, x0, y0, CONFIG_APP_EXTRACT_WIDTH,
		CONFIG_APP_EXTRACT_HEIGHT, (const uint16_t*) srcData, srcWidth);

	IMAGE_Resize(extract_buf, CONFIG_APP_EXTRACT_WIDTH,
		CONFIG_APP_EXTRACT_HEIGHT, s_inputData,
		s_inputDims.data[2], s_inputDims.data[1], s_inputDims.data[3]);
}
#else /* CONFIG_APP_RESIZE_FOR_MODEL=n*/
void Model_Resize(uint8_t* srcData, int srcWidth, int srcHeight) {
	(void) srcData;
	(void) srcWidth;
	(void) srcHeight;
}
#endif /* CONFIG_APP_RESIZE_FOR_MODEL */

void Rgb565StridedToRgb888(const uint16_t* pIn, int srcW, int wndW, int wndH, int wndX0, int wndY0,
	uint8_t* p888, int stride, uint8_t isSub128) {
	const uint16_t* pSrc = pIn;
	uint32_t datIn, datOut, datOuts[3];
	uint8_t* p888out = p888;

	for (int y = wndY0,y1=(wndH-wndY0)/stride-wndY0; y < wndH; y += stride,y1--) {
		pSrc = pIn + srcW * y + wndX0;

		for (int x = 0; x < wndW; x += stride * 4) {
			datIn = pSrc[0];
			pSrc += stride;
			datOuts[0] = (datIn & 31) << 19| (datIn & 63 << 5) << 5 | ((datIn>>8) & 0xf8);

			datIn = pSrc[0];
			pSrc += stride;
			datOut = (datIn & 31) << 19| (datIn & 63 << 5) << 5 | ((datIn>>8) & 0xf8);
			datOuts[0] |= datOut << 24;
			datOuts[1] = datOut >> 8;

			datIn = pSrc[0];
			pSrc += stride;
			datOut = (datIn & 31) << 19| (datIn & 63 << 5) << 5 | ((datIn>>8) & 0xf8);
			datOuts[1] |= (datOut << 16) & 0xFFFF0000;
			datOuts[2] = datOut >> 16;

			datIn = pSrc[0];
			pSrc += stride;
			datOut = (datIn & 31) << 19| (datIn & 63 << 5) << 5 | ((datIn>>8) & 0xf8);

			datOuts[2] |= datOut << 8;

			if (isSub128) {
				// subtract 128 bytewisely, equal to XOR with 0x80
				datOuts[0] ^= 0x80808080;
				datOuts[1] ^= 0x80808080;
				datOuts[2] ^= 0x80808080;
			}
			memcpy(p888out, datOuts, 3 * 4);
			p888out += 3 * 4;
		}
	}
}

#if DT_HAS_CHOSEN(zephyr_modelbuf)
/* Place the buffer for the model in a specific linker memory region */
static uint8_t model_input_buf[MODEL_IN_W*MODEL_IN_H*MODEL_IN_C]
	Z_GENERIC_SECTION(LINKER_DT_NODE_REGION_NAME(DT_CHOSEN(zephyr_modelbuf)))
	= {0};


void copy_slice_to_model_input(uint32_t idx, uint32_t cam_slice_buffer,
	uint32_t cam_slice_width, uint32_t cam_slice_height, uint32_t max_idx)
{
	static uint8_t* pCurDat;
	uint32_t curY;
	uint32_t s_imgStride = cam_slice_width / MODEL_IN_W;
	uint32_t ndx = idx;
	curY = ndx * cam_slice_height;
	int wndY = (s_imgStride - (curY - WND_Y0) % s_imgStride) % s_imgStride;

	if (idx > max_idx)
		return;

	pCurDat = model_input_buf + 3 * ((cam_slice_height * ndx + wndY) *
		cam_slice_width / s_imgStride / s_imgStride);

	if (curY + cam_slice_height >= WND_Y0){
		if (MODEL_IN_COLOR_BGR == 1) {
			//Rgb565StridedToBgr888((uint16_t*)cam_slice_buffer, cam_slice_width, cam_slice_width, cam_slice_height, WND_X0, wndY, pCurDat, s_imgStride, 1);
		}else {
			Rgb565StridedToRgb888((uint16_t*)cam_slice_buffer,
				cam_slice_width, cam_slice_width,
				cam_slice_height, WND_X0, wndY, pCurDat,
				s_imgStride, 1);
		}
	}
}
#endif /* DT_HAS_CHOSEN(zephyr_modelbuf) */

void MODEL_ODLogResult(const ODResult_t *p, int retCnt)
{
	LOG_INF("Found boxes count %d\r\n",retCnt);
	for (int i=0; i<retCnt; i++,p++) {
		LOG_INF("%0.2f%%, x1: %d, y1: %d, x2: %d, y2: %d\r\n",
		(double)(p->score*100.0f), p->x1, p->y1, p->x2, p->y2);
	}
}

const char * GetBriefString(inf_results_t * results) {
	static char sz[26];
	sprintf(sz, "%dobj,%04dms", results->odRetCnt,
		((int)results->infUs)/1000);
	sz[11] = 0;
	return sz;
}

void init_face_det(int originalWidth, int originalHeight)
{
	size_t arenaSize;

	if (MODEL_Init() != kStatus_Success)
	{
		LOG_ERR("Failed initializing model");
		for (;;) {}
	}

	size_t usedSize = MODEL_GetArenaUsedBytes(&arenaSize);
	LOG_INF("\r\n%d/%d kB (%0.2f%%) tensor arena used\r\n", usedSize / 1024,
		arenaSize / 1024, 100.0*usedSize/arenaSize);

	s_inputData = MODEL_GetInputTensorData(&s_inputDims, &s_inputType);
	uint32_t out_size = MODEL_GetOutputSize();

	static yolo::object_detection::PostProcessParams postProcessParams =
		yolo::object_detection::PostProcessParams {
		.inputImgRows = (int) s_inputDims.data[1],
		.inputImgCols =	(int) s_inputDims.data[2],
		.output_size = (int) out_size,
		.originalImageWidth = originalWidth,
		.originalImageHeight = originalHeight,
		.threshold = 0.70,
		.nms = 0.45,
		.numClasses = 1,
	#if SERVO_ENABLE
		.topN = 1
	#else
		.topN = 0
	#endif
	};

	float *anchors = MODEL_GetAnchors();
	for (uint32_t i=0; i < out_size; i ++)
	{
		outputTensor[i] = MODEL_GetOutputTensor(i);
		postProcessParams.anchors[i][0] = *(anchors + 6*i);
		postProcessParams.anchors[i][1] = *(anchors + 6*i + 1);
		postProcessParams.anchors[i][2] = *(anchors + 6*i + 2);
		postProcessParams.anchors[i][3] = *(anchors + 6*i + 3);
		postProcessParams.anchors[i][4] = *(anchors + 6*i + 4);
		postProcessParams.anchors[i][5] = *(anchors + 6*i + 5);
	}

	static yolo::DetectorPostProcess postProcess = 
		yolo::DetectorPostProcess((const TfLiteTensor**)outputTensor,
		s_results, postProcessParams);
	sp_postProcess = &postProcess;
}

void face_det(uint8_t *pSrc, int srcWidth, int srcHeight)
{
	inf_results_t InfResults;
	k_thread_runtime_stats_t stats_inf_thread;

#if DT_HAS_CHOSEN(zephyr_modelbuf)
	uint8_t *buf = 0;

	/* Copy intermediate buffer of camera slices to buffer used by model */
	memset(s_inputData,0,s_inputDims.data[1]*s_inputDims.data[2]*s_inputDims.data[3]);
	buf = s_inputData + (s_inputDims.data[1] - MODEL_IN_H) /2 * MODEL_IN_W * MODEL_IN_C;
	memcpy(buf, model_input_buf, MODEL_IN_W*MODEL_IN_H*MODEL_IN_C);
#endif /* DT_HAS_CHOSEN(zephyr_modelbuf) */

#ifdef CONFIG_APP_RESIZE_FOR_MODEL
	Model_Resize((uint8_t *)pSrc, srcWidth, srcHeight);
	MODEL_ConvertInput(s_inputData, &s_inputDims, s_inputType);
#endif

	s_results.clear();
	k_thread_runtime_stats_get(k_current_get(), &stats_inf_thread);
	uint64_t startTime = stats_inf_thread.execution_cycles;
	MODEL_RunInference();
	k_thread_runtime_stats_get(k_current_get(), &stats_inf_thread);
	InfResults.retsTimeStamp = stats_inf_thread.execution_cycles;

	InfResults.infUs = k_cyc_to_us_ceil32(InfResults.retsTimeStamp - startTime);
	InfResults.odRetCnt = 0;
	if (!sp_postProcess->DoPostProcess()) {
		LOG_ERR("Post-processing failed.");
		InfResults.odRetCnt = 0;
	}

	for (const auto& result: s_results) {
		if(result.m_normalisedVal > BOX_SCORE_THRESHOLD) { //score of box
			ODResult_t * odRet;
			odRet = &InfResults.odRets[InfResults.odRetCnt];
			odRet->x1 = result.m_x0;
			odRet->x2 = result.m_x0 + result.m_w;
			odRet->y1 = result.m_y0;
			odRet->y2 = result.m_y0 + result.m_h;
			odRet->score = result.m_normalisedVal;
		#if SERVO_ENABLE
			if((result.m_w * result.m_h) > area_max){
				servo_motor_set_pos((uint16_t)(result.m_x0 + (int(result.m_w) >> 1)),(uint16_t)(result.m_y0 + (int(result.m_h) >> 1)));
				area_max = result.m_w * result.m_h;

			}
		#endif
			InfResults.odRetCnt ++;
		}
	}

	if (InfResults.odRetCnt > 0) {
	#if SERVO_ENABLE
		servo_motor_set_cnt(1);
	#endif
		MODEL_ODLogResult(InfResults.odRets, InfResults.odRetCnt);
		LOG_INF("Inference time %d\r\n", InfResults.infUs);
	}

	/* Copy inference results to global struct for other threads */
	k_sched_lock();
	memcpy(&g_InfResults, &InfResults, sizeof(InfResults));
	k_sched_unlock();
}

void inference_thread(void *config, void *fifo, void *dummy3) {

	uint8_t *inf_buf = NULL, *next_buf = NULL;
	struct k_fifo *inf_fifo = (struct k_fifo *) fifo;
	inf_thread_config_t *inf_config = (inf_thread_config_t *) config;

	init_face_det(inf_config->frameWidth, inf_config->fullFrameHeight);

	while(1) {
		inf_buf = (uint8_t *) k_fifo_get(inf_fifo, K_FOREVER);
		if(inf_buf == NULL) {
			LOG_ERR("k_fifo_get() returned NULL in inference_thread\n");
			return;
		}

		/* Inference the latest buffer in FIFO, check FIFO for more */
		do {
			next_buf = (uint8_t *) k_fifo_get(inf_fifo, K_NO_WAIT);
			if (next_buf != NULL) {
				/* free older buffer for next conversion */
				convdisp_enqueue(inf_buf);
				inf_buf = next_buf;
			}
		} while (next_buf != NULL);

		face_det(inf_buf, inf_config->frameWidth, inf_config->singleFrameHeight);
		convdisp_enqueue(inf_buf);

		/* give other threads chance to execute */
		k_sleep(K_MSEC(10));
	}
}

void sync_slice_rectangles(inf_results_t *infResults) {
	if (infResults->odRetCnt == 0) {
		/* Copy Inference results to slice rectangle copy for this
		 * full frame. */
		memcpy(infResults, &g_InfResults, sizeof(g_InfResults));
	} else {
		if (infResults->retsTimeStamp != g_InfResults.retsTimeStamp) {
			/* Results updated since last sync, but older slices on
			 * display are showing last rectangle.  Set odRetCnt to
			 * 0 to remove all rectangles on this frame.  Results
			 * will sync on the next full frame */
			infResults->odRetCnt = 0;
		}
	}
}

} /* extern "C" */
