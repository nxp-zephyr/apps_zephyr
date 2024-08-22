/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
	
	
	.section .rodata
	.align 16
	.global model_data
	.global model_data_end


	.global od_image_data
	.global od_image_data_end


model_data:
	.incbin "face_detect_converted.tflite"
model_data_end:

od_image_data:
od_image_data_end:




