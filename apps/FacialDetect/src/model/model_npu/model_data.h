/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// This is a standard TensorFlow Lite model file that has been converted into
// a C data array, so it can be easily compiled into a binary for devices that
// don't have a file system. It was created using the command
// (with additional modification for alignment specification):
// xxd -i cifar10_quant_int8_npu.tflite > model_data.h

#ifdef __arm__
#include <cmsis_compiler.h>
#else
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif

#define MODEL_NAME "cifarnet_quant_int8_npu"
#define MODEL_INPUT_MEAN 127.5f
#define MODEL_INPUT_STD 127.5f

extern uint8_t model_data[];
