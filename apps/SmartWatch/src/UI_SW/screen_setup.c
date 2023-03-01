/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "screen_setup.h"
#include "ui_helpers.h"
#include <lvgl.h>

#include "gui_guider.h"
#include "animation.h"
#include "ui_Music.h"
#include "../../../../../modules/lib/gui/lvgl/src/core/lv_event.h"
#include "../../../../../modules/lib/gui/lvgl/src/core/lv_disp.h"

void ui_S0_Splash_screen_init(void);

uint8_t SongCounter=0;
static void ui_event_BTN_Next_Song(lv_event_t * e);
static void ui_event_BTN_Home1(lv_event_t * e);
static void ui_event_S1_Watch_Digital(lv_event_t * e);
static void ui_event_S0_Splash(lv_event_t * e); 
 int screen_digital_clock_1_hour_value = 15;
 int screen_digital_clock_1_min_value = 31;
 int screen_digital_clock_1_sec_value = 52;

uint32_t AngleSecLP = 0;
uint32_t AngleMinLP = 0;
uint32_t AngleHourLP = 0;

static void lv_screen_loaded(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOADED:
	{

		/*CODE*/
	update_lvtask_delay();
	}
		break;
	default:
		break;
	}
}


static void ui_event_S1_Watch_Digital(lv_event_t * e)
{
	lv_dir_t dir;
	lv_event_code_t event = lv_event_get_code(e);
	if(event ==  LV_EVENT_GESTURE)
	{
		dir = lv_indev_get_gesture_dir(lv_indev_get_act());
		ChangeScreen(dir);
	}

}
static void ui_event_BTN_Home1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    //lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(guider_ui.ui_S1_Watch_Digital, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
        changedirectory();
    }
}
static void ui_event_BTN_Next_Song(lv_event_t * e)
{

    lv_event_code_t event = lv_event_get_code(e);
   // lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
    	//DbgConsole_Printf("BTN CallBack\r\n");
    SongCounter++;
    if((SongCounter % 2) > 0)
    {		ui_Change_Song(kDance_onTheMoon);}
     else { ui_Change_Song(kSong_2);}
}
}

static void ui_event_S0_Splash(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
//     if(event == LV_EVENT_SCREEN_LOAD_START) {
//        OpaOn_Animation(guider_ui.ui_Image_NXP_Logo, 200);
//        StartUp_Animation(guider_ui.ui_Panel_SLS_Logo, 0);
//        OpaOn_Animation(guider_ui.ui_Label_Smartwatch_Demo, 300);
//        OpaOn_Animation(guider_ui.ui_Label_Powered, 500);
//        _ui_screen_change(guider_ui.ui_S2_Watch_Analog, LV_SCR_LOAD_ANIM_FADE_ON, 60, 2300);
//        OpaOn_Animation(guider_ui.ui_Label_MIMXRT595EVK, 400);
//        OpaOn_Animation(guider_ui.ui_Image_Bg_Splash, 0);
//        NXP_Animation(guider_ui.ui_Image_NXP_Logo1, 100);
//   //       //Cloud_Animation(guider_ui.ui_Image_Cloud_Bg1, 0);
//   //      // ClockwiseSec_Animation(guider_ui.ui_Image_Sec, 0);
//   //      // Imagescale_Animation(guider_ui.ui_Image_Payment_Ok_Anim, 0);
//   //     //  Imagescale_Animation(guider_ui.ui_Image_Find_Anim1, 0);
//   //     //  ECG_Animation(guider_ui.ui_Image_EKG, 0);
//   //     //  Imagescale_Animation(guider_ui.ui_Image_Heart2, 0);
//  }
	Cloud_Animation(guider_ui.ui_Image_Cloud_Bg12, 0);
  ECG_Animation(guider_ui.ui_Image_EKG, 0);
  Imagescale_Animation(guider_ui.ui_Image_Heart2, 0);
 	if(event ==  LV_EVENT_RELEASED)
 {
lv_scr_load(guider_ui.ui_S1_Watch_Digital);
 }

}
void clock_count_24(int * hour, int * minute, int * seconds)
{
    (*seconds)++;

    if(*seconds == 60) {
        *seconds = 0;
        (*minute)++;
    }

    if(*minute == 60) {
        *minute = 0;
        (*hour)++;
    }

    if(*hour == 24) {
        *hour = 0;
    }
}

void AnimScreen(lv_obj_t * TargetObject){

if(TargetObject==guider_ui.ui_S1_Watch_Digital){
	StartDown_Animation(guider_ui.ui_Label_Hour, 0);
	StartUp_Animation(guider_ui.ui_Label_Minute, 100);
	OpaOn_Animation(guider_ui.ui_Image_Bg, 0);
	OpaOn_Animation(guider_ui.ui_S1_Content, 200);
	StartRight_Animation(guider_ui.ui_Image_NXP, 500);
}
if(TargetObject==guider_ui.ui_S2_Watch_Analog){
	OpaOn_Animation(guider_ui.ui_Image_Bg1, 0);
	OpaOn_Animation(guider_ui.ui_Anim_On1, 0);
	StartRight_Animation(guider_ui.ui_Image_NXP1, 500);
	//ClockwiseSec_Animation(guider_ui.ui_Image_Sec, 0);
}
if(TargetObject==guider_ui.ui_S5_Weather){
	OpaOn_Animation(guider_ui.ui_Anim_On_S5, 100);
	StartUp_Animation(guider_ui.ui_Anim_Up_S5, 80);
	StartDown_Animation(guider_ui.ui_Anim_Down_S5, 100);
	OpaOn_Animation(guider_ui.ui_Image_Cloud_Bg1, 0);
	OpaOn_Animation(guider_ui.ui_Image_Cloud_Bg12, 0);
	OpaOn_Animation(guider_ui.ui_Image_Sun, 0);
	Cloud_Animation(guider_ui.ui_Image_Cloud_Bg12, 0);
}
if(TargetObject==guider_ui.ui_S9_Sport){
	OpaOn_Animation(guider_ui.ui_Image_Bg7, 0);
	StartRight_Animation(guider_ui.ui_Anim_Right_S9, 0);
	StartDown_Animation(guider_ui.ui_Header_S9, 0);
	StartUp_Animation(guider_ui.ui_Anim_On_S9, 0);
}
if(TargetObject==guider_ui.ui_S11_Music){
	OpaOn_Animation(guider_ui.ui_Anim_On_S11, 0);
	StartDown_Animation(guider_ui.ui_Anim_Down_S11, 80);
	StartUp_Animation(guider_ui.ui_Anim_Up_S11, 60);
}
if(TargetObject==guider_ui.ui_S24_EKG){
    OpaOn_Animation(guider_ui.ui_Image_Bg21, 0);
    StartUp_Animation(guider_ui.ui_Anim_Up_S24, 200);
    StartDown_Animation(guider_ui.ui_Header_S24, 0);
    OpaOn_Animation(guider_ui.ui_Anim_On_S24, 120);
    StartDown_Animation(guider_ui.ui_Anim_Down_S24, 100);
    ECG_Animation(guider_ui.ui_Image_EKG, 0);
   Imagescale_Animation(guider_ui.ui_Image_Heart2, 0);
}
}

