/*
 * Copyright 2023 NXP
 *
 * SPDX-LICENSE-IDENTIFIER: BSD-3-Clause
 *
 */

#ifndef _SCREEN_SETUP_H_
#define _SCREEN_SETUP_H_


#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#include "gui_guider.h"
#else
#include <lvgl.h>

#endif

void complete_set(void);
//static void ui_event_S1_Watch_Digital(lv_event_t * e);
//static void ui_event_BTN_Home1(lv_event_t * e);
//static void ui_event_BTN_Next_Song(lv_event_t * e);
void ui_S1_Watch_Digital_screen_init(void);
void ui_S5_Weather_screen_init(void);
void ui_S9_Sport_screen_init(void);
void ui_S11_Music_screen_init(void);
void ui_S24_EKG_screen_init(void);
void ui_S2_Watch_Analog_screen_init(void);
void Set_border_style(lv_obj_t * Tarjet);

void AnimScreen(lv_obj_t * TargetObject);

void changedirectory(void);
void ChangeScreen(lv_dir_t Dir);
void update_lvtask_delay(void);

extern lv_ui guider_ui;


void clock_count_24(int * hour, int * minute, int * seconds);
void updateTIMERS(int Min, int Hours);

void ui_Screen_LowPower(void);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
