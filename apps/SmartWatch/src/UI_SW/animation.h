/*
 * Copyright 2023 NXP
 *
 * SPDX-LICENSE-IDENTIFIER: BSD-3-Clause
 *
 */

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#define DELAY_STARTDOWN 250
#define DELAY_STARTUP 300
#define DELAY_STARTRIGHT 500

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include <lvgl.h>

#endif

//void AnimScreen(lv_obj_t * TargetObject);
void StartDown_Animation(lv_obj_t * TargetObject, int delay);
void StartUp_Animation(lv_obj_t * TargetObject, int delay);
void StartRight_Animation(lv_obj_t * TargetObject, int delay);
void ClockwiseMin_Animation(lv_obj_t * TargetObject, int delay);
void ClockwiseHour_Animation(lv_obj_t * TargetObject, int delay);
void Cloud_Animation(lv_obj_t * TargetObject, int delay);
void OpaOn_Animation(lv_obj_t * TargetObject, int delay);
void Carunlock_Animation(lv_obj_t * TargetObject, int delay);
void Imagescale_Animation(lv_obj_t * TargetObject, int delay);
void ECG_Animation(lv_obj_t * TargetObject, int delay);
void ClockwiseSec_Animation(lv_obj_t * TargetObject, int delay);
void NXP_Animation(lv_obj_t * TargetObject, int delay);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