void Set_border_style(lv_obj_t * Tarjet){
    static lv_style_t style_NoBorder;
           lv_style_init(&style_NoBorder);

           lv_style_set_border_width(&style_NoBorder, 0);
           lv_obj_add_style(Tarjet, &style_NoBorder, LV_PART_MAIN|LV_STATE_DEFAULT);
           lv_obj_set_style_bg_img_src(Tarjet, &style_NoBorder, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void complete_set(void){

	ui_S1_Watch_Digital_screen_init();
	ui_S2_Watch_Analog_screen_init();
	ui_S5_Weather_screen_init();
	ui_S9_Sport_screen_init();
	ui_S11_Music_screen_init();
	ui_S24_EKG_screen_init();
  ui_Screen_LowPower();
	ui_S0_Splash_screen_init();

   lv_obj_add_event_cb(guider_ui.ui_S1_Watch_Digital, ui_event_S1_Watch_Digital, LV_EVENT_GESTURE, NULL);
	 lv_obj_clear_flag(guider_ui.ui_S1_Watch_Digital, LV_OBJ_FLAG_SCROLLABLE);

	 lv_obj_add_event_cb(guider_ui.ui_S2_Watch_Analog, ui_event_S1_Watch_Digital, LV_EVENT_GESTURE, NULL);
	 lv_obj_clear_flag(guider_ui.ui_S2_Watch_Analog, LV_OBJ_FLAG_SCROLLABLE);

	 lv_obj_add_event_cb(guider_ui.ui_S5_Weather, ui_event_S1_Watch_Digital, LV_EVENT_GESTURE, NULL);
	 lv_obj_clear_flag(guider_ui.ui_S5_Weather, LV_OBJ_FLAG_SCROLLABLE);
	 lv_obj_add_event_cb(guider_ui.ui_BTN_Home1, ui_event_BTN_Home1, LV_EVENT_ALL, NULL);

	 lv_obj_add_event_cb(guider_ui.ui_S9_Sport, ui_event_S1_Watch_Digital, LV_EVENT_GESTURE, NULL);
	 lv_obj_clear_flag(guider_ui.ui_S9_Sport, LV_OBJ_FLAG_SCROLLABLE);
	 lv_obj_add_event_cb(guider_ui.ui_BTN_Home5, ui_event_BTN_Home1, LV_EVENT_ALL, NULL);
 
	 lv_obj_add_event_cb(guider_ui.ui_S11_Music, ui_event_S1_Watch_Digital, LV_EVENT_GESTURE, NULL);
   lv_obj_clear_flag(guider_ui.ui_S11_Music, LV_OBJ_FLAG_SCROLLABLE);
  
  lv_obj_add_event_cb(guider_ui.ui_BTN_Home7, ui_event_BTN_Home1, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(guider_ui.ui_Image_Audio_Next_btn, ui_event_BTN_Next_Song, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(guider_ui.ui_Image_Audio_Back, ui_event_BTN_Next_Song, LV_EVENT_ALL, NULL);

  lv_obj_add_event_cb(guider_ui.ui_S24_EKG, ui_event_S1_Watch_Digital, LV_EVENT_GESTURE, NULL);
  lv_obj_clear_flag(guider_ui.ui_S24_EKG, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_add_event_cb(guider_ui.ui_BTN_Home20, ui_event_BTN_Home1, LV_EVENT_ALL, NULL);


  lv_obj_add_event_cb(guider_ui.ui_SLowPower, ui_event_S1_Watch_Digital, LV_EVENT_GESTURE, NULL);
  lv_obj_clear_flag(guider_ui.ui_SLowPower, LV_OBJ_FLAG_SCROLLABLE);

 lv_obj_add_event_cb(guider_ui.ui_S0_Splash, ui_event_S0_Splash, LV_EVENT_RELEASED, NULL);
 lv_obj_clear_flag(guider_ui.ui_S0_Splash, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_add_event_cb(guider_ui.ui_S0_Splash, ui_event_S0_Splash, LV_EVENT_SCREEN_LOAD_START, NULL);


lv_obj_add_event_cb(guider_ui.ui_S1_Watch_Digital, lv_screen_loaded, LV_EVENT_SCREEN_LOADED, NULL);
lv_obj_add_event_cb(guider_ui.ui_SLowPower, lv_screen_loaded, LV_EVENT_SCREEN_LOADED, NULL);
lv_obj_add_event_cb(guider_ui.ui_S2_Watch_Analog, lv_screen_loaded, LV_EVENT_SCREEN_LOADED, NULL);

// lv_obj_add_event_cb(guider_ui.ui_S1_Watch_Digital, lv_screen_start, LV_EVENT_SCREEN_UNLOAD_START, NULL);
// lv_obj_add_event_cb(guider_ui.ui_SLowPower, lv_screen_start, LV_EVENT_SCREEN_UNLOAD_START, NULL);
// lv_obj_add_event_cb(guider_ui.ui_S2_Watch_Analog, lv_screen_start, LV_EVENT_SCREEN_UNLOAD_START, NULL);


}

 void set_angle_clockLP(uint16_t Hours, uint16_t Minutes, uint16_t Seconds){
	 if(Hours>12){
		 Hours = Hours - 12;
	 }
	 AngleHourLP = Hours*300;
	 AngleMinLP = Minutes*60;

	 AngleSecLP = Seconds*60;

	 if(AngleHourLP > 360){AngleHourLP = AngleHourLP - 3600;}
	 if(AngleMinLP > 360){AngleMinLP = AngleMinLP - 3600;}
   if(AngleSecLP > 360){AngleSecLP = AngleSecLP - 3600;}

 }

void screen_digital_clock_1_timer(lv_timer_t *timer)
{	
  clock_count_24(&screen_digital_clock_1_hour_value, &screen_digital_clock_1_min_value, &screen_digital_clock_1_sec_value);
 
    lv_label_set_text_fmt(guider_ui.ui_Label_Seconds, "%02d", screen_digital_clock_1_sec_value);
    lv_label_set_text_fmt(guider_ui.ui_Label_Minute,     "%02d", screen_digital_clock_1_min_value);
    lv_label_set_text_fmt(guider_ui.ui_Label_Hour,     "%02d", screen_digital_clock_1_hour_value);

    set_angle_clockLP(screen_digital_clock_1_hour_value, screen_digital_clock_1_min_value, screen_digital_clock_1_sec_value);
    
    lv_img_set_angle(guider_ui.ui_Image_SecLP, (AngleSecLP));
    lv_img_set_angle(guider_ui.ui_Image_MinLP, (AngleMinLP));
    lv_img_set_angle(guider_ui.ui_Image_HourLP, (AngleHourLP));

      //   lv_img_t * img = (lv_img_t *)guider_ui.ui_Image_Sec;
      // img->angle = AngleSecLP;
   
    //vg_lite_rotate(80,  &ui_img_img_clockwise_sec_png_data);


    lv_img_set_angle(guider_ui.ui_Image_Sec, (AngleSecLP));
    lv_img_set_angle(guider_ui.ui_Image_Min, (AngleMinLP));
    lv_img_set_angle(guider_ui.ui_Image_Hour, (AngleHourLP));

    // lv_obj_refresh_ext_draw_size(guider_ui.ui_Image_Min);
     
     //_lv_refr_init();
     //lv_obj_redraw(NULL, guider_ui.ui_Image_Min);
 //if( guider_ui.ui_S2_Watch_Analog == ptrScreen){   
  //	lv_refr_now(NULL);
   //lv_scr_load(guider_ui.ui_S2_Watch_Analog);
 //}
}
void updateTIMERS(int Min, int Hours){
screen_digital_clock_1_hour_value = Hours;
screen_digital_clock_1_min_value = Min;

}

void ui_S0_Splash_screen_init(void)
{

    // ui_S0_Splash

    guider_ui.ui_S0_Splash = lv_obj_create(NULL);

    lv_obj_clear_flag(guider_ui.ui_S0_Splash, LV_OBJ_FLAG_SCROLLABLE);

   // 
    lv_obj_set_style_bg_color(guider_ui.ui_S0_Splash, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S0_Splash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Image_Bg_Splash

    guider_ui.ui_Image_Bg_Splash = lv_img_create(guider_ui.ui_S0_Splash);
    lv_img_set_src(guider_ui.ui_Image_Bg_Splash, &ui_img_img_bg_png);

    lv_obj_set_width(guider_ui.ui_Image_Bg_Splash, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Bg_Splash, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Bg_Splash, 0);
    lv_obj_set_y(guider_ui.ui_Image_Bg_Splash, 0);

    lv_obj_set_align(guider_ui.ui_Image_Bg_Splash, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Bg_Splash, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Bg_Splash, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Bg_Splash, 0, 0);

    // ui_Image_NXP_Logo1

    guider_ui.ui_Image_NXP_Logo1 = lv_img_create(guider_ui.ui_S0_Splash);
    lv_img_set_src(guider_ui.ui_Image_NXP_Logo1, &ui_img_img_nxp_logo_big_png);

    lv_obj_set_width(guider_ui.ui_Image_NXP_Logo1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_NXP_Logo1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_NXP_Logo1, 0);
    lv_obj_set_y(guider_ui.ui_Image_NXP_Logo1, 85);

    lv_obj_set_align(guider_ui.ui_Image_NXP_Logo1, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(guider_ui.ui_Image_NXP_Logo1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_NXP_Logo1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_NXP_Logo1, 114, 40);

    // ui_Image_NXP_Logo

    guider_ui.ui_Image_NXP_Logo = lv_img_create(guider_ui.ui_S0_Splash);
    lv_img_set_src(guider_ui.ui_Image_NXP_Logo, &ui_img_img_nxp_logo_big_png);

    lv_obj_set_width(guider_ui.ui_Image_NXP_Logo, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_NXP_Logo, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_NXP_Logo, 0);
    lv_obj_set_y(guider_ui.ui_Image_NXP_Logo, 85);

    lv_obj_set_align(guider_ui.ui_Image_NXP_Logo, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(guider_ui.ui_Image_NXP_Logo, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_NXP_Logo, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_NXP_Logo, 0, 0);

    // ui_Label_MIMXRT595EVK

    guider_ui.ui_Label_MIMXRT595EVK = lv_label_create(guider_ui.ui_S0_Splash);

    lv_obj_set_width(guider_ui.ui_Label_MIMXRT595EVK, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_MIMXRT595EVK, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_MIMXRT595EVK, -5);
    lv_obj_set_y(guider_ui.ui_Label_MIMXRT595EVK, 30);

    lv_obj_set_align(guider_ui.ui_Label_MIMXRT595EVK, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_MIMXRT595EVK, "MIMXRT595-EVK");

    lv_obj_set_style_text_color(guider_ui.ui_Label_MIMXRT595EVK, lv_color_hex(0x919191), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_MIMXRT595EVK, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_MIMXRT595EVK, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label_Smartwatch_Demo

    guider_ui.ui_Label_Smartwatch_Demo = lv_label_create(guider_ui.ui_S0_Splash);

    lv_obj_set_width(guider_ui.ui_Label_Smartwatch_Demo, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Smartwatch_Demo, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Smartwatch_Demo, 0);
    lv_obj_set_y(guider_ui.ui_Label_Smartwatch_Demo, 0);

    lv_obj_set_align(guider_ui.ui_Label_Smartwatch_Demo, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Smartwatch_Demo, "Smartwatch Demo v1.0");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Smartwatch_Demo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Smartwatch_Demo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Smartwatch_Demo, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label_Powered

   guider_ui.ui_Label_Powered = lv_label_create(guider_ui.ui_S0_Splash);

    lv_obj_set_width(guider_ui.ui_Label_Powered, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Powered, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Powered, 0);
    lv_obj_set_y(guider_ui.ui_Label_Powered, -85);

    lv_obj_set_align(guider_ui.ui_Label_Powered, LV_ALIGN_BOTTOM_MID);

    lv_label_set_text(guider_ui.ui_Label_Powered, "Powered by");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Powered, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Powered, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Powered, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Panel_SLS_Logo

    guider_ui.ui_Panel_SLS_Logo = lv_obj_create(guider_ui.ui_S0_Splash);

    lv_obj_set_height(guider_ui.ui_Panel_SLS_Logo, 69);
    lv_obj_set_width(guider_ui.ui_Panel_SLS_Logo, lv_pct(100));

    lv_obj_set_x(guider_ui.ui_Panel_SLS_Logo, 0);
    lv_obj_set_y(guider_ui.ui_Panel_SLS_Logo, 0);

    lv_obj_set_align(guider_ui.ui_Panel_SLS_Logo, LV_ALIGN_BOTTOM_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_SLS_Logo, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_pad_left(guider_ui.ui_Panel_SLS_Logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(guider_ui.ui_Panel_SLS_Logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(guider_ui.ui_Panel_SLS_Logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(guider_ui.ui_Panel_SLS_Logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Image_SLS_Logo

    guider_ui.ui_Image_SLS_Logo = lv_img_create(guider_ui.ui_Panel_SLS_Logo);
    lv_img_set_src(guider_ui.ui_Image_SLS_Logo, &_Zephyr_RTOS_logo_118x57);

    lv_obj_set_width(guider_ui.ui_Image_SLS_Logo, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_SLS_Logo, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_SLS_Logo, 0);
    lv_obj_set_y(guider_ui.ui_Image_SLS_Logo, 0);

    lv_obj_set_align(guider_ui.ui_Image_SLS_Logo, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_SLS_Logo, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_SLS_Logo, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_SLS_Logo, 0, 0);
}

void ui_S1_Watch_Digital_screen_init(void)
{

    // ui_S1_Watch_Digital
    guider_ui.ui_S1_Watch_Digital = lv_obj_create(NULL);
    lv_obj_clear_flag(guider_ui.ui_S1_Watch_Digital, LV_OBJ_FLAG_SCROLLABLE);


   // lv_obj_add_event_cb(guider_ui.ui_S1_Watch_Digital, ui_event_S1_Watch_Digital, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_S1_Watch_Digital, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S1_Watch_Digital, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Bg

    guider_ui.ui_Image_Bg = lv_img_create(guider_ui.ui_S1_Watch_Digital);
    lv_img_set_src(guider_ui.ui_Image_Bg, &ui_img_img_bg_digital_png);

    lv_obj_set_width(guider_ui.ui_Image_Bg, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Bg, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Bg, 0);
    lv_obj_set_y(guider_ui.ui_Image_Bg, 0);

    lv_obj_set_align(guider_ui.ui_Image_Bg, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Bg, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Bg, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Bg, 0, 0);

    // guider.ui_Label_Minute

    guider_ui.ui_Label_Minute = lv_label_create(guider_ui.ui_S1_Watch_Digital);

    lv_obj_set_width(guider_ui.ui_Label_Minute, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Minute, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Minute, 4);
    lv_obj_set_y(guider_ui.ui_Label_Minute, 62);

    lv_obj_set_align(guider_ui.ui_Label_Minute, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Minute, "32");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Minute, lv_color_hex(0xFF4818), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Minute, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Minute, &ui_font_number_light, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_S1_Content

    guider_ui.ui_S1_Content = lv_obj_create(guider_ui.ui_S1_Watch_Digital);

    lv_obj_set_width(guider_ui.ui_S1_Content, 392);
    lv_obj_set_height(guider_ui.ui_S1_Content, 395);

    lv_obj_set_x(guider_ui.ui_S1_Content, 0);
    lv_obj_set_y(guider_ui.ui_S1_Content, 0);

    lv_obj_set_align(guider_ui.ui_S1_Content, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_S1_Content, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_S1_Content, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S1_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    Set_border_style(guider_ui.ui_S1_Content);
    // guider_ui.ui_Label_Power

    guider_ui.ui_Label_Power = lv_label_create(guider_ui.ui_S1_Content);

    lv_obj_set_width(guider_ui.ui_Label_Power, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Power, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Power, 9);
    lv_obj_set_y(guider_ui.ui_Label_Power, -152);

    lv_obj_set_align(guider_ui.ui_Label_Power, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Power, "86%");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Power, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Power, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Power, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Flash

    guider_ui.ui_Image_Flash = lv_img_create(guider_ui.ui_S1_Content);
    lv_img_set_src(guider_ui.ui_Image_Flash, &ui_img_icn_flash_png);

    lv_obj_set_width(guider_ui.ui_Image_Flash, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Flash, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Flash, -26);
    lv_obj_set_y(guider_ui.ui_Image_Flash, -152);

    lv_obj_set_align(guider_ui.ui_Image_Flash, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Flash, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Flash, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Flash, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Flash, lv_color_hex(0x1099E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Flash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Sport

    guider_ui.ui_Image_Sport = lv_img_create(guider_ui.ui_S1_Content);
    lv_img_set_src(guider_ui.ui_Image_Sport, &ui_img_icn_sport_png);

    lv_obj_set_width(guider_ui.ui_Image_Sport, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Sport, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Sport, 130);
    lv_obj_set_y(guider_ui.ui_Image_Sport, -77);

    lv_obj_set_align(guider_ui.ui_Image_Sport, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Sport, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Sport, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Sport, 0, 0);

    // guider_ui.ui_Image_Label_Sport

    guider_ui.ui_Image_Label_Sport = lv_img_create(guider_ui.ui_S1_Content);
    lv_img_set_src(guider_ui.ui_Image_Label_Sport, &ui_img_text_sport_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Sport, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Sport, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Sport, 155);
    lv_obj_set_y(guider_ui.ui_Image_Label_Sport, -94);

    lv_obj_set_align(guider_ui.ui_Image_Label_Sport, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Sport, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Sport, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Sport, 0, 0);
    Set_border_style(guider_ui.ui_Image_Label_Sport);
    // guider_ui.ui_Image_Label_Messages

    guider_ui.ui_Image_Label_Messages = lv_img_create(guider_ui.ui_S1_Content);
    lv_img_set_src(guider_ui.ui_Image_Label_Messages, &ui_img_text_message_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Messages, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Messages, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Messages, 145);
    lv_obj_set_y(guider_ui.ui_Image_Label_Messages, 101);

    lv_obj_set_align(guider_ui.ui_Image_Label_Messages, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Messages, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Messages, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Messages, 0, 0);
    Set_border_style(guider_ui.ui_Image_Label_Messages);

   // lv_obj_add_event_cb(guider_ui.ui_Image_Label_Messages, ui_event_Image_Label_Messages, LV_EVENT_ALL, NULL);

    // guider_ui.ui_Image_Notifi

    guider_ui.ui_Image_Notifi = lv_img_create(guider_ui.ui_S1_Content);
    lv_img_set_src(guider_ui.ui_Image_Notifi, &ui_img_icn_message_png);

    lv_obj_set_width(guider_ui.ui_Image_Notifi, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Notifi, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Notifi, 129);
    lv_obj_set_y(guider_ui.ui_Image_Notifi, 81);

    lv_obj_set_align(guider_ui.ui_Image_Notifi, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Notifi, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Notifi, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Notifi, 0, 0);

    // guider_ui.ui_Image_Step

    guider_ui.ui_Image_Step = lv_img_create(guider_ui.ui_S1_Content);
    lv_img_set_src(guider_ui.ui_Image_Step, &ui_img_icn_step_png);

    lv_obj_set_width(guider_ui.ui_Image_Step, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Step, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Step, -24);
    lv_obj_set_y(guider_ui.ui_Image_Step, 150);

    lv_obj_set_align(guider_ui.ui_Image_Step, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Step, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Step, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Step, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Step, lv_color_hex(0xE35515), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Step, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Weather

    guider_ui.ui_Image_Weather = lv_img_create(guider_ui.ui_S1_Content);
    lv_img_set_src(guider_ui.ui_Image_Weather, &ui_img_icn_weather_1_png);

    lv_obj_set_width(guider_ui.ui_Image_Weather, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Weather, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Weather, -127);
    lv_obj_set_y(guider_ui.ui_Image_Weather, 65);

    lv_obj_set_align(guider_ui.ui_Image_Weather, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Weather, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Weather, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Weather, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Weather, lv_color_hex(0x7B797B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Weather, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Date

    guider_ui.ui_Label_Date = lv_label_create(guider_ui.ui_S1_Content);

    lv_obj_set_width(guider_ui.ui_Label_Date, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Date, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Date, -116);
    lv_obj_set_y(guider_ui.ui_Label_Date, -76);

    lv_obj_set_align(guider_ui.ui_Label_Date, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Date, "05/15");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Date, lv_color_hex(0x7B797B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Date, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Date, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Week

    guider_ui.ui_Label_Week = lv_label_create(guider_ui.ui_S1_Content);

    lv_obj_set_width(guider_ui.ui_Label_Week, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Week, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Week, -116);
    lv_obj_set_y(guider_ui.ui_Label_Week, -51);

    lv_obj_set_align(guider_ui.ui_Label_Week, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Week, "WED");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Week, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Week, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Week, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.guider_ui.ui_Label_Degree

    guider_ui.ui_Label_Degree = lv_label_create(guider_ui.ui_S1_Content);

    lv_obj_set_width(guider_ui.ui_Label_Degree, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Degree, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Degree, -120);
    lv_obj_set_y(guider_ui.ui_Label_Degree, 95);

    lv_obj_set_align(guider_ui.ui_Label_Degree, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Degree, "26°");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Degree, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Degree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Degree, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Step_Count

    guider_ui.ui_Label_Step_Count = lv_label_create(guider_ui.ui_S1_Content);

    lv_obj_set_width(guider_ui.ui_Label_Step_Count, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Step_Count, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Step_Count, 13);
    lv_obj_set_y(guider_ui.ui_Label_Step_Count, 152);

    lv_obj_set_align(guider_ui.ui_Label_Step_Count, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Step_Count, "1526");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Step_Count, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Step_Count, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Step_Count, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Arc_Battery

    guider_ui.ui_Arc_Battery = lv_arc_create(guider_ui.ui_S1_Content);

    lv_obj_set_width(guider_ui.ui_Arc_Battery, 370);
    lv_obj_set_height(guider_ui.ui_Arc_Battery, 370);

    lv_obj_set_x(guider_ui.ui_Arc_Battery, 0);
    lv_obj_set_y(guider_ui.ui_Arc_Battery, 0);

    lv_obj_set_align(guider_ui.ui_Arc_Battery, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Arc_Battery, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Arc_Battery, LV_OBJ_FLAG_CLICKABLE);

    lv_arc_set_range(guider_ui.ui_Arc_Battery, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Battery, 80);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Battery, 0, 50);
    lv_arc_set_rotation(guider_ui.ui_Arc_Battery, 245);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Battery, lv_color_hex(0x4A4C4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Battery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Battery, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Battery, lv_color_hex(0x1099E6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Battery, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Battery, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Battery, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Battery, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // ui_Arc_Step_Count

    guider_ui.ui_Arc_Step_Count = lv_arc_create(guider_ui.ui_S1_Content);

    lv_obj_set_width(guider_ui.ui_Arc_Step_Count, 370);
    lv_obj_set_height(guider_ui.ui_Arc_Step_Count, 370);

    lv_obj_set_x(guider_ui.ui_Arc_Step_Count, 0);
    lv_obj_set_y(guider_ui.ui_Arc_Step_Count, 0);

    lv_obj_set_align(guider_ui.ui_Arc_Step_Count, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Arc_Step_Count, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Arc_Step_Count, LV_OBJ_FLAG_CLICKABLE);

    lv_arc_set_range(guider_ui.ui_Arc_Step_Count, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Step_Count, 80);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Step_Count, 0, 50);
    lv_arc_set_rotation(guider_ui.ui_Arc_Step_Count, 65);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Step_Count, lv_color_hex(0x4A4C4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Step_Count, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Step_Count, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Step_Count, lv_color_hex(0xFF5D18), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Step_Count, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Step_Count, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Step_Count, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Step_Count, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // guider_ui.ui_Image2

    guider_ui.ui_Image2 = lv_img_create(guider_ui.ui_S1_Watch_Digital);
    lv_img_set_src(guider_ui.ui_Image2, &ui_img_img_clock_shadow_png);

    lv_obj_set_width(guider_ui.ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image2, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image2, 0);
    lv_obj_set_y(guider_ui.ui_Image2, 28);

    lv_obj_set_align(guider_ui.ui_Image2, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image2, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image2, 0, 0);

    // guider_ui.ui_Label_Hour

    guider_ui.ui_Label_Hour = lv_label_create(guider_ui.ui_S1_Watch_Digital);

    lv_obj_set_width(guider_ui.ui_Label_Hour, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Hour, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Hour, 5);
    lv_obj_set_y(guider_ui.ui_Label_Hour, -57);

    lv_obj_set_align(guider_ui.ui_Label_Hour, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Hour, "15");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Hour, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Hour, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Hour, &ui_font_number_bold, LV_PART_MAIN | LV_STATE_DEFAULT);


    // guider_ui.ui_Label_Seconds 
    guider_ui.ui_Label_Seconds = lv_label_create(guider_ui.ui_S1_Watch_Digital);

    lv_obj_set_width(guider_ui.ui_Label_Seconds, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Seconds, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Seconds, 100);
    lv_obj_set_y(guider_ui.ui_Label_Seconds, 0);

    lv_obj_set_align(guider_ui.ui_Label_Seconds, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Seconds, "51");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Seconds, lv_color_hex(0x95de0d), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Seconds, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Seconds, &lv_font_Montserrat_Light_40 , LV_PART_MAIN | LV_STATE_DEFAULT);



    // guider_ui.ui_Image_NXP

    guider_ui.ui_Image_NXP = lv_img_create(guider_ui.ui_S1_Watch_Digital);
    lv_img_set_src(guider_ui.ui_Image_NXP, &ui_img_img_nxp_png);

    lv_obj_set_width(guider_ui.ui_Image_NXP, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_NXP, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_NXP, -130);
    lv_obj_set_y(guider_ui.ui_Image_NXP, 0);

    lv_obj_set_align(guider_ui.ui_Image_NXP, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_NXP, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_NXP, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_NXP, 0, 0);

    // guider_ui.ui_S1_Buttons

    guider_ui.ui_S1_Buttons = lv_obj_create(guider_ui.ui_S1_Watch_Digital);

    lv_obj_set_width(guider_ui.ui_S1_Buttons, 392);
    lv_obj_set_height(guider_ui.ui_S1_Buttons, 392);

    lv_obj_set_x(guider_ui.ui_S1_Buttons, 0);
    lv_obj_set_y(guider_ui.ui_S1_Buttons, 0);

    lv_obj_set_align(guider_ui.ui_S1_Buttons, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_S1_Buttons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_S1_Buttons, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S1_Buttons, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    Set_border_style(guider_ui.ui_S1_Buttons);

    // guider_ui.ui_BTN_Messages

    guider_ui.ui_BTN_Messages = lv_obj_create(guider_ui.ui_S1_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Messages, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Messages, 80);




    lv_obj_set_x(guider_ui.ui_BTN_Messages, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Messages, 90);

    lv_obj_set_align(guider_ui.ui_BTN_Messages, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Messages, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

  //  lv_obj_add_event_cb(guider_ui.ui_BTN_Messages, ui_event_BTN_Messages, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Messages, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Messages, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_BTN_Messages);

    // guider_ui.ui_BTN_Sport

    guider_ui.ui_BTN_Sport = lv_obj_create(guider_ui.ui_S1_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Sport, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Sport, 80);

    lv_obj_set_x(guider_ui.ui_BTN_Sport, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Sport, -90);

    lv_obj_set_align(guider_ui.ui_BTN_Sport, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Sport, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

  //  lv_obj_add_event_cb(guider_ui.ui_BTN_Sport, ui_event_BTN_Sport, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Sport, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Sport, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_BTN_Sport);

    // guider_ui.ui_Panel_Menu1

    guider_ui.ui_Panel_Menu1 = lv_obj_create(guider_ui.ui_S1_Watch_Digital);

    lv_obj_set_width(guider_ui.ui_Panel_Menu1, 33);
    lv_obj_set_height(guider_ui.ui_Panel_Menu1, 124);

    lv_obj_set_x(guider_ui.ui_Panel_Menu1, 0);
    lv_obj_set_y(guider_ui.ui_Panel_Menu1, 0);

    lv_obj_set_align(guider_ui.ui_Panel_Menu1, LV_ALIGN_RIGHT_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Menu1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Menu1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Menu1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_outline_opa(guider_ui.ui_Panel_Menu1,0, LV_PART_MAIN);
    Set_border_style(guider_ui.ui_Panel_Menu1);

    lv_obj_set_style_bg_img_src(guider_ui.ui_Panel_Menu1, &ui_img_img_menu_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Menu_Knob1

    guider_ui.ui_Menu_Knob1 = lv_obj_create(guider_ui.ui_Panel_Menu1);

    lv_obj_set_width(guider_ui.ui_Menu_Knob1, 8);
    lv_obj_set_height(guider_ui.ui_Menu_Knob1, 8);

    lv_obj_set_x(guider_ui.ui_Menu_Knob1, -3);
    lv_obj_set_y(guider_ui.ui_Menu_Knob1, -48);

    lv_obj_set_align(guider_ui.ui_Menu_Knob1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Menu_Knob1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(guider_ui.ui_Menu_Knob1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);


  //Anim Clock
		lv_timer_create(screen_digital_clock_1_timer, 1000, NULL);


}
void ui_S5_Weather_screen_init(void)
{

    // guider_ui.ui_S5_Weather

    guider_ui.ui_S5_Weather = lv_obj_create(NULL);

    lv_obj_clear_flag(guider_ui.ui_S5_Weather, LV_OBJ_FLAG_SCROLLABLE);

   // lv_obj_add_event_cb(guider_ui.ui_S5_Weather, ui_event_S5_Weather, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_S5_Weather, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S5_Weather, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Cloud_Bg1

    guider_ui.ui_Image_Cloud_Bg1 = lv_img_create(guider_ui.ui_S5_Weather);
    lv_img_set_src(guider_ui.ui_Image_Cloud_Bg1, &ui_img_img_cloud_png);

    lv_obj_set_width(guider_ui.ui_Image_Cloud_Bg1, 1192);
    lv_obj_set_height(guider_ui.ui_Image_Cloud_Bg1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Cloud_Bg1, 0);
    lv_obj_set_y(guider_ui.ui_Image_Cloud_Bg1, 0);

    lv_obj_add_flag(guider_ui.ui_Image_Cloud_Bg1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Cloud_Bg1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Cloud_Bg1, 0, 0);
    Set_border_style(guider_ui.ui_Image_Cloud_Bg1);
    // guider_ui.ui_Image_Cloud_Bg12

    guider_ui.ui_Image_Cloud_Bg12 = lv_img_create(guider_ui.ui_S5_Weather);
    lv_img_set_src(guider_ui.ui_Image_Cloud_Bg12, &_img_cloud_2_586x147);

    lv_obj_set_width(guider_ui.ui_Image_Cloud_Bg12, 1192);
    lv_obj_set_height(guider_ui.ui_Image_Cloud_Bg12, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Cloud_Bg12, 0);
    lv_obj_set_y(guider_ui.ui_Image_Cloud_Bg12, 245);

    lv_obj_add_flag(guider_ui.ui_Image_Cloud_Bg12, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Cloud_Bg12, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Cloud_Bg12, 0, 0);
    Set_border_style(guider_ui.ui_Image_Cloud_Bg12);
    // guider_ui.ui_Image_Sun

    guider_ui.ui_Image_Sun = lv_img_create(guider_ui.ui_S5_Weather);
    lv_img_set_src(guider_ui.ui_Image_Sun, &ui_img_img_sun_png);

    lv_obj_set_width(guider_ui.ui_Image_Sun, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Sun, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Sun, 0);
    lv_obj_set_y(guider_ui.ui_Image_Sun, 0);

    lv_obj_add_flag(guider_ui.ui_Image_Sun, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Sun, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Sun, 0, 0);

    lv_obj_set_style_blend_mode(guider_ui.ui_Image_Sun, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Anim_Down_S5

    guider_ui.ui_Anim_Down_S5 = lv_obj_create(guider_ui.ui_S5_Weather);

    lv_obj_set_width(guider_ui.ui_Anim_Down_S5, 392);
    lv_obj_set_height(guider_ui.ui_Anim_Down_S5, 395);

    lv_obj_set_x(guider_ui.ui_Anim_Down_S5, 0);
    lv_obj_set_y(guider_ui.ui_Anim_Down_S5, 0);

    lv_obj_set_align(guider_ui.ui_Anim_Down_S5, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_Down_S5, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_Down_S5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_Down_S5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_Down_S5);
    // guider_ui.ui_Label_Call_Name6

    guider_ui.ui_Label_Call_Name6 = lv_label_create(guider_ui.ui_Anim_Down_S5);

    lv_obj_set_width(guider_ui.ui_Label_Call_Name6, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Call_Name6, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Call_Name6, 0);
    lv_obj_set_y(guider_ui.ui_Label_Call_Name6, 45);

    lv_obj_set_align(guider_ui.ui_Label_Call_Name6, LV_ALIGN_TOP_MID);

    lv_label_set_text(guider_ui.ui_Label_Call_Name6, "New York");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Call_Name6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Call_Name6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Call_Name6, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Anim_On_S5

    guider_ui.ui_Anim_On_S5 = lv_obj_create(guider_ui.ui_S5_Weather);

    lv_obj_set_width(guider_ui.ui_Anim_On_S5, 392);
    lv_obj_set_height(guider_ui.ui_Anim_On_S5, 395);

    lv_obj_set_x(guider_ui.ui_Anim_On_S5, 0);
    lv_obj_set_y(guider_ui.ui_Anim_On_S5, 0);

    lv_obj_set_align(guider_ui.ui_Anim_On_S5, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_On_S5, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_On_S5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_On_S5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_On_S5);

    // guider_ui.ui_Image_Label_Home2

    guider_ui.ui_Image_Label_Home2 = lv_img_create(guider_ui.ui_Anim_On_S5);
    lv_img_set_src(guider_ui.ui_Image_Label_Home2, &ui_img_text_home_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Home2, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Home2, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Home2, 154);
    lv_obj_set_y(guider_ui.ui_Image_Label_Home2, 97);

    lv_obj_set_align(guider_ui.ui_Image_Label_Home2, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Home2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Home2, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Home2, 0, 0);

    // guider_ui.ui_Image_Label_Select1

    guider_ui.ui_Image_Label_Select1 = lv_img_create(guider_ui.ui_Anim_On_S5);
    lv_img_set_src(guider_ui.ui_Image_Label_Select1, &ui_img_text_select_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Select1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Select1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Select1, 152);
    lv_obj_set_y(guider_ui.ui_Image_Label_Select1, -94);

    lv_obj_set_align(guider_ui.ui_Image_Label_Select1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Select1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Select1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Select1, 0, 0);

    // guider_ui.ui_Label_Deg

    guider_ui.ui_Label_Deg = lv_label_create(guider_ui.ui_Anim_On_S5);

    lv_obj_set_width(guider_ui.ui_Label_Deg, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Deg, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Deg, 9);
    lv_obj_set_y(guider_ui.ui_Label_Deg, -44);

    lv_obj_set_align(guider_ui.ui_Label_Deg, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Deg, "23°");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Deg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Deg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Deg, &ui_font_number_light, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Anim_Up_S5

    guider_ui.ui_Anim_Up_S5 = lv_obj_create(guider_ui.ui_S5_Weather);

    lv_obj_set_width(guider_ui.ui_Anim_Up_S5, 392);
    lv_obj_set_height(guider_ui.ui_Anim_Up_S5, 395);

    lv_obj_set_x(guider_ui.ui_Anim_Up_S5, 0);
    lv_obj_set_y(guider_ui.ui_Anim_Up_S5, 0);

    lv_obj_set_align(guider_ui.ui_Anim_Up_S5, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_Up_S5, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_Up_S5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_Up_S5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_Up_S5);

    // guider_ui.ui_Image_Weather_Icon

    guider_ui.ui_Image_Weather_Icon = lv_img_create(guider_ui.ui_Anim_Up_S5);
    lv_img_set_src(guider_ui.ui_Image_Weather_Icon, &ui_img_icn_big_weather_cloud_png);

    lv_obj_set_width(guider_ui.ui_Image_Weather_Icon, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Weather_Icon, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Weather_Icon, 0);
    lv_obj_set_y(guider_ui.ui_Image_Weather_Icon, -109);

    lv_obj_set_align(guider_ui.ui_Image_Weather_Icon, LV_ALIGN_BOTTOM_MID);

    lv_obj_add_flag(guider_ui.ui_Image_Weather_Icon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Weather_Icon, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Weather_Icon, 0, 0);

    // guider_ui.ui_Label_Mostly

    guider_ui.ui_Label_Mostly = lv_label_create(guider_ui.ui_Anim_Up_S5);

    lv_obj_set_width(guider_ui.ui_Label_Mostly, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Mostly, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Mostly, 0);
    lv_obj_set_y(guider_ui.ui_Label_Mostly, -65);

    lv_obj_set_align(guider_ui.ui_Label_Mostly, LV_ALIGN_BOTTOM_MID);

   // lv_label_set_text(guider_ui.ui_Label_Mostly, "Mostly sunny\nMax: 28° Min: 21°");
    lv_label_set_text(guider_ui.ui_Label_Mostly, "Mostly sunny");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Mostly, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Mostly, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_Mostly, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Mostly, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

//    Label Max

    guider_ui.ui_Label_Max = lv_label_create(guider_ui.ui_Anim_Up_S5);

     lv_obj_set_width(guider_ui.ui_Label_Max, LV_SIZE_CONTENT);
     lv_obj_set_height(guider_ui.ui_Label_Max, LV_SIZE_CONTENT);

     lv_obj_set_x(guider_ui.ui_Label_Max, 0);
     lv_obj_set_y(guider_ui.ui_Label_Max, -45);

     lv_obj_set_align(guider_ui.ui_Label_Max, LV_ALIGN_BOTTOM_MID);

     lv_label_set_text(guider_ui.ui_Label_Max, "\nMax:     °  Min:    °");

     lv_obj_set_style_text_color(guider_ui.ui_Label_Max, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(guider_ui.ui_Label_Max, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_align(guider_ui.ui_Label_Max, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_font(guider_ui.ui_Label_Max, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);


    //LabelMax_Number
    guider_ui.ui_Label_Max_Number = lv_label_create(guider_ui.ui_Anim_Up_S5);

     lv_obj_set_width(guider_ui.ui_Label_Max_Number, LV_SIZE_CONTENT);
     lv_obj_set_height(guider_ui.ui_Label_Max_Number, LV_SIZE_CONTENT);

     lv_obj_set_x(guider_ui.ui_Label_Max_Number, -20);
     lv_obj_set_y(guider_ui.ui_Label_Max_Number, -45);

     lv_obj_set_align(guider_ui.ui_Label_Max_Number, LV_ALIGN_BOTTOM_MID);

    // lv_label_set_text(guider_ui.ui_Label_Mostly, "Mostly sunny\nMax: 28° Min: 21°");
     lv_label_set_text(guider_ui.ui_Label_Max_Number, "28");

     lv_obj_set_style_text_color(guider_ui.ui_Label_Max_Number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(guider_ui.ui_Label_Max_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_align(guider_ui.ui_Label_Max_Number, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_font(guider_ui.ui_Label_Max_Number, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

//     //LabelMin_Number
     guider_ui.ui_Label_Min_Number = lv_label_create(guider_ui.ui_Anim_Up_S5);

      lv_obj_set_width(guider_ui.ui_Label_Min_Number, LV_SIZE_CONTENT);
      lv_obj_set_height(guider_ui.ui_Label_Min_Number, LV_SIZE_CONTENT);

      lv_obj_set_x(guider_ui.ui_Label_Min_Number, 65);
      lv_obj_set_y(guider_ui.ui_Label_Min_Number, -45);

      lv_obj_set_align(guider_ui.ui_Label_Min_Number, LV_ALIGN_BOTTOM_MID);

      lv_label_set_text(guider_ui.ui_Label_Min_Number, "21");

      lv_obj_set_style_text_color(guider_ui.ui_Label_Min_Number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_opa(guider_ui.ui_Label_Min_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_align(guider_ui.ui_Label_Min_Number, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(guider_ui.ui_Label_Min_Number, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_S5_Buttons

    guider_ui.ui_S5_Buttons = lv_obj_create(guider_ui.ui_S5_Weather);

    lv_obj_set_width(guider_ui.ui_S5_Buttons, 392);
    lv_obj_set_height(guider_ui.ui_S5_Buttons, 392);

    lv_obj_set_x(guider_ui.ui_S5_Buttons, 0);
    lv_obj_set_y(guider_ui.ui_S5_Buttons, 0);

    lv_obj_set_align(guider_ui.ui_S5_Buttons, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_S5_Buttons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_S5_Buttons, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S5_Buttons, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_S5_Buttons);

    // guider_ui.ui_BTN_Home1

    guider_ui.ui_BTN_Home1 = lv_obj_create(guider_ui.ui_S5_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Home1, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Home1, 80);

    lv_obj_set_x(guider_ui.ui_BTN_Home1, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Home1, 90);

    lv_obj_set_align(guider_ui.ui_BTN_Home1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Home1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);
    Set_border_style(guider_ui.ui_BTN_Home1);

    //lv_obj_add_event_cb(guider_ui.ui_BTN_Home1, ui_event_BTN_Home1, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Home1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Home1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_BTN_Select1

    guider_ui.ui_BTN_Select1 = lv_obj_create(guider_ui.ui_S5_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Select1, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Select1, 80);

    lv_obj_set_x(guider_ui.ui_BTN_Select1, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Select1, -90);

    lv_obj_set_align(guider_ui.ui_BTN_Select1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Select1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Select1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Select1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_BTN_Select1);

    // guider_ui.ui_Panel_Menu3

    guider_ui.ui_Panel_Menu3 = lv_obj_create(guider_ui.ui_S5_Weather);

    lv_obj_set_width(guider_ui.ui_Panel_Menu3, 33);
    lv_obj_set_height(guider_ui.ui_Panel_Menu3, 124);

    lv_obj_set_x(guider_ui.ui_Panel_Menu3, 0);
    lv_obj_set_y(guider_ui.ui_Panel_Menu3, 0);

    lv_obj_set_align(guider_ui.ui_Panel_Menu3, LV_ALIGN_RIGHT_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Menu3, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Menu3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Menu3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Menu3);

    lv_obj_set_style_bg_img_src(guider_ui.ui_Panel_Menu3, &ui_img_img_menu_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Menu_Knob3

    guider_ui.ui_Menu_Knob3 = lv_obj_create(guider_ui.ui_Panel_Menu3);

    lv_obj_set_width(guider_ui.ui_Menu_Knob3, 8);
    lv_obj_set_height(guider_ui.ui_Menu_Knob3, 8);

    lv_obj_set_x(guider_ui.ui_Menu_Knob3, 0);
    lv_obj_set_y(guider_ui.ui_Menu_Knob3, -37);

    lv_obj_set_align(guider_ui.ui_Menu_Knob3, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Menu_Knob3, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(guider_ui.ui_Menu_Knob3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_S9_Sport_screen_init(void)
{

    // guider_ui.ui_S9_Sport

    guider_ui.ui_S9_Sport = lv_obj_create(NULL);

    lv_obj_clear_flag(guider_ui.ui_S9_Sport, LV_OBJ_FLAG_SCROLLABLE);

   // lv_obj_add_event_cb(guider_ui.ui_S9_Sport, ui_event_S9_Sport, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_S9_Sport, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S9_Sport, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Bg7

    guider_ui.ui_Image_Bg7 = lv_img_create(guider_ui.ui_S9_Sport);
    lv_img_set_src(guider_ui.ui_Image_Bg7, &ui_img_img_bg_2_png);

    lv_obj_set_width(guider_ui.ui_Image_Bg7, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Bg7, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Bg7, 0);
    lv_obj_set_y(guider_ui.ui_Image_Bg7, 0);

    lv_obj_set_align(guider_ui.ui_Image_Bg7, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Bg7, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Bg7, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Bg7, 0, 0);
    Set_border_style(guider_ui.ui_Image_Bg7);
    // guider_ui.ui_Anim_Right_S9

    guider_ui.ui_Anim_Right_S9 = lv_obj_create(guider_ui.ui_S9_Sport);

    lv_obj_set_width(guider_ui.ui_Anim_Right_S9, 392);
    lv_obj_set_height(guider_ui.ui_Anim_Right_S9, 395);

    lv_obj_set_x(guider_ui.ui_Anim_Right_S9, 0);
    lv_obj_set_y(guider_ui.ui_Anim_Right_S9, 0);

    lv_obj_set_align(guider_ui.ui_Anim_Right_S9, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_Right_S9, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_Right_S9, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_Right_S9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_Right_S9);

    // guider_ui.ui_Panel_Fitness_Pulse

    guider_ui.ui_Panel_Fitness_Pulse = lv_obj_create(guider_ui.ui_Anim_Right_S9);

    lv_obj_set_width(guider_ui.ui_Panel_Fitness_Pulse, 140);
    lv_obj_set_height(guider_ui.ui_Panel_Fitness_Pulse, 82);

    lv_obj_set_x(guider_ui.ui_Panel_Fitness_Pulse, -40);
    lv_obj_set_y(guider_ui.ui_Panel_Fitness_Pulse, 65);

    lv_obj_set_align(guider_ui.ui_Panel_Fitness_Pulse, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(guider_ui.ui_Panel_Fitness_Pulse, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Fitness_Pulse, lv_color_hex(0x080C08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Fitness_Pulse, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Fitness_Pulse);

    // guider_ui.ui_Label_Pulse

    guider_ui.ui_Label_Pulse = lv_label_create(guider_ui.ui_Panel_Fitness_Pulse);

    lv_obj_set_width(guider_ui.ui_Label_Pulse, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Pulse, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Pulse, 35);
    lv_obj_set_y(guider_ui.ui_Label_Pulse, -6);

    lv_label_set_text(guider_ui.ui_Label_Pulse, "PULSE");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Pulse, lv_color_hex(0x949194), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Pulse, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_Pulse, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Pulse, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Pulse_Number

    guider_ui.ui_Label_Pulse_Number = lv_label_create(guider_ui.ui_Panel_Fitness_Pulse);

    lv_obj_set_width(guider_ui.ui_Label_Pulse_Number, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Pulse_Number, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Pulse_Number, 35);
    lv_obj_set_y(guider_ui.ui_Label_Pulse_Number, 0);

    lv_obj_set_align(guider_ui.ui_Label_Pulse_Number, LV_ALIGN_BOTTOM_LEFT);

    lv_label_set_long_mode(guider_ui.ui_Label_Pulse_Number, LV_LABEL_LONG_DOT);
    lv_label_set_text(guider_ui.ui_Label_Pulse_Number, "128");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Pulse_Number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Pulse_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Pulse_Number, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Pulse

    guider_ui.ui_Image_Pulse = lv_img_create(guider_ui.ui_Panel_Fitness_Pulse);
    lv_img_set_src(guider_ui.ui_Image_Pulse, &ui_img_icn_small_pulse_png);

    lv_obj_set_width(guider_ui.ui_Image_Pulse, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Pulse, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Pulse, 0);
    lv_obj_set_y(guider_ui.ui_Image_Pulse, -10);

    lv_obj_set_align(guider_ui.ui_Image_Pulse, LV_ALIGN_BOTTOM_LEFT);

    lv_obj_add_flag(guider_ui.ui_Image_Pulse, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Pulse, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Pulse, 0, 0);

    // guider_uiui_Panel_Fitness_Duration

    guider_ui.ui_Panel_Fitness_Duration = lv_obj_create(guider_ui.ui_Anim_Right_S9);

    lv_obj_set_width(guider_ui.ui_Panel_Fitness_Duration, 140);
    lv_obj_set_height(guider_ui.ui_Panel_Fitness_Duration, 82);

    lv_obj_set_x(guider_ui.ui_Panel_Fitness_Duration, -40);
    lv_obj_set_y(guider_ui.ui_Panel_Fitness_Duration, 135);

    lv_obj_set_align(guider_ui.ui_Panel_Fitness_Duration, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(guider_ui.ui_Panel_Fitness_Duration, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Fitness_Duration, lv_color_hex(0x080C08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Fitness_Duration, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Fitness_Duration);

    // guider_ui.ui_Label_Duration

    guider_ui.ui_Label_Duration = lv_label_create(guider_ui.ui_Panel_Fitness_Duration);

    lv_obj_set_width(guider_ui.ui_Label_Duration, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Duration, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Duration, 35);
    lv_obj_set_y(guider_ui.ui_Label_Duration, -6);

    lv_label_set_text(guider_ui.ui_Label_Duration, "DURATION");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Duration, lv_color_hex(0x949194), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Duration, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_Duration, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Duration, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Duration_Number

    guider_ui.ui_Label_Duration_Number = lv_label_create(guider_ui.ui_Panel_Fitness_Duration);

    lv_obj_set_width(guider_ui.ui_Label_Duration_Number, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Duration_Number, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Duration_Number, 35);
    lv_obj_set_y(guider_ui.ui_Label_Duration_Number, 0);

    lv_obj_set_align(guider_ui.ui_Label_Duration_Number, LV_ALIGN_BOTTOM_LEFT);

    lv_label_set_long_mode(guider_ui.ui_Label_Duration_Number, LV_LABEL_LONG_DOT);
    lv_label_set_text(guider_ui.ui_Label_Duration_Number, "02:53");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Duration_Number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Duration_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Duration_Number, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Duration

    guider_ui.ui_Image_Duration = lv_img_create(guider_ui.ui_Panel_Fitness_Duration);
    lv_img_set_src(guider_ui.ui_Image_Duration, &ui_img_icn_small_time_png);

    lv_obj_set_width(guider_ui.ui_Image_Duration, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Duration, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Duration, 0);
    lv_obj_set_y(guider_ui.ui_Image_Duration, -10);

    lv_obj_set_align(guider_ui.ui_Image_Duration, LV_ALIGN_BOTTOM_LEFT);

    lv_obj_add_flag(guider_ui.ui_Image_Duration, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Duration, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Duration, 0, 0);

    // guider_ui.ui_Panel_Fitness_Distance

    guider_ui.ui_Panel_Fitness_Distance = lv_obj_create(guider_ui.ui_Anim_Right_S9);

    lv_obj_set_width(guider_ui.ui_Panel_Fitness_Distance, 140);
    lv_obj_set_height(guider_ui.ui_Panel_Fitness_Distance, 80);

    lv_obj_set_x(guider_ui.ui_Panel_Fitness_Distance, -40);
    lv_obj_set_y(guider_ui.ui_Panel_Fitness_Distance, 205);

    lv_obj_set_align(guider_ui.ui_Panel_Fitness_Distance, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(guider_ui.ui_Panel_Fitness_Distance, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Fitness_Distance, lv_color_hex(0x080C08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Fitness_Distance, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Fitness_Distance);

    // guider_ui.ui_Label_Distance

    guider_ui.ui_Label_Distance = lv_label_create(guider_ui.ui_Panel_Fitness_Distance);

    lv_obj_set_width(guider_ui.ui_Label_Distance, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Distance, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Distance, 35);
    lv_obj_set_y(guider_ui.ui_Label_Distance, -6);

    lv_label_set_text(guider_ui.ui_Label_Distance, "DISTANCE");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Distance, lv_color_hex(0x949194), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Distance, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_Distance, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Distance, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Distance_Number

    guider_ui.ui_Label_Distance_Number = lv_label_create(guider_ui.ui_Panel_Fitness_Distance);

    lv_obj_set_width(guider_ui.ui_Label_Distance_Number, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Distance_Number, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Distance_Number, 35);
    lv_obj_set_y(guider_ui.ui_Label_Distance_Number, 0);

    lv_obj_set_align(guider_ui.ui_Label_Distance_Number, LV_ALIGN_BOTTOM_LEFT);

    lv_label_set_long_mode(guider_ui.ui_Label_Distance_Number, LV_LABEL_LONG_DOT);
    lv_label_set_text(guider_ui.ui_Label_Distance_Number, "02:53");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Distance_Number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Distance_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Distance_Number, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Distance

    guider_ui.ui_Image_Distance = lv_img_create(guider_ui.ui_Panel_Fitness_Distance);
    lv_img_set_src(guider_ui.ui_Image_Distance, &ui_img_icn_small_pos_png);

    lv_obj_set_width(guider_ui.ui_Image_Distance, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Distance, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Distance, 0);
    lv_obj_set_y(guider_ui.ui_Image_Distance, -10);

    lv_obj_set_align(guider_ui.ui_Image_Distance, LV_ALIGN_BOTTOM_LEFT);

    lv_obj_add_flag(guider_ui.ui_Image_Distance, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Distance, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Distance, 0, 0);

    // guider_ui.ui_Panel_Fitness_Calorie

    guider_ui.ui_Panel_Fitness_Calorie = lv_obj_create(guider_ui.ui_Anim_Right_S9);

    lv_obj_set_width(guider_ui.ui_Panel_Fitness_Calorie, 140);
    lv_obj_set_height(guider_ui.ui_Panel_Fitness_Calorie, 80);

    lv_obj_set_x(guider_ui.ui_Panel_Fitness_Calorie, -40);
    lv_obj_set_y(guider_ui.ui_Panel_Fitness_Calorie, 280);

    lv_obj_set_align(guider_ui.ui_Panel_Fitness_Calorie, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(guider_ui.ui_Panel_Fitness_Calorie, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Fitness_Calorie, lv_color_hex(0x080C08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Fitness_Calorie, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Fitness_Calorie);

    // guider_ui.ui_Label_Calorie

    guider_ui.ui_Label_Calorie = lv_label_create(guider_ui.ui_Panel_Fitness_Calorie);

    lv_obj_set_width(guider_ui.ui_Label_Calorie, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Calorie, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Calorie, 35);
    lv_obj_set_y(guider_ui.ui_Label_Calorie, -6);

    lv_label_set_text(guider_ui.ui_Label_Calorie, "CALORIE");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Calorie, lv_color_hex(0x949194), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Calorie, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_Calorie, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Calorie, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Calorie_Number

    guider_ui.ui_Label_Calorie_Number = lv_label_create(guider_ui.ui_Panel_Fitness_Calorie);

    lv_obj_set_width(guider_ui.ui_Label_Calorie_Number, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Calorie_Number, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Calorie_Number, 35);
    lv_obj_set_y(guider_ui.ui_Label_Calorie_Number, 0);

    lv_obj_set_align(guider_ui.ui_Label_Calorie_Number, LV_ALIGN_BOTTOM_LEFT);

    lv_label_set_long_mode(guider_ui.ui_Label_Calorie_Number, LV_LABEL_LONG_DOT);
    lv_label_set_text(guider_ui.ui_Label_Calorie_Number, "355");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Calorie_Number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Calorie_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Calorie_Number, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Calorie

    guider_ui.ui_Image_Calorie = lv_img_create(guider_ui.ui_Panel_Fitness_Calorie);
    lv_img_set_src(guider_ui.ui_Image_Calorie, &ui_img_icn_small_burn_png);

    lv_obj_set_width(guider_ui.ui_Image_Calorie, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Calorie, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Calorie, 0);
    lv_obj_set_y(guider_ui.ui_Image_Calorie, -10);

    lv_obj_set_align(guider_ui.ui_Image_Calorie, LV_ALIGN_BOTTOM_LEFT);

    lv_obj_add_flag(guider_ui.ui_Image_Calorie, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Calorie, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Calorie, 0, 0);

    // guider_ui.ui_Header_S9

    guider_ui.ui_Header_S9 = lv_obj_create(guider_ui.ui_S9_Sport);

    lv_obj_set_width(guider_ui.ui_Header_S9, 392);
    lv_obj_set_height(guider_ui.ui_Header_S9, 128);

    lv_obj_set_x(guider_ui.ui_Header_S9, 0);
    lv_obj_set_y(guider_ui.ui_Header_S9, -10);

    lv_obj_set_align(guider_ui.ui_Header_S9, LV_ALIGN_TOP_MID);

    lv_obj_clear_flag(guider_ui.ui_Header_S9, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Header_S9, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Header_S9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Header_S9);
    // guider_ui.ui_Image_Header_Shadow4

    guider_ui.ui_Image_Header_Shadow4 = lv_img_create(guider_ui.ui_Header_S9);
    lv_img_set_src(guider_ui.ui_Image_Header_Shadow4, &ui_img_img_header_bg_shadow_png);

    lv_obj_set_width(guider_ui.ui_Image_Header_Shadow4, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Header_Shadow4, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Header_Shadow4, 0);
    lv_obj_set_y(guider_ui.ui_Image_Header_Shadow4, -8);

    lv_obj_set_align(guider_ui.ui_Image_Header_Shadow4, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Header_Shadow4, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Header_Shadow4, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Header_Shadow4, 0, 0);

    // guider_ui.ui_Image_Header4

    guider_ui.ui_Image_Header4 = lv_img_create(guider_ui.ui_Header_S9);
    lv_img_set_src(guider_ui.ui_Image_Header4, &ui_img_img_header_bg_png);

    lv_obj_set_width(guider_ui.ui_Image_Header4, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Header4, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Header4, 0);
    lv_obj_set_y(guider_ui.ui_Image_Header4, -27);

    lv_obj_set_align(guider_ui.ui_Image_Header4, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Header4, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Header4, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Header4, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Header4, lv_color_hex(0x109D31), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Header4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Fitness

    guider_ui.ui_Label_Fitness = lv_label_create(guider_ui.ui_Header_S9);

    lv_obj_set_width(guider_ui.ui_Label_Fitness, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Fitness, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Fitness, 0);
    lv_obj_set_y(guider_ui.ui_Label_Fitness, -20);

    lv_obj_set_align(guider_ui.ui_Label_Fitness, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Fitness, "Fitness");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Fitness, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Fitness, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Fitness, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Label_Home6

    guider_ui.ui_Image_Label_Home6 = lv_img_create(guider_ui.ui_S9_Sport);
    lv_img_set_src(guider_ui.ui_Image_Label_Home6, &ui_img_text_home_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Home6, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Home6, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Home6, 154);
    lv_obj_set_y(guider_ui.ui_Image_Label_Home6, 97);

    lv_obj_set_align(guider_ui.ui_Image_Label_Home6, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Home6, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Home6, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Home6, 0, 0);

    // guider_ui.ui_Image_Label_Start

    guider_ui.ui_Image_Label_Start = lv_img_create(guider_ui.ui_S9_Sport);
    lv_img_set_src(guider_ui.ui_Image_Label_Start, &ui_img_text_start_stop_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Start, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Start, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Start, 157);
    lv_obj_set_y(guider_ui.ui_Image_Label_Start, -90);

    lv_obj_set_align(guider_ui.ui_Image_Label_Start, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Start, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Start, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Start, 0, 0);

    // guider_ui.ui_Anim_On_S9

    guider_ui.ui_Anim_On_S9 = lv_obj_create(guider_ui.ui_S9_Sport);

    lv_obj_set_width(guider_ui.ui_Anim_On_S9, 392);
    lv_obj_set_height(guider_ui.ui_Anim_On_S9, 392);

    lv_obj_set_x(guider_ui.ui_Anim_On_S9, 0);
    lv_obj_set_y(guider_ui.ui_Anim_On_S9, 0);

    lv_obj_set_align(guider_ui.ui_Anim_On_S9, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_On_S9, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_On_S9, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_On_S9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_On_S9);

    // guider_ui.ui_Arc_Calorie

    guider_ui.ui_Arc_Calorie = lv_arc_create(guider_ui.ui_Anim_On_S9);

    lv_obj_set_width(guider_ui.ui_Arc_Calorie, 370);
    lv_obj_set_height(guider_ui.ui_Arc_Calorie, 370);

    lv_obj_set_x(guider_ui.ui_Arc_Calorie, 0);
    lv_obj_set_y(guider_ui.ui_Arc_Calorie, 0);

    lv_obj_set_align(guider_ui.ui_Arc_Calorie, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Arc_Calorie, LV_OBJ_FLAG_CLICKABLE);

    lv_arc_set_range(guider_ui.ui_Arc_Calorie, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Calorie, 40);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Calorie, 95, 220);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Calorie, lv_color_hex(0x202420), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Calorie, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Calorie, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Calorie, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Calorie, lv_color_hex(0xEEC200), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Calorie, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Calorie, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Calorie, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Calorie, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Calorie, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // guider_ui.ui_Arc_Distance

    guider_ui.ui_Arc_Distance = lv_arc_create(guider_ui.ui_Anim_On_S9);

    lv_obj_set_width(guider_ui.ui_Arc_Distance, 308);
    lv_obj_set_height(guider_ui.ui_Arc_Distance, 308);

    lv_obj_set_x(guider_ui.ui_Arc_Distance, 0);
    lv_obj_set_y(guider_ui.ui_Arc_Distance, 0);

    lv_obj_set_align(guider_ui.ui_Arc_Distance, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Arc_Distance, LV_OBJ_FLAG_CLICKABLE);

    lv_arc_set_range(guider_ui.ui_Arc_Distance, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Distance, 80);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Distance, 95, 220);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Distance, lv_color_hex(0x202420), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Distance, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Distance, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Distance, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Distance, lv_color_hex(0x00CE10), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Distance, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Distance, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Distance, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Distance, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Distance, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // guider_ui.ui_Arc_Duration

    guider_ui.ui_Arc_Duration = lv_arc_create(guider_ui.ui_Anim_On_S9);

    lv_obj_set_width(guider_ui.ui_Arc_Duration, 246);
    lv_obj_set_height(guider_ui.ui_Arc_Duration, 246);

    lv_obj_set_x(guider_ui.ui_Arc_Duration, 0);
    lv_obj_set_y(guider_ui.ui_Arc_Duration, 0);

    lv_obj_set_align(guider_ui.ui_Arc_Duration, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Arc_Duration, LV_OBJ_FLAG_CLICKABLE);

    lv_arc_set_range(guider_ui.ui_Arc_Duration, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Duration, 50);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Duration, 95, 220);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Duration, lv_color_hex(0x202420), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Duration, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Duration, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Duration, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Duration, lv_color_hex(0x00A1FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Duration, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Duration, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Duration, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Duration, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Duration, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // guider_ui.ui_Arc_Pusle

    guider_ui.ui_Arc_Pusle = lv_arc_create(guider_ui.ui_Anim_On_S9);

    lv_obj_set_width(guider_ui.ui_Arc_Pusle, 185);
    lv_obj_set_height(guider_ui.ui_Arc_Pusle, 185);

    lv_obj_set_x(guider_ui.ui_Arc_Pusle, 0);
    lv_obj_set_y(guider_ui.ui_Arc_Pusle, 0);

    lv_obj_set_align(guider_ui.ui_Arc_Pusle, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Arc_Pusle, LV_OBJ_FLAG_CLICKABLE);

    lv_arc_set_range(guider_ui.ui_Arc_Pusle, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Pusle, 70);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Pusle, 95, 220);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Pusle, lv_color_hex(0x202420), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Pusle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Pusle, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Pusle, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Pusle, lv_color_hex(0xF30C76), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Pusle, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Pusle, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Pusle, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Pusle, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Pusle, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // guider_ui.ui_S9_Buttons

    guider_ui.ui_S9_Buttons = lv_obj_create(guider_ui.ui_S9_Sport);

    lv_obj_set_width(guider_ui.ui_S9_Buttons, 392);
    lv_obj_set_height(guider_ui.ui_S9_Buttons, 392);

    lv_obj_set_x(guider_ui.ui_S9_Buttons, 0);
    lv_obj_set_y(guider_ui.ui_S9_Buttons, 0);

    lv_obj_set_align(guider_ui.ui_S9_Buttons, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_S9_Buttons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_S9_Buttons, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S9_Buttons, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_S9_Buttons);
    // guider_ui.ui_BTN_Home5

    guider_ui.ui_BTN_Home5 = lv_obj_create(guider_ui.ui_S9_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Home5, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Home5, 80);

    lv_obj_set_x(guider_ui.ui_BTN_Home5, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Home5, 90);

    lv_obj_set_align(guider_ui.ui_BTN_Home5, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Home5, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

    //lv_obj_add_event_cb(guider_ui.ui_BTN_Home5, ui_event_BTN_Home5, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Home5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Home5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_BTN_Home5);

    // guider_ui.ui_BTN_StartStop

    guider_ui.ui_BTN_StartStop = lv_obj_create(guider_ui.ui_S9_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_StartStop, 80);
    lv_obj_set_height(guider_ui.ui_BTN_StartStop, 80);

    lv_obj_set_x(guider_ui.ui_BTN_StartStop, 130);
    lv_obj_set_y(guider_ui.ui_BTN_StartStop, -90);

    lv_obj_set_align(guider_ui.ui_BTN_StartStop, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_StartStop, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_BTN_StartStop, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_StartStop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_BTN_StartStop);
    // guider_ui.ui_Panel_Menu4

    guider_ui.ui_Panel_Menu4 = lv_obj_create(guider_ui.ui_S9_Sport);

    lv_obj_set_width(guider_ui.ui_Panel_Menu4, 33);
    lv_obj_set_height(guider_ui.ui_Panel_Menu4, 124);

    lv_obj_set_x(guider_ui.ui_Panel_Menu4, 0);
    lv_obj_set_y(guider_ui.ui_Panel_Menu4, 0);

    lv_obj_set_align(guider_ui.ui_Panel_Menu4, LV_ALIGN_RIGHT_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Menu4, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Menu4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Menu4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    static lv_style_t style_NoBorderPanel4;
           lv_style_init(&style_NoBorderPanel4);

           lv_style_set_border_width(&style_NoBorderPanel4, 0);
           lv_obj_add_style(guider_ui.ui_Panel_Menu4, &style_NoBorderPanel4, LV_PART_MAIN|LV_STATE_DEFAULT);
           lv_obj_set_style_bg_img_src(guider_ui.ui_Panel_Menu4, &style_NoBorderPanel4, LV_PART_MAIN | LV_STATE_DEFAULT);
           lv_obj_set_style_bg_img_src(guider_ui.ui_Panel_Menu4, &ui_img_img_menu_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    // guider_ui.ui_Menu_Knob4

    guider_ui.ui_Menu_Knob4 = lv_obj_create(guider_ui.ui_Panel_Menu4);

    lv_obj_set_width(guider_ui.ui_Menu_Knob4, 8);
    lv_obj_set_height(guider_ui.ui_Menu_Knob4, 8);

    lv_obj_set_x(guider_ui.ui_Menu_Knob4, 2);
    lv_obj_set_y(guider_ui.ui_Menu_Knob4, -24);

    lv_obj_set_align(guider_ui.ui_Menu_Knob4, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Menu_Knob4, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(guider_ui.ui_Menu_Knob4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_S11_Music_screen_init(void)
{

    // guider_ui.ui_S11_Music

    guider_ui.ui_S11_Music = lv_obj_create(NULL);

    lv_obj_clear_flag(guider_ui.ui_S11_Music, LV_OBJ_FLAG_SCROLLABLE);

  //  lv_obj_add_event_cb(guider_ui.ui_S11_Music, ui_event_S11_Music, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_S11_Music, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S11_Music, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Anim_On_S11

    guider_ui.ui_Anim_On_S11 = lv_obj_create(guider_ui.ui_S11_Music);

    lv_obj_set_width(guider_ui.ui_Anim_On_S11, 392);
    lv_obj_set_height(guider_ui.ui_Anim_On_S11, 392);

    lv_obj_set_x(guider_ui.ui_Anim_On_S11, 0);
    lv_obj_set_y(guider_ui.ui_Anim_On_S11, 0);

    lv_obj_set_align(guider_ui.ui_Anim_On_S11, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_On_S11, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_On_S11, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_On_S11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_On_S11);

    // guider_ui.ui_Image_Audio_Album_1

    guider_ui.ui_Image_Audio_Album_1 = lv_img_create(guider_ui.ui_Anim_On_S11);
    lv_img_set_src(guider_ui.ui_Image_Audio_Album_1, &ui_img_img_audio_album_png);

    lv_obj_set_width(guider_ui.ui_Image_Audio_Album_1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Audio_Album_1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Audio_Album_1, 0);
    lv_obj_set_y(guider_ui.ui_Image_Audio_Album_1, 0);

    lv_obj_set_align(guider_ui.ui_Image_Audio_Album_1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Audio_Album_1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Audio_Album_1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Audio_Album_1, 0, 0);
    Set_border_style(guider_ui.ui_Image_Audio_Album_1);

    // guider_ui.ui_Btn_Audio_Play

    guider_ui.ui_Btn_Audio_Play = lv_obj_create(guider_ui.ui_Anim_On_S11);

    lv_obj_set_width(guider_ui.ui_Btn_Audio_Play, 100);
    lv_obj_set_height(guider_ui.ui_Btn_Audio_Play, 100);

    lv_obj_set_x(guider_ui.ui_Btn_Audio_Play, 0);
    lv_obj_set_y(guider_ui.ui_Btn_Audio_Play, 0);

    lv_obj_set_align(guider_ui.ui_Btn_Audio_Play, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Btn_Audio_Play, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_flag(guider_ui.ui_Btn_Audio_Play, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(guider_ui.ui_Btn_Audio_Play, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.ui_Btn_Audio_Play, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Btn_Audio_Play, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(guider_ui.ui_Btn_Audio_Play, &ui_img_icn_audio_play_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(guider_ui.ui_Btn_Audio_Play, &ui_img_img_pause_png, LV_PART_MAIN | LV_STATE_CHECKED);

    // guider_ui.ui_Image_Audio_Back

    guider_ui.ui_Image_Audio_Back = lv_obj_create(guider_ui.ui_Anim_On_S11);

    lv_obj_set_width(guider_ui.ui_Image_Audio_Back, 75);
    lv_obj_set_height(guider_ui.ui_Image_Audio_Back, 75);

    lv_obj_set_x(guider_ui.ui_Image_Audio_Back, -110);
    lv_obj_set_y(guider_ui.ui_Image_Audio_Back, 0);

    lv_obj_set_align(guider_ui.ui_Image_Audio_Back, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Audio_Back, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Audio_Back, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(guider_ui.ui_Image_Audio_Back, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(guider_ui.ui_Image_Audio_Back, 0,LV_PART_MAIN);
  //  lv_img_set_pivot(guider_ui.ui_Image_Audio_Back, 0, 0);
    lv_obj_set_style_bg_img_src(guider_ui.ui_Image_Audio_Back, &ui_img_icn_audio_back_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Audio_Next

     guider_ui.ui_Image_Audio_Next = lv_img_create(guider_ui.ui_Anim_On_S11);
     lv_img_set_src(guider_ui.ui_Image_Audio_Next, &ui_img_icn_audio_next_png);

     lv_obj_set_width(guider_ui.ui_Image_Audio_Next, 17);
     lv_obj_set_height(guider_ui.ui_Image_Audio_Next, 26  );

     lv_obj_set_x(guider_ui.ui_Image_Audio_Next, 110);
     lv_obj_set_y(guider_ui.ui_Image_Audio_Next, 0);
     lv_obj_set_align(guider_ui.ui_Image_Audio_Next, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Audio_Next, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Audio_Next,LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);
    //lv_img_set_pivot(guider_ui.ui_Image_Audio_Next, 0, 0);
    lv_obj_set_style_bg_opa(guider_ui.ui_Image_Audio_Next, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(guider_ui.ui_Image_Audio_Next, 0,LV_PART_MAIN);
   
  
    //guider_ui.ui_Image_Audio_Next_btn
     guider_ui.ui_Image_Audio_Next_btn = lv_obj_create(guider_ui.ui_Anim_On_S11);

     lv_obj_set_width(guider_ui.ui_Image_Audio_Next_btn, 75);
     lv_obj_set_height(guider_ui.ui_Image_Audio_Next_btn, 75  );

     lv_obj_set_x(guider_ui.ui_Image_Audio_Next_btn, 110);
     lv_obj_set_y(guider_ui.ui_Image_Audio_Next_btn, 0);

     lv_obj_set_align(guider_ui.ui_Image_Audio_Next_btn, LV_ALIGN_CENTER);
      
     static lv_style_t style_screen_btn_1_main_main_default;
     lv_style_init(&style_screen_btn_1_main_main_default);
     lv_style_set_radius(&style_screen_btn_1_main_main_default, 0);
     lv_style_set_bg_opa(&style_screen_btn_1_main_main_default, 0);
     lv_style_set_border_opa(&style_screen_btn_1_main_main_default, 0);
     lv_style_set_border_width(&style_screen_btn_1_main_main_default, 0);
     lv_obj_add_style(guider_ui.ui_Image_Audio_Next_btn, &style_screen_btn_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Label_Home_S11

  //  guider_ui.ui_Image_Label_Home_S11 = lv_img_create(guider_ui.ui_Anim_On_S11);
  //   lv_img_set_src(guider_ui.ui_Image_Label_Home_S11, &ui_img_text_home_png);

  //   lv_obj_set_width(guider_ui.ui_Image_Label_Home_S11, LV_SIZE_CONTENT);
  //   lv_obj_set_height(guider_ui.ui_Image_Label_Home_S11, LV_SIZE_CONTENT);

  //   lv_obj_set_x(guider_ui.ui_Image_Label_Home_S11, 154);
  //   lv_obj_set_y(guider_ui.ui_Image_Label_Home_S11, 97);

  //   lv_obj_set_align(guider_ui.ui_Image_Label_Home_S11, LV_ALIGN_CENTER);

  //   lv_obj_add_flag(guider_ui.ui_Image_Label_Home_S11, LV_OBJ_FLAG_ADV_HITTEST);
  //   lv_obj_clear_flag(guider_ui.ui_Image_Label_Home_S11, LV_OBJ_FLAG_SCROLLABLE);

  //   lv_img_set_pivot(guider_ui.ui_Image_Label_Home_S11, 0, 0);

  //   // guider_ui.ui_Image_Home_S11

  //   guider_ui.ui_Image_Home_S11 = lv_img_create(guider_ui.ui_Anim_On_S11);
  //   lv_img_set_src(guider_ui.ui_Image_Home_S11, &ui_img_icn_home_png);

  //   lv_obj_set_width(guider_ui.ui_Image_Home_S11, LV_SIZE_CONTENT);
  //   lv_obj_set_height(guider_ui.ui_Image_Home_S11, LV_SIZE_CONTENT);

  //   lv_obj_set_x(guider_ui.ui_Image_Home_S11, 130);
  //   lv_obj_set_y(guider_ui.ui_Image_Home_S11, 81);

  //   lv_obj_set_align(guider_ui.ui_Image_Home_S11, LV_ALIGN_CENTER);

  //   lv_obj_add_flag(guider_ui.ui_Image_Home_S11, LV_OBJ_FLAG_ADV_HITTEST);
  //   lv_obj_clear_flag(guider_ui.ui_Image_Home_S11, LV_OBJ_FLAG_SCROLLABLE);

  //   lv_img_set_pivot(guider_ui.ui_Image_Home_S11, 0, 0);

  //   // guider_ui.ui_Anim_Down_S11

    guider_ui.ui_Anim_Down_S11 = lv_obj_create(guider_ui.ui_S11_Music);

    lv_obj_set_width(guider_ui.ui_Anim_Down_S11, 392);
    lv_obj_set_height(guider_ui.ui_Anim_Down_S11, 392);

    lv_obj_set_x(guider_ui.ui_Anim_Down_S11, 0);
    lv_obj_set_y(guider_ui.ui_Anim_Down_S11, 0);

    lv_obj_set_align(guider_ui.ui_Anim_Down_S11, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_Down_S11, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_Down_S11, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_Down_S11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_Down_S11);

    // guider_ui.guider_ui.ui_Panel_Audio_Time_Mask

    guider_ui.ui_Panel_Audio_Time_Mask = lv_obj_create(guider_ui.ui_Anim_Down_S11);

    lv_obj_set_width(guider_ui.ui_Panel_Audio_Time_Mask, 392);
    lv_obj_set_height(guider_ui.ui_Panel_Audio_Time_Mask, 392);

    lv_obj_set_x(guider_ui.ui_Panel_Audio_Time_Mask, 0);
    lv_obj_set_y(guider_ui.ui_Panel_Audio_Time_Mask, 0);

    lv_obj_set_align(guider_ui.ui_Panel_Audio_Time_Mask, LV_ALIGN_TOP_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Audio_Time_Mask, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Audio_Time_Mask, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Audio_Time_Mask, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Audio_Time_Mask);

    // guider_ui.ui_Arc_Audio_Time

    guider_ui.ui_Arc_Audio_Time = lv_arc_create(guider_ui.ui_Panel_Audio_Time_Mask);

    lv_obj_set_width(guider_ui.ui_Arc_Audio_Time, 370);
    lv_obj_set_height(guider_ui.ui_Arc_Audio_Time, 370);

    lv_obj_set_x(guider_ui.ui_Arc_Audio_Time, 0);
    lv_obj_set_y(guider_ui.ui_Arc_Audio_Time, -25);

    lv_obj_set_align(guider_ui.ui_Arc_Audio_Time, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(guider_ui.ui_Arc_Audio_Time, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Arc_Audio_Time, LV_OBJ_FLAG_GESTURE_BUBBLE);

    lv_arc_set_range(guider_ui.ui_Arc_Audio_Time, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Audio_Time, 100);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Audio_Time, 160, 320);
   // lv_arc_set_rotation(guider_ui.ui_Arc_Audio_Time, -43);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Audio_Time, lv_color_hex(0x3E3E3E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Audio_Time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Audio_Time, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Audio_Time, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Audio_Time, lv_color_hex(0xC5C5C5), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Audio_Time, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Audio_Time, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Audio_Time, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(guider_ui.ui_Arc_Audio_Time, 7, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Audio_Time, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Audio_Time, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(guider_ui.ui_Arc_Audio_Time, 9, LV_STATE_DEFAULT);
    // Set_border_style(guider_ui.ui_Arc_Audio_Time);
    lv_obj_clear_flag(guider_ui.ui_Arc_Audio_Time, LV_OBJ_FLAG_CLICKABLE);

    // guider_ui.ui_Label_Audio_Arist

    guider_ui.ui_Label_Audio_Arist = lv_label_create(guider_ui.ui_Anim_Down_S11);

    lv_obj_set_width(guider_ui.ui_Label_Audio_Arist, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Audio_Arist, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Audio_Arist, 0);
    lv_obj_set_y(guider_ui.ui_Label_Audio_Arist, 70);

    lv_obj_set_align(guider_ui.ui_Label_Audio_Arist, LV_ALIGN_TOP_MID);

    lv_label_set_text(guider_ui.ui_Label_Audio_Arist, "Erica Smith");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Audio_Arist, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Audio_Arist, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Audio_Arist, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Audio_Title

    guider_ui.ui_Label_Audio_Title = lv_label_create(guider_ui.ui_Anim_Down_S11);

    lv_obj_set_width(guider_ui.ui_Label_Audio_Title, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Audio_Title, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Audio_Title, 1);
    lv_obj_set_y(guider_ui.ui_Label_Audio_Title, 110);

    lv_obj_set_align(guider_ui.ui_Label_Audio_Title, LV_ALIGN_TOP_MID);

    lv_label_set_text(guider_ui.ui_Label_Audio_Title, "Dance on the moon");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Audio_Title, lv_color_hex(0xC5C6C5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Audio_Title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Audio_Title, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Anim_Up_S11

    guider_ui.ui_Anim_Up_S11 = lv_obj_create(guider_ui.ui_S11_Music);

    lv_obj_set_width(guider_ui.ui_Anim_Up_S11, 392);
    lv_obj_set_height(guider_ui.ui_Anim_Up_S11, 392);

    lv_obj_set_x(guider_ui.ui_Anim_Up_S11, 0);
    lv_obj_set_y(guider_ui.ui_Anim_Up_S11, 0);

    lv_obj_set_align(guider_ui.ui_Anim_Up_S11, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_Up_S11, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_Up_S11, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_Up_S11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_Up_S11);

    // guider_ui.ui_Image_Label_Volume1

    guider_ui.ui_Image_Label_Volume1 = lv_img_create(guider_ui.ui_Anim_Up_S11);
    lv_img_set_src(guider_ui.ui_Image_Label_Volume1, &ui_img_text_audio_volume_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Volume1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Volume1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Volume1, -114);
    lv_obj_set_y(guider_ui.ui_Image_Label_Volume1, 108);

    lv_obj_set_align(guider_ui.ui_Image_Label_Volume1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Volume1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Volume1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Volume1, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Label_Volume1, lv_color_hex(0xA0A0A0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Label_Volume1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Panel_Volume_Mask2

    guider_ui.ui_Panel_Volume_Mask2 = lv_obj_create(guider_ui.ui_Anim_Up_S11);

    lv_obj_set_width(guider_ui.ui_Panel_Volume_Mask2, 337);
    lv_obj_set_height(guider_ui.ui_Panel_Volume_Mask2, 168);

    lv_obj_set_x(guider_ui.ui_Panel_Volume_Mask2, -30);
    lv_obj_set_y(guider_ui.ui_Panel_Volume_Mask2, -4);

    lv_obj_set_align(guider_ui.ui_Panel_Volume_Mask2, LV_ALIGN_BOTTOM_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Volume_Mask2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Volume_Mask2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Volume_Mask2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Volume_Mask2);

    // guider_ui.ui_Arc_Volume1

    guider_ui.ui_Arc_Volume1 = lv_arc_create(guider_ui.ui_Panel_Volume_Mask2);

    lv_obj_set_width(guider_ui.ui_Arc_Volume1, 370);
    lv_obj_set_height(guider_ui.ui_Arc_Volume1, 370);

    lv_obj_set_x(guider_ui.ui_Arc_Volume1, 30);
    lv_obj_set_y(guider_ui.ui_Arc_Volume1, -97);

    lv_obj_set_align(guider_ui.ui_Arc_Volume1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Arc_Volume1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Arc_Volume1, LV_OBJ_FLAG_GESTURE_BUBBLE);

    lv_arc_set_range(guider_ui.ui_Arc_Volume1, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Volume1, 70);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Volume1, 0, 96);
    lv_arc_set_rotation(guider_ui.ui_Arc_Volume1, 50);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Volume1, lv_color_hex(0x4A4C4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Volume1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Volume1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Volume1, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Volume1, lv_color_hex(0x09CF09), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Volume1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(guider_ui.ui_Arc_Volume1, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Volume1, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Volume1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Volume1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_clear_flag(guider_ui.ui_Arc_Volume1, LV_OBJ_FLAG_CLICKABLE);

    // guider_ui.ui_Label_Audio_Time

    guider_ui.ui_Label_Audio_Time = lv_label_create(guider_ui.ui_Anim_Up_S11);

    lv_obj_set_width(guider_ui.ui_Label_Audio_Time, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Audio_Time, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Audio_Time, 0);
    lv_obj_set_y(guider_ui.ui_Label_Audio_Time, -110);

    lv_obj_set_align(guider_ui.ui_Label_Audio_Time, LV_ALIGN_BOTTOM_MID);

    lv_label_set_text(guider_ui.ui_Label_Audio_Time, "01:24  |  02:15");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Audio_Time, lv_color_hex(0xC5C6C5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Audio_Time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Audio_Time, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Audio_RND

    guider_ui.ui_Image_Audio_RND = lv_img_create(guider_ui.ui_Anim_Up_S11);
    lv_img_set_src(guider_ui.ui_Image_Audio_RND, &ui_img_icn_audio_rnd_png);

    lv_obj_set_width(guider_ui.ui_Image_Audio_RND, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Audio_RND, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Audio_RND, 0);
    lv_obj_set_y(guider_ui.ui_Image_Audio_RND, -60);

    lv_obj_set_align(guider_ui.ui_Image_Audio_RND, LV_ALIGN_BOTTOM_MID);

    lv_obj_add_flag(guider_ui.ui_Image_Audio_RND, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Audio_RND, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Audio_RND, 0, 0);

    // guider_ui.ui_S11_Buttons

    guider_ui.ui_S11_Buttons = lv_obj_create(guider_ui.ui_S11_Music);

    lv_obj_set_width(guider_ui.ui_S11_Buttons, 392);
    lv_obj_set_height(guider_ui.ui_S11_Buttons, 392);

    lv_obj_set_x(guider_ui.ui_S11_Buttons, 0);
    lv_obj_set_y(guider_ui.ui_S11_Buttons, 0);

    lv_obj_set_align(guider_ui.ui_S11_Buttons, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_S11_Buttons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_S11_Buttons, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S11_Buttons, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_S11_Buttons);

    // guider_ui.ui_BTN_Home7

    guider_ui.ui_BTN_Home7 = lv_obj_create(guider_ui.ui_S11_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Home7, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Home7, 80);

    lv_obj_set_x(guider_ui.ui_BTN_Home7, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Home7, 90);

    lv_obj_set_align(guider_ui.ui_BTN_Home7, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Home7, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

    //lv_obj_add_event_cb(guider_ui.ui_BTN_Home7, ui_event_BTN_Home1, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Home7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Home7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_BTN_Home7);

    // guider_ui.ui_Panel_Menu5

    guider_ui.ui_Panel_Menu5 = lv_obj_create(guider_ui.ui_S11_Music);

    lv_obj_set_width(guider_ui.ui_Panel_Menu5, 33);
    lv_obj_set_height(guider_ui.ui_Panel_Menu5, 124);

    lv_obj_set_x(guider_ui.ui_Panel_Menu5, 0);
    lv_obj_set_y(guider_ui.ui_Panel_Menu5, 0);

    lv_obj_set_align(guider_ui.ui_Panel_Menu5, LV_ALIGN_RIGHT_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Menu5, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Menu5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Menu5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Menu5);
    lv_obj_set_style_bg_img_src(guider_ui.ui_Panel_Menu5, &ui_img_img_menu_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Menu_Knob5

    guider_ui.ui_Menu_Knob5 = lv_obj_create(guider_ui.ui_Panel_Menu5);

    lv_obj_set_width(guider_ui.ui_Menu_Knob5, 8);
    lv_obj_set_height(guider_ui.ui_Menu_Knob5, 8);

    lv_obj_set_x(guider_ui.ui_Menu_Knob5, 3);
    lv_obj_set_y(guider_ui.ui_Menu_Knob5, -13);

    lv_obj_set_align(guider_ui.ui_Menu_Knob5, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Menu_Knob5, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(guider_ui.ui_Menu_Knob5, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_S24_EKG_screen_init(void)
{

    // guider_ui.ui_S24_EKG

    guider_ui.ui_S24_EKG = lv_obj_create(NULL);

    lv_obj_clear_flag(guider_ui.ui_S24_EKG, LV_OBJ_FLAG_SCROLLABLE);

  //  lv_obj_add_event_cb(guider_ui.ui_S24_EKG, ui_event_S24_EKG, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_S24_EKG, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S24_EKG, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Bg21

    guider_ui.ui_Image_Bg21 = lv_img_create(guider_ui.ui_S24_EKG);
    lv_img_set_src(guider_ui.ui_Image_Bg21, &ui_img_img_bg_health_png);

    lv_obj_set_width(guider_ui.ui_Image_Bg21, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Bg21, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Bg21, 0);
    lv_obj_set_y(guider_ui.ui_Image_Bg21, 0);

    lv_obj_set_align(guider_ui.ui_Image_Bg21, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Bg21, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Bg21, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Bg21, 0, 0);
    Set_border_style(guider_ui.ui_Image_Bg21);
    // guider_ui.ui_Anim_On_S24

    guider_ui.ui_Anim_On_S24 = lv_obj_create(guider_ui.ui_S24_EKG);

    lv_obj_set_width(guider_ui.ui_Anim_On_S24, 392);
    lv_obj_set_height(guider_ui.ui_Anim_On_S24, 392);

    lv_obj_set_x(guider_ui.ui_Anim_On_S24, 0);
    lv_obj_set_y(guider_ui.ui_Anim_On_S24, 0);

    lv_obj_set_align(guider_ui.ui_Anim_On_S24, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_On_S24, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_On_S24, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_On_S24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_On_S24);

    // guider_ui.ui_Image_EKG

    guider_ui.ui_Image_EKG = lv_img_create(guider_ui.ui_Anim_On_S24);
    lv_img_set_src(guider_ui.ui_Image_EKG, &ui_img_img_ekg_png);

    lv_obj_set_width(guider_ui.ui_Image_EKG, 512);
    lv_obj_set_height(guider_ui.ui_Image_EKG, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_EKG, 0);
    lv_obj_set_y(guider_ui.ui_Image_EKG, 0);

    lv_obj_set_align(guider_ui.ui_Image_EKG, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(guider_ui.ui_Image_EKG, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_EKG, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_EKG, 0, 0);
   // Set_border_style(guider_ui.ui_Image_EKG);

    // guider_ui.ui_Anim_Up_S24

    guider_ui.ui_Anim_Up_S24 = lv_obj_create(guider_ui.ui_S24_EKG);

    lv_obj_set_width(guider_ui.ui_Anim_Up_S24, 392);
    lv_obj_set_height(guider_ui.ui_Anim_Up_S24, 395);

    lv_obj_set_x(guider_ui.ui_Anim_Up_S24, 0);
    lv_obj_set_y(guider_ui.ui_Anim_Up_S24, 0);

    lv_obj_set_align(guider_ui.ui_Anim_Up_S24, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_Up_S24, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_Up_S24, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_Up_S24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_Up_S24);

    // guider_ui.ui_Panel_Pulse

    guider_ui.ui_Panel_Pulse = lv_obj_create(guider_ui.ui_Anim_Up_S24);

    lv_obj_set_width(guider_ui.ui_Panel_Pulse, 71);
    lv_obj_set_height(guider_ui.ui_Panel_Pulse, 114);

    lv_obj_set_x(guider_ui.ui_Panel_Pulse, 45);
    lv_obj_set_y(guider_ui.ui_Panel_Pulse, 5);

    lv_obj_set_align(guider_ui.ui_Panel_Pulse, LV_ALIGN_BOTTOM_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Pulse, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Pulse, lv_color_hex(0x080C08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Pulse, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Pulse);

    // guider_ui.ui_Label_Pulse2

    guider_ui.ui_Label_Pulse2 = lv_label_create(guider_ui.ui_Panel_Pulse);

    lv_obj_set_width(guider_ui.ui_Label_Pulse2, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Pulse2, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Pulse2, -5);
    lv_obj_set_y(guider_ui.ui_Label_Pulse2, 4);

    lv_label_set_text(guider_ui.ui_Label_Pulse2, "PULSE");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Pulse2, lv_color_hex(0x949194), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Pulse2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_Pulse2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Pulse2, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Seat_Number2

    guider_ui.ui_Label_Seat_Number2 = lv_label_create(guider_ui.ui_Panel_Pulse);

    lv_obj_set_width(guider_ui.ui_Label_Seat_Number2, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Seat_Number2, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Seat_Number2, -5);
    lv_obj_set_y(guider_ui.ui_Label_Seat_Number2, 0);

    lv_obj_set_align(guider_ui.ui_Label_Seat_Number2, LV_ALIGN_LEFT_MID);

    lv_label_set_long_mode(guider_ui.ui_Label_Seat_Number2, LV_LABEL_LONG_DOT);
    lv_label_set_text(guider_ui.ui_Label_Seat_Number2, "67");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Seat_Number2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Seat_Number2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Seat_Number2, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_bpm

    guider_ui.ui_Label_bpm = lv_label_create(guider_ui.ui_Panel_Pulse);

    lv_obj_set_width(guider_ui.ui_Label_bpm, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_bpm, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_bpm, -5);
    lv_obj_set_y(guider_ui.ui_Label_bpm, 4);

    lv_obj_set_align(guider_ui.ui_Label_bpm, LV_ALIGN_BOTTOM_LEFT);

    lv_label_set_text(guider_ui.ui_Label_bpm, "bpm");

    lv_obj_set_style_text_color(guider_ui.ui_Label_bpm, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_bpm, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_bpm, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_bpm, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Heart1

    guider_ui.ui_Image_Heart1 = lv_img_create(guider_ui.ui_Anim_Up_S24);
    lv_img_set_src(guider_ui.ui_Image_Heart1, &ui_img_img_heart_png);

    lv_obj_set_width(guider_ui.ui_Image_Heart1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Heart1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Heart1, -30);
    lv_obj_set_y(guider_ui.ui_Image_Heart1, 141);

    lv_obj_set_align(guider_ui.ui_Image_Heart1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Heart1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Heart1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Heart1, 25, 21);

    // guider_ui.ui_Image_Heart2

    guider_ui.ui_Image_Heart2 = lv_img_create(guider_ui.ui_Anim_Up_S24);
    lv_img_set_src(guider_ui.ui_Image_Heart2, &ui_img_img_heart_png);

    lv_obj_set_width(guider_ui.ui_Image_Heart2, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Heart2, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Heart2, -30);
    lv_obj_set_y(guider_ui.ui_Image_Heart2, 141);

    lv_obj_set_align(guider_ui.ui_Image_Heart2, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Heart2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Heart2, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Heart2, 25, 21);

    // guider_ui.ui_Anim_Down_S24

    guider_ui.ui_Anim_Down_S24 = lv_obj_create(guider_ui.ui_S24_EKG);

    lv_obj_set_width(guider_ui.ui_Anim_Down_S24, 392);
    lv_obj_set_height(guider_ui.ui_Anim_Down_S24, 392);

    lv_obj_set_x(guider_ui.ui_Anim_Down_S24, 0);
    lv_obj_set_y(guider_ui.ui_Anim_Down_S24, 0);

    lv_obj_set_align(guider_ui.ui_Anim_Down_S24, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_Down_S24, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_Down_S24, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_Down_S24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Anim_Down_S24);

    // guider_ui.ui_Panel_Arrival1

    guider_ui.ui_Panel_Arrival1 = lv_obj_create(guider_ui.ui_Anim_Down_S24);

    lv_obj_set_width(guider_ui.ui_Panel_Arrival1, 148);
    lv_obj_set_height(guider_ui.ui_Panel_Arrival1, 75);

    lv_obj_set_x(guider_ui.ui_Panel_Arrival1, -40);
    lv_obj_set_y(guider_ui.ui_Panel_Arrival1, -90);

    lv_obj_set_align(guider_ui.ui_Panel_Arrival1, LV_ALIGN_RIGHT_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Arrival1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Arrival1, lv_color_hex(0x080C08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Arrival1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Arrival1);

    // guider_ui.ui_Label_EKG_Beat_Count

    guider_ui.ui_Label_EKG_Beat_Count = lv_label_create(guider_ui.ui_Panel_Arrival1);

    lv_obj_set_width(guider_ui.ui_Label_EKG_Beat_Count, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_EKG_Beat_Count, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_EKG_Beat_Count, 0);
    lv_obj_set_y(guider_ui.ui_Label_EKG_Beat_Count, -5);

    lv_obj_set_align(guider_ui.ui_Label_EKG_Beat_Count, LV_ALIGN_TOP_MID);

    lv_label_set_text(guider_ui.ui_Label_EKG_Beat_Count, "BEAT COUNT");

    lv_obj_set_style_text_color(guider_ui.ui_Label_EKG_Beat_Count, lv_color_hex(0x949194), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_EKG_Beat_Count, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_EKG_Beat_Count, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_EKG_Beat_Count, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_EKG_Beat_Number

    guider_ui.ui_Label_EKG_Beat_Number = lv_label_create(guider_ui.ui_Panel_Arrival1);

    lv_obj_set_width(guider_ui.ui_Label_EKG_Beat_Number, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_EKG_Beat_Number, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_EKG_Beat_Number, 0);
    lv_obj_set_y(guider_ui.ui_Label_EKG_Beat_Number, 10);

    lv_obj_set_align(guider_ui.ui_Label_EKG_Beat_Number, LV_ALIGN_BOTTOM_MID);

    lv_label_set_long_mode(guider_ui.ui_Label_EKG_Beat_Number, LV_LABEL_LONG_DOT);
    lv_label_set_text(guider_ui.ui_Label_EKG_Beat_Number, "320");

    lv_obj_set_style_text_color(guider_ui.ui_Label_EKG_Beat_Number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_EKG_Beat_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_EKG_Beat_Number, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Panel_Departure1

    guider_ui.ui_Panel_Departure1 = lv_obj_create(guider_ui.ui_Anim_Down_S24);

    lv_obj_set_width(guider_ui.ui_Panel_Departure1, 148);
    lv_obj_set_height(guider_ui.ui_Panel_Departure1, 75);

    lv_obj_set_x(guider_ui.ui_Panel_Departure1, 40);
    lv_obj_set_y(guider_ui.ui_Panel_Departure1, -90);

    lv_obj_set_align(guider_ui.ui_Panel_Departure1, LV_ALIGN_LEFT_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Departure1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Departure1, lv_color_hex(0x080C08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Departure1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Panel_Departure1);

    // guider_ui.ui_Label_EKG_Interval

    guider_ui.ui_Label_EKG_Interval = lv_label_create(guider_ui.ui_Panel_Departure1);

    lv_obj_set_width(guider_ui.ui_Label_EKG_Interval, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_EKG_Interval, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_EKG_Interval, 0);
    lv_obj_set_y(guider_ui.ui_Label_EKG_Interval, -5);

    lv_obj_set_align(guider_ui.ui_Label_EKG_Interval, LV_ALIGN_TOP_MID);

    lv_label_set_text(guider_ui.ui_Label_EKG_Interval, "R-R INTERVAL");

    lv_obj_set_style_text_color(guider_ui.ui_Label_EKG_Interval, lv_color_hex(0x949194), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_EKG_Interval, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(guider_ui.ui_Label_EKG_Interval, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_EKG_Interval, &ui_font_small_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label_EKG_Interval_Number

    guider_ui.ui_Label_EKG_Interval_Number = lv_label_create(guider_ui.ui_Panel_Departure1);

    lv_obj_set_width(guider_ui.ui_Label_EKG_Interval_Number, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_EKG_Interval_Number, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_EKG_Interval_Number, 0);
    lv_obj_set_y(guider_ui.ui_Label_EKG_Interval_Number, 10);

    lv_obj_set_align(guider_ui.ui_Label_EKG_Interval_Number, LV_ALIGN_BOTTOM_MID);

    lv_label_set_long_mode(guider_ui.ui_Label_EKG_Interval_Number, LV_LABEL_LONG_DOT);
    lv_label_set_text(guider_ui.ui_Label_EKG_Interval_Number, "940");

    lv_obj_set_style_text_color(guider_ui.ui_Label_EKG_Interval_Number, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_EKG_Interval_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_EKG_Interval_Number, &ui_font_big_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Header_S24

    guider_ui.ui_Header_S24 = lv_obj_create(guider_ui.ui_S24_EKG);

    lv_obj_set_width(guider_ui.ui_Header_S24, 392);
    lv_obj_set_height(guider_ui.ui_Header_S24, 128);

    lv_obj_set_x(guider_ui.ui_Header_S24, 0);
    lv_obj_set_y(guider_ui.ui_Header_S24, -10);

    lv_obj_set_align(guider_ui.ui_Header_S24, LV_ALIGN_TOP_MID);

    lv_obj_clear_flag(guider_ui.ui_Header_S24, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Header_S24, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Header_S24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_Header_S24);
    // guider_ui.ui_Image_Header_Shadow17

    guider_ui.ui_Image_Header_Shadow17 = lv_img_create(guider_ui.ui_Header_S24);
    lv_img_set_src(guider_ui.ui_Image_Header_Shadow17, &ui_img_img_header_bg_shadow_png);

    lv_obj_set_width(guider_ui.ui_Image_Header_Shadow17, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Header_Shadow17, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Header_Shadow17, 0);
    lv_obj_set_y(guider_ui.ui_Image_Header_Shadow17, -8);

    lv_obj_set_align(guider_ui.ui_Image_Header_Shadow17, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Header_Shadow17, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Header_Shadow17, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Header_Shadow17, 0, 0);

    // guider_ui.ui_Image_Header17

    guider_ui.ui_Image_Header17 = lv_img_create(guider_ui.ui_Header_S24);
    lv_img_set_src(guider_ui.ui_Image_Header17, &ui_img_img_header_bg_png);

    lv_obj_set_width(guider_ui.ui_Image_Header17, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Header17, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Header17, 0);
    lv_obj_set_y(guider_ui.ui_Image_Header17, -27);

    lv_obj_set_align(guider_ui.ui_Image_Header17, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Header17, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Header17, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Header17, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Header17, lv_color_hex(0xBD1C39), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Header17, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Your_Flight2

    guider_ui.ui_Label_Your_Flight2 = lv_label_create(guider_ui.ui_Header_S24);

    lv_obj_set_width(guider_ui.ui_Label_Your_Flight2, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Your_Flight2, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Your_Flight2, 0);
    lv_obj_set_y(guider_ui.ui_Label_Your_Flight2, -20);

    lv_obj_set_align(guider_ui.ui_Label_Your_Flight2, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Your_Flight2, "EKG");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Your_Flight2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Your_Flight2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Your_Flight2, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Label_Home20

    guider_ui.ui_Image_Label_Home20 = lv_img_create(guider_ui.ui_S24_EKG);
    lv_img_set_src(guider_ui.ui_Image_Label_Home20, &ui_img_text_home_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Home20, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Home20, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Home20, 154);
    lv_obj_set_y(guider_ui.ui_Image_Label_Home20, 97);

    lv_obj_set_align(guider_ui.ui_Image_Label_Home20, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Home20, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Home20, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Home20, 0, 0);

    // guider_ui.ui_S24_Buttons

    guider_ui.ui_S24_Buttons = lv_obj_create(guider_ui.ui_S24_EKG);

    lv_obj_set_width(guider_ui.ui_S24_Buttons, 392);
    lv_obj_set_height(guider_ui.ui_S24_Buttons, 392);

    lv_obj_set_x(guider_ui.ui_S24_Buttons, 0);
    lv_obj_set_y(guider_ui.ui_S24_Buttons, 0);

    lv_obj_set_align(guider_ui.ui_S24_Buttons, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_S24_Buttons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_S24_Buttons, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S24_Buttons, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_S24_Buttons);
    // guider_ui.ui_BTN_Home20

    guider_ui.ui_BTN_Home20 = lv_obj_create(guider_ui.ui_S24_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Home20, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Home20, 80);

    lv_obj_set_x(guider_ui.ui_BTN_Home20, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Home20, 90);

    lv_obj_set_align(guider_ui.ui_BTN_Home20, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Home20, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

  //  lv_obj_add_event_cb(guider_ui.ui_BTN_Home20, ui_event_BTN_Home20, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Home20, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Home20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    Set_border_style(guider_ui.ui_BTN_Home20);
    // guider_ui.ui_Image_Arrow23

    guider_ui.ui_Image_Arrow23 = lv_img_create(guider_ui.ui_S24_EKG);
    lv_img_set_src(guider_ui.ui_Image_Arrow23, &ui_img_img_arrow_right_png);

    lv_obj_set_width(guider_ui.ui_Image_Arrow23, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Arrow23, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Arrow23, -4);
    lv_obj_set_y(guider_ui.ui_Image_Arrow23, 0);

    lv_obj_set_align(guider_ui.ui_Image_Arrow23, LV_ALIGN_RIGHT_MID);

    lv_obj_add_flag(guider_ui.ui_Image_Arrow23, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Arrow23, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Arrow23, 0, 0);

    // guider_ui.ui_Image_Arrow24

    guider_ui.ui_Image_Arrow24 = lv_img_create(guider_ui.ui_S24_EKG);
    lv_img_set_src(guider_ui.ui_Image_Arrow24, &ui_img_img_arrow_left_png);

    lv_obj_set_width(guider_ui.ui_Image_Arrow24, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Arrow24, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Arrow24, 4);
    lv_obj_set_y(guider_ui.ui_Image_Arrow24, 0);

    lv_obj_set_align(guider_ui.ui_Image_Arrow24, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(guider_ui.ui_Image_Arrow24, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Arrow24, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Arrow24, 0, 0);

}
void ui_S2_Watch_Analog_screen_init(void)
{

    // guider_ui.ui_S2_Watch_Analog

    guider_ui.ui_S2_Watch_Analog = lv_obj_create(NULL);

    lv_obj_clear_flag(guider_ui.ui_S2_Watch_Analog, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_S2_Watch_Analog, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S2_Watch_Analog, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Bg1

    guider_ui.ui_Image_Bg1 = lv_img_create(guider_ui.ui_S2_Watch_Analog);
    lv_img_set_src(guider_ui.ui_Image_Bg1, &ui_img_img_bg_analog_png);

    lv_obj_set_width(guider_ui.ui_Image_Bg1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Bg1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Bg1, 0);
    lv_obj_set_y(guider_ui.ui_Image_Bg1, 0);

    lv_obj_set_align(guider_ui.ui_Image_Bg1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Bg1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Bg1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Bg1, 0, 0);

    static lv_style_t style_image_Bg;
    lv_style_init(&style_image_Bg);

    lv_style_set_border_width(&style_image_Bg, 0);
    lv_obj_add_style(guider_ui.ui_Image_Bg1, &style_image_Bg, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(guider_ui.ui_Image_Bg1, &style_image_Bg, LV_PART_MAIN | LV_STATE_DEFAULT);



    guider_ui.ui_Image_Sec = lv_img_create(guider_ui.ui_S2_Watch_Analog);
    lv_img_set_src(guider_ui.ui_Image_Sec, &ui_img_img_clockwise_sec_png);

    lv_obj_set_width(guider_ui.ui_Image_Sec, 31);
    lv_obj_set_height(guider_ui.ui_Image_Sec, 180);

   // lv_obj_set_width(guider_ui.ui_Image_Sec, LV_SIZE_CONTENT);
    //lv_obj_set_height(guider_ui.ui_Image_Sec, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Sec, 0);
    lv_obj_set_y(guider_ui.ui_Image_Sec, -66);

    lv_obj_set_align(guider_ui.ui_Image_Sec, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Sec, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Sec, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Sec, 16, 156);
    lv_img_set_angle(guider_ui.ui_Image_Sec, 0);

static lv_style_t style_screen_btn_1_main_main_default;
    lv_style_init(&style_screen_btn_1_main_main_default);
    lv_style_set_bg_grad_color(&style_screen_btn_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_opa(&style_screen_btn_1_main_main_default, 0);
    lv_style_set_border_width(&style_screen_btn_1_main_main_default, 0);
    lv_obj_add_style(guider_ui.ui_Image_Sec, &style_screen_btn_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    // guider_ui.ui_Anim_On1

    guider_ui.ui_Anim_On1 = lv_obj_create(guider_ui.ui_S2_Watch_Analog);

    lv_obj_set_width(guider_ui.ui_Anim_On1, 392);
    lv_obj_set_height(guider_ui.ui_Anim_On1, 395);

    lv_obj_set_x(guider_ui.ui_Anim_On1, 0);
    lv_obj_set_y(guider_ui.ui_Anim_On1, 0);

    lv_obj_set_align(guider_ui.ui_Anim_On1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Anim_On1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Anim_On1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Anim_On1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_add_style(guider_ui.ui_Anim_On1, &style_image_Bg, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(guider_ui.ui_Anim_On1, &style_image_Bg, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Power1

    guider_ui.ui_Label_Power1 = lv_label_create(guider_ui.ui_Anim_On1);

    lv_obj_set_width(guider_ui.ui_Label_Power1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Power1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Power1, 9);
    lv_obj_set_y(guider_ui.ui_Label_Power1, -172);

    lv_obj_set_align(guider_ui.ui_Label_Power1, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Power1, "86%");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Power1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Power1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Power1, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Flash1

    guider_ui.ui_Image_Flash1 = lv_img_create(guider_ui.ui_Anim_On1);
    lv_img_set_src(guider_ui.ui_Image_Flash1, &ui_img_icn_flash_png);

    lv_obj_set_width(guider_ui.ui_Image_Flash1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Flash1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Flash1, -26);
    lv_obj_set_y(guider_ui.ui_Image_Flash1, -172);

    lv_obj_set_align(guider_ui.ui_Image_Flash1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Flash1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Flash1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Flash1, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Flash1, lv_color_hex(0x1099E6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Flash1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Sport1

    guider_ui.ui_Image_Sport1 = lv_img_create(guider_ui.ui_Anim_On1);
    lv_img_set_src(guider_ui.ui_Image_Sport1, &ui_img_icn_sport_png);

    lv_obj_set_width(guider_ui.ui_Image_Sport1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Sport1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Sport1, 130);
    lv_obj_set_y(guider_ui.ui_Image_Sport1, -77);

    lv_obj_set_align(guider_ui.ui_Image_Sport1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Sport1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Sport1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Sport1, 0, 0);
   // lv_obj_set_style_bg_img_src(guider_ui.ui_Image_Sport1, &ui_img_icn_step_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    /**********************************************************************************************************************************************************************/

    // guider_ui.ui_Image_Label_Sport1

    guider_ui.ui_Image_Label_Sport1 = lv_img_create(guider_ui.ui_Anim_On1);
    lv_img_set_src(guider_ui.ui_Image_Label_Sport1, &ui_img_text_sport_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Sport1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Sport1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Sport1, 155);
    lv_obj_set_y(guider_ui.ui_Image_Label_Sport1, -94);

    lv_obj_set_align(guider_ui.ui_Image_Label_Sport1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Sport1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Sport1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Sport1, 0, 0);

    // guider_ui.ui_Image_Label_Messages1

    guider_ui.ui_Image_Label_Messages1 = lv_img_create(guider_ui.ui_Anim_On1);
    lv_img_set_src(guider_ui.ui_Image_Label_Messages1, &ui_img_text_message_png);

    lv_obj_set_width(guider_ui.ui_Image_Label_Messages1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Label_Messages1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Label_Messages1, 145);
    lv_obj_set_y(guider_ui.ui_Image_Label_Messages1, 101);

    lv_obj_set_align(guider_ui.ui_Image_Label_Messages1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Label_Messages1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Label_Messages1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Label_Messages1, 0, 0);

    // guider_ui.ui_Image_Notifi1

    guider_ui.ui_Image_Notifi1 = lv_img_create(guider_ui.ui_Anim_On1);
    lv_img_set_src(guider_ui.ui_Image_Notifi1, &ui_img_icn_message_png);

    lv_obj_set_width(guider_ui.ui_Image_Notifi1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Notifi1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Notifi1, 129);
    lv_obj_set_y(guider_ui.ui_Image_Notifi1, 81);

    lv_obj_set_align(guider_ui.ui_Image_Notifi1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Notifi1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Notifi1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Notifi1, 0, 0);
    lv_obj_set_style_outline_opa(guider_ui.ui_Image_Notifi1,0, LV_PART_MAIN);

	static lv_style_t style_image_Noti1;
	lv_style_init(&style_image_Noti1);

	lv_style_set_border_width(&style_image_Noti1, 0);
	lv_obj_add_style(guider_ui.ui_Image_Notifi1, &style_image_Noti1, LV_PART_MAIN|LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Step1

    guider_ui.ui_Image_Step1 = lv_img_create(guider_ui.ui_Anim_On1);
    lv_img_set_src(guider_ui.ui_Image_Step1, &ui_img_icn_step_png);

    lv_obj_set_width(guider_ui.ui_Image_Step1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Step1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Step1, -24);
    lv_obj_set_y(guider_ui.ui_Image_Step1, 150);

    lv_obj_set_align(guider_ui.ui_Image_Step1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Step1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Step1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Step1, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Step1, lv_color_hex(0xE35515), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Step1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Weather1

    guider_ui.ui_Image_Weather1 = lv_img_create(guider_ui.ui_Anim_On1);
    lv_img_set_src(guider_ui.ui_Image_Weather1, &ui_img_icn_weather_1_png);

    lv_obj_set_width(guider_ui.ui_Image_Weather1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_Weather1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Weather1, -117);
    lv_obj_set_y(guider_ui.ui_Image_Weather1, 30);

    lv_obj_set_align(guider_ui.ui_Image_Weather1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Weather1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Weather1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Weather1, 0, 0);

    lv_obj_set_style_img_recolor(guider_ui.ui_Image_Weather1, lv_color_hex(0x7B797B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(guider_ui.ui_Image_Weather1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_NXP1

    guider_ui.ui_Image_NXP1 = lv_img_create(guider_ui.ui_Anim_On1);
    lv_img_set_src(guider_ui.ui_Image_NXP1, &ui_img_img_nxp_png);

    lv_obj_set_width(guider_ui.ui_Image_NXP1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_NXP1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_NXP1, 130);
    lv_obj_set_y(guider_ui.ui_Image_NXP1, 0);

    lv_obj_set_align(guider_ui.ui_Image_NXP1, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_NXP1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_NXP1, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_NXP1, 0, 0);

    // guider_ui.ui_Label_Date1

    guider_ui.ui_Label_Date1 = lv_label_create(guider_ui.ui_Anim_On1);

    lv_obj_set_width(guider_ui.ui_Label_Date1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Date1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Date1, -116);
    lv_obj_set_y(guider_ui.ui_Label_Date1, -76);

    lv_obj_set_align(guider_ui.ui_Label_Date1, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Date1, "05/15");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Date1, lv_color_hex(0x7B797B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Date1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Date1, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Week1

    guider_ui.ui_Label_Week1 = lv_label_create(guider_ui.ui_Anim_On1);

    lv_obj_set_width(guider_ui.ui_Label_Week1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Week1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Week1, -116);
    lv_obj_set_y(guider_ui.ui_Label_Week1, -51);

    lv_obj_set_align(guider_ui.ui_Label_Week1, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Week1, "WED");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Week1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Week1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Week1, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Degree1

    guider_ui.ui_Label_Degree1 = lv_label_create(guider_ui.ui_Anim_On1);

    lv_obj_set_width(guider_ui.ui_Label_Degree1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Degree1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Degree1, -115);
    lv_obj_set_y(guider_ui.ui_Label_Degree1, 65);

    lv_obj_set_align(guider_ui.ui_Label_Degree1, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Degree1, "26°");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Degree1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Degree1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Degree1, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Label_Step_Count1

    guider_ui.ui_Label_Step_Count1 = lv_label_create(guider_ui.ui_Anim_On1);

    lv_obj_set_width(guider_ui.ui_Label_Step_Count1, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Label_Step_Count1, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Label_Step_Count1, 13);
    lv_obj_set_y(guider_ui.ui_Label_Step_Count1, 152);

    lv_obj_set_align(guider_ui.ui_Label_Step_Count1, LV_ALIGN_CENTER);

    lv_label_set_text(guider_ui.ui_Label_Step_Count1, "1526");

    lv_obj_set_style_text_color(guider_ui.ui_Label_Step_Count1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(guider_ui.ui_Label_Step_Count1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(guider_ui.ui_Label_Step_Count1, &ui_font_medium_font, LV_PART_MAIN | LV_STATE_DEFAULT);


    // guider_ui.ui_Arc_Step_Count1

    guider_ui.ui_Arc_Step_Count1 = lv_arc_create(guider_ui.ui_Anim_On1);

    lv_obj_set_width(guider_ui.ui_Arc_Step_Count1, 370);
    lv_obj_set_height(guider_ui.ui_Arc_Step_Count1, 370);

    lv_obj_set_x(guider_ui.ui_Arc_Step_Count1, 0);
    lv_obj_set_y(guider_ui.ui_Arc_Step_Count1, 0);

    lv_obj_set_align(guider_ui.ui_Arc_Step_Count1, LV_ALIGN_CENTER);

  //  lv_obj_add_flag(guider_ui.ui_Arc_Step_Count1, LV_OBJ_FLAG_ADV_HITTEST);

    lv_arc_set_range(guider_ui.ui_Arc_Step_Count1, 0, 100);
    lv_arc_set_value(guider_ui.ui_Arc_Step_Count1, 80);
    lv_arc_set_bg_angles(guider_ui.ui_Arc_Step_Count1, 0, 50);
    lv_arc_set_rotation(guider_ui.ui_Arc_Step_Count1, 65);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Step_Count1, lv_color_hex(0x4A4C4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Step_Count1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Step_Count1, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Step_Count1, lv_color_hex(0xFF5D18), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Step_Count1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Step_Count1, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Step_Count1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Step_Count1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Hour

    guider_ui.ui_Image_Hour = lv_img_create(guider_ui.ui_S2_Watch_Analog);
    lv_img_set_src(guider_ui.ui_Image_Hour, &ui_img_img_clockwise_hour_png);

    lv_obj_set_width(guider_ui.ui_Image_Hour, 18);
    lv_obj_set_height(guider_ui.ui_Image_Hour, 98);

    //lv_obj_set_width(guider_ui.ui_Image_Hour, LV_SIZE_CONTENT);
    //lv_obj_set_height(guider_ui.ui_Image_Hour, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_Hour, 0);
    lv_obj_set_y(guider_ui.ui_Image_Hour, -50);

    lv_obj_set_align(guider_ui.ui_Image_Hour, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Hour, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Hour, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Hour, 9, 98);

   //lv_obj_add_style(guider_ui.ui_Image_Hour, &style_screen_btn_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    // guider_ui.ui_Image_Min

    guider_ui.ui_Image_Min = lv_img_create(guider_ui.ui_S2_Watch_Analog);
    lv_img_set_src(guider_ui.ui_Image_Min, &ui_img_img_clockwise_min_png);

    lv_obj_set_width(guider_ui.ui_Image_Min, 18);
    lv_obj_set_height(guider_ui.ui_Image_Min, 157);

    lv_obj_set_x(guider_ui.ui_Image_Min, 1);
    lv_obj_set_y(guider_ui.ui_Image_Min, -80);

    lv_obj_set_align(guider_ui.ui_Image_Min, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_Min, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_Min, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_Min, 9, 157);

  //  lv_img_set_angle(guider_ui.ui_Image_Min, 2100);
    
    //lv_obj_add_style(guider_ui.ui_Image_Min, &style_screen_btn_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    
    // guider_ui.ui_S2_Buttons

    guider_ui.ui_S2_Buttons = lv_obj_create(guider_ui.ui_S2_Watch_Analog);

    lv_obj_set_width(guider_ui.ui_S2_Buttons, 392);
    lv_obj_set_height(guider_ui.ui_S2_Buttons, 392);

    lv_obj_set_x(guider_ui.ui_S2_Buttons, 0);
    lv_obj_set_y(guider_ui.ui_S2_Buttons, 0);

    lv_obj_set_align(guider_ui.ui_S2_Buttons, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_S2_Buttons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_S2_Buttons, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_S2_Buttons, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_style_set_border_width(&style_image_Noti1, 0);
    lv_obj_add_style(guider_ui.ui_S2_Buttons, &style_image_Noti1, LV_PART_MAIN|LV_STATE_DEFAULT);

    // guider_ui.ui_BTN_Messages1

    guider_ui.ui_BTN_Messages1 = lv_obj_create(guider_ui.ui_S2_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Messages1, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Messages1, 80);

    lv_obj_set_x(guider_ui.ui_BTN_Messages1, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Messages1, 90);

    lv_obj_set_align(guider_ui.ui_BTN_Messages1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Messages1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

    //lv_obj_add_event_cb(guider_ui.ui_BTN_Messages1, ui_event_BTN_Messages1, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Messages1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Messages1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    static lv_style_t style_image_Butons;
     lv_style_init(&style_image_Butons);

     lv_style_set_border_width(&style_image_Butons, 0);
     lv_obj_add_style(guider_ui.ui_BTN_Messages1, &style_image_Butons, LV_PART_MAIN|LV_STATE_DEFAULT);
     lv_obj_set_style_bg_img_src(guider_ui.ui_BTN_Messages1, &style_image_Butons, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_BTN_Sport1

    guider_ui.ui_BTN_Sport1 = lv_obj_create(guider_ui.ui_S2_Buttons);

    lv_obj_set_width(guider_ui.ui_BTN_Sport1, 80);
    lv_obj_set_height(guider_ui.ui_BTN_Sport1, 80);

    lv_obj_set_x(guider_ui.ui_BTN_Sport1, 130);
    lv_obj_set_y(guider_ui.ui_BTN_Sport1, -90);

    lv_obj_set_align(guider_ui.ui_BTN_Sport1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_BTN_Sport1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_BTN_Sport1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_BTN_Sport1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(guider_ui.ui_BTN_Sport1, &style_image_Butons, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(guider_ui.ui_BTN_Sport1, &style_image_Butons, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Panel_Menu2

    guider_ui.ui_Panel_Menu2 = lv_obj_create(guider_ui.ui_S2_Watch_Analog);

    lv_obj_set_width(guider_ui.ui_Panel_Menu2, 33);
    lv_obj_set_height(guider_ui.ui_Panel_Menu2, 124);

    lv_obj_set_x(guider_ui.ui_Panel_Menu2, 0);
    lv_obj_set_y(guider_ui.ui_Panel_Menu2, 0);

    lv_obj_set_align(guider_ui.ui_Panel_Menu2, LV_ALIGN_RIGHT_MID);

    lv_obj_clear_flag(guider_ui.ui_Panel_Menu2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(guider_ui.ui_Panel_Menu2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_Panel_Menu2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(guider_ui.ui_Panel_Menu2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(guider_ui.ui_Panel_Menu2,0, LV_PART_MAIN);

    static lv_style_t style_image_Menu2;
    lv_style_init(&style_image_Menu2);

    lv_style_set_border_width(&style_image_Menu2, 0);
    lv_obj_add_style(guider_ui.ui_Panel_Menu2, &style_image_Menu2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(guider_ui.ui_Panel_Menu2, &ui_img_img_menu_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Menu_Knob2

    guider_ui.ui_Menu_Knob2 = lv_obj_create(guider_ui.ui_Panel_Menu2);

    lv_obj_set_width(guider_ui.ui_Menu_Knob2, 8);
    lv_obj_set_height(guider_ui.ui_Menu_Knob2, 8);

    lv_obj_set_x(guider_ui.ui_Menu_Knob2, -7);
    lv_obj_set_y(guider_ui.ui_Menu_Knob2, -48);

    lv_obj_set_align(guider_ui.ui_Menu_Knob2, LV_ALIGN_CENTER);

    lv_obj_clear_flag(guider_ui.ui_Menu_Knob2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(guider_ui.ui_Menu_Knob2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    // guider_ui.ui_Arc_Battery1

//    guider_ui.ui_Arc_Battery1 = lv_arc_create(guider_ui.ui_Anim_On1);
//
//    lv_obj_set_width(guider_ui.ui_Arc_Battery1, 370);
//    lv_obj_set_height(guider_ui.ui_Arc_Battery1, 370);
//
//    lv_obj_set_x(guider_ui.ui_Arc_Battery1, 0);
//    lv_obj_set_y(guider_ui.ui_Arc_Battery1, 0);
//
//    lv_obj_set_align(guider_ui.ui_Arc_Battery1, LV_ALIGN_CENTER);
//
//    lv_obj_add_flag(guider_ui.ui_Arc_Battery1, LV_OBJ_FLAG_ADV_HITTEST);
//
//    lv_arc_set_range(guider_ui.ui_Arc_Battery1, 0, 100);
//    lv_arc_set_value(guider_ui.ui_Arc_Battery1, 80);
//    lv_arc_set_bg_angles(guider_ui.ui_Arc_Battery1, 0, 50);
//    lv_arc_set_rotation(guider_ui.ui_Arc_Battery1, 245);
//
//    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Battery1, lv_color_hex(0x4A4C4A), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Battery1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Battery1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
//
//    lv_obj_set_style_arc_color(guider_ui.ui_Arc_Battery1, lv_color_hex(0x1099E6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_opa(guider_ui.ui_Arc_Battery1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//    lv_obj_set_style_arc_rounded(guider_ui.ui_Arc_Battery1, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//
//    lv_obj_set_style_bg_color(guider_ui.ui_Arc_Battery1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(guider_ui.ui_Arc_Battery1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

   // guider_ui.ui_Image_Sec


}

void ui_Screen_LowPower(void){
    // ui_S1_Watch_Digital
    guider_ui.ui_SLowPower = lv_obj_create(NULL);
    lv_obj_clear_flag(guider_ui.ui_SLowPower, LV_OBJ_FLAG_SCROLLABLE);

   // lv_obj_add_event_cb(guider_ui.ui_S1_Watch_Digital, ui_event_S1_Watch_Digital, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(guider_ui.ui_SLowPower, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.ui_SLowPower, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    // guider_ui.ui_Image_NXP

    guider_ui.ui_Image_NXPLP = lv_img_create(guider_ui.ui_SLowPower);
    lv_img_set_src(guider_ui.ui_Image_NXPLP, &_img_nxpLP_65x23);

    lv_obj_set_width(guider_ui.ui_Image_NXPLP, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_NXPLP, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_NXPLP, -130);
    lv_obj_set_y(guider_ui.ui_Image_NXPLP, 0);

    lv_obj_set_align(guider_ui.ui_Image_NXPLP, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_NXPLP, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_NXPLP, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_NXPLP, 0, 0);

 // guider_ui.ui_Image_Sec

    guider_ui.ui_Image_SecLP = lv_img_create(guider_ui.ui_SLowPower);
    lv_img_set_src(guider_ui.ui_Image_SecLP, &_img_clockwise_secLP_31x180);

    lv_obj_set_width(guider_ui.ui_Image_SecLP, 31);
    lv_obj_set_height(guider_ui.ui_Image_SecLP, 180);

    lv_obj_set_x(guider_ui.ui_Image_SecLP, 0);
    lv_obj_set_y(guider_ui.ui_Image_SecLP, -66);

    lv_obj_set_align(guider_ui.ui_Image_SecLP, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_SecLP, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_SecLP, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_SecLP, 16, 156);


    lv_img_set_angle(guider_ui.ui_Image_SecLP, 400);

    // guider_ui.ui_Image_Hour

    guider_ui.ui_Image_HourLP = lv_img_create(guider_ui.ui_SLowPower);
    lv_img_set_src(guider_ui.ui_Image_HourLP, &_img_clockwise_hourLP_18x98);

    lv_obj_set_width(guider_ui.ui_Image_HourLP, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_HourLP, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_HourLP, 0);
    lv_obj_set_y(guider_ui.ui_Image_HourLP, -50);

    lv_obj_set_align(guider_ui.ui_Image_HourLP, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_HourLP, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_HourLP, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_HourLP, 9, 98);

    // guider_ui.ui_Image_Min

    guider_ui.ui_Image_MinLP = lv_img_create(guider_ui.ui_SLowPower);
    lv_img_set_src(guider_ui.ui_Image_MinLP, &_img_clockwise_minLP_18x157);

    lv_obj_set_width(guider_ui.ui_Image_MinLP, LV_SIZE_CONTENT);
    lv_obj_set_height(guider_ui.ui_Image_MinLP, LV_SIZE_CONTENT);

    lv_obj_set_x(guider_ui.ui_Image_MinLP, 1);
    lv_obj_set_y(guider_ui.ui_Image_MinLP, -80);

    lv_obj_set_align(guider_ui.ui_Image_MinLP, LV_ALIGN_CENTER);

    lv_obj_add_flag(guider_ui.ui_Image_MinLP, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(guider_ui.ui_Image_MinLP, LV_OBJ_FLAG_SCROLLABLE);

    lv_img_set_pivot(guider_ui.ui_Image_MinLP, 9, 157);

}
