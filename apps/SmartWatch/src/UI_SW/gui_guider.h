/*
 * Copyright 2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#include "../../../../../modules/lib/gui/lvgl/src/lvgl.h"

#include <lvgl.h>
void complete_set(void);
typedef struct
{
	lv_obj_t * ui_S0_Splash;
	lv_obj_t * ui_Image_Bg_Splash;
	lv_obj_t * ui_Image_NXP_Logo1;
	lv_obj_t * ui_Image_NXP_Logo;
	lv_obj_t * ui_Label_MIMXRT595EVK;
	lv_obj_t * ui_Label_Smartwatch_Demo;
	lv_obj_t * ui_Label_Powered;
	lv_obj_t * ui_Panel_SLS_Logo;
	lv_obj_t * ui_Image_SLS_Logo;
    lv_obj_t * ui_S1_Watch_Digital;
    lv_obj_t * ui_Image_Bg;
    lv_obj_t * ui_Label_Minute;
    lv_obj_t * ui_S1_Content;
    lv_obj_t * ui_Label_Power;
    lv_obj_t * ui_Image_Flash;
    lv_obj_t * ui_Image_Sport;
    lv_obj_t * ui_Image_Label_Sport;
    lv_obj_t * ui_Image_Label_Messages;
    lv_obj_t * ui_Image_Notifi;
    lv_obj_t * ui_Image_Step;
    lv_obj_t * ui_Image_Weather;
    lv_obj_t * ui_Label_Date;
    lv_obj_t * ui_Label_Week;
    lv_obj_t * ui_Label_Degree;
    lv_obj_t * ui_Label_Step_Count;
    lv_obj_t * ui_Arc_Battery;
    lv_obj_t * ui_Arc_Step_Count;
    lv_obj_t * ui_Image2;
    lv_obj_t * ui_Label_Hour;
	lv_obj_t * ui_Label_Seconds;
    lv_obj_t * ui_Image_NXP;
    lv_obj_t * ui_S1_Buttons;
    lv_obj_t * ui_BTN_Messages;
    lv_obj_t * ui_BTN_Sport;
    lv_obj_t * ui_Panel_Menu1;
    lv_obj_t * ui_Menu_Knob1;
    lv_obj_t * ui_S2_Watch_Analog;
    lv_obj_t * ui_Image_Bg1;
    lv_obj_t * ui_Anim_On1;
    lv_obj_t * ui_Label_Power1;
    lv_obj_t * ui_Image_Flash1;
    lv_obj_t * ui_Image_Sport1;
    lv_obj_t * ui_Image_Label_Sport1;
    lv_obj_t * ui_Image_Label_Messages1;
    lv_obj_t * ui_Image_Notifi1;
    lv_obj_t * ui_Image_Step1;
    lv_obj_t * ui_Image_Weather1;
    lv_obj_t * ui_Image_NXP1;
    lv_obj_t * ui_Label_Date1;
    lv_obj_t * ui_Label_Week1;
    lv_obj_t * ui_Label_Degree1;
    lv_obj_t * ui_Label_Step_Count1;
    lv_obj_t * ui_Arc_Battery1;
    lv_obj_t * ui_Arc_Step_Count1;
    lv_obj_t * ui_Image_Hour;
    lv_obj_t * ui_Image_Min;
    lv_obj_t * ui_Image_Sec;
    lv_obj_t * ui_S2_Buttons;
    lv_obj_t * ui_BTN_Messages1;
    lv_obj_t * ui_BTN_Sport1;
    lv_obj_t * ui_Panel_Menu2;
    lv_obj_t * ui_Menu_Knob2;
    lv_obj_t * ui_S5_Weather;
    lv_obj_t * ui_Image_Cloud_Bg1;
    lv_obj_t * ui_Image_Cloud_Bg12;
    lv_obj_t * ui_Image_Sun;
    lv_obj_t * ui_Anim_Down_S5;
    lv_obj_t * ui_Label_Call_Name6;
    lv_obj_t * ui_Anim_On_S5;
    lv_obj_t * ui_Image_Label_Home2;
    lv_obj_t * ui_Image_Label_Select1;
    lv_obj_t * ui_Label_Deg;
    lv_obj_t * ui_Anim_Up_S5;
    lv_obj_t * ui_Image_Weather_Icon;
    lv_obj_t * ui_Label_Mostly;
    lv_obj_t * ui_Label_Max;
    lv_obj_t * ui_Label_Max_Number;
    lv_obj_t * ui_Label_Min;
    lv_obj_t * ui_Label_Min_Number;
    lv_obj_t * ui_S5_Buttons;
    lv_obj_t * ui_BTN_Home1;
    lv_obj_t * ui_BTN_Select1;
    lv_obj_t * ui_Panel_Menu3;
    lv_obj_t * ui_Menu_Knob3;
	lv_obj_t * ui_S9_Sport;
    lv_obj_t * ui_Image_Bg7;
	lv_obj_t * ui_Anim_Right_S9;
	lv_obj_t * ui_Panel_Fitness_Pulse;
	lv_obj_t * ui_Label_Pulse;
	lv_obj_t * ui_Label_Pulse_Number;
	lv_obj_t * ui_Image_Pulse;
	lv_obj_t * ui_Panel_Fitness_Duration;
	lv_obj_t * ui_Label_Duration;
	lv_obj_t * ui_Label_Duration_Number;
	lv_obj_t * ui_Image_Duration;
	lv_obj_t * ui_Panel_Fitness_Distance;
    lv_obj_t * ui_Label_Distance;
	lv_obj_t * ui_Label_Distance_Number;
	lv_obj_t * ui_Image_Distance;
	lv_obj_t * ui_Panel_Fitness_Calorie;
	lv_obj_t * ui_Label_Calorie;
	lv_obj_t * ui_Label_Calorie_Number;
	lv_obj_t * ui_Image_Calorie;
	lv_obj_t * ui_Header_S9;
	lv_obj_t * ui_Image_Header_Shadow4;
    lv_obj_t * ui_Image_Header4;
	lv_obj_t * ui_Label_Fitness;
	lv_obj_t * ui_Image_Label_Home6;
	lv_obj_t * ui_Image_Label_Start;
	lv_obj_t * ui_Anim_On_S9;
	lv_obj_t * ui_Arc_Calorie;
	lv_obj_t * ui_Arc_Distance;
	lv_obj_t * ui_Arc_Duration;
	lv_obj_t * ui_Arc_Pusle;
	lv_obj_t * ui_S9_Buttons;
	lv_obj_t * ui_BTN_Home5;
	lv_obj_t * ui_BTN_StartStop;
	lv_obj_t * ui_Panel_Menu4;
	lv_obj_t * ui_Menu_Knob4;
	lv_obj_t * ui_S11_Music;
	lv_obj_t * ui_Anim_On_S11;
	lv_obj_t * ui_Image_Audio_Album_1;
	lv_obj_t * ui_Btn_Audio_Play;
	lv_obj_t * ui_Image_Audio_Back;
	lv_obj_t * ui_Image_Audio_Next;
	lv_obj_t * ui_Image_Audio_Next_btn;
	lv_obj_t * ui_Image_Label_Home_S11;
	lv_obj_t * ui_Image_Home_S11;
	lv_obj_t * ui_Anim_Down_S11;
	lv_obj_t * ui_Panel_Audio_Time_Mask;
	lv_obj_t * ui_Arc_Audio_Time;
	lv_obj_t * ui_Label_Audio_Arist;
	lv_obj_t * ui_Label_Audio_Title;
	lv_obj_t * ui_Anim_Up_S11;
	lv_obj_t * ui_Image_Label_Volume1;
	lv_obj_t * ui_Panel_Volume_Mask2;
	lv_obj_t * ui_Arc_Volume1;
	lv_obj_t * ui_Label_Audio_Time;
	lv_obj_t * ui_Image_Audio_RND;
	lv_obj_t * ui_S11_Buttons;
	lv_obj_t * ui_BTN_Home7;
	lv_obj_t * ui_Panel_Menu5;
	lv_obj_t * ui_Menu_Knob5;
	lv_obj_t * ui_S24_EKG;
	lv_obj_t * ui_Image_Bg21;
	lv_obj_t * ui_Anim_On_S24;
	lv_obj_t * ui_Image_EKG;
	lv_obj_t * ui_Anim_Up_S24;
	lv_obj_t * ui_Panel_Pulse;
	lv_obj_t * ui_Label_Pulse2;
	lv_obj_t * ui_Label_Seat_Number2;
	lv_obj_t * ui_Label_bpm;
	lv_obj_t * ui_Image_Heart1;
	lv_obj_t * ui_Image_Heart2;
	lv_obj_t * ui_Anim_Down_S24;
	lv_obj_t * ui_Panel_Arrival1;
	lv_obj_t * ui_Label_EKG_Beat_Count;
	lv_obj_t * ui_Label_EKG_Beat_Number;
	lv_obj_t * ui_Panel_Departure1;
	lv_obj_t * ui_Label_EKG_Interval;
	lv_obj_t * ui_Label_EKG_Interval_Number;
	lv_obj_t * ui_Header_S24;
	lv_obj_t * ui_Image_Header_Shadow17;
	lv_obj_t * ui_Image_Header17;
	lv_obj_t * ui_Label_Your_Flight2;
	lv_obj_t * ui_Image_Label_Home20;
	lv_obj_t * ui_S24_Buttons;
	lv_obj_t * ui_BTN_Home20;
	lv_obj_t * ui_Image_Arrow23;
	lv_obj_t * ui_Image_Arrow24;
	lv_obj_t * ui_SLowPower;
	lv_obj_t * ui_Image_NXPLP;
	lv_obj_t * ui_Image_SecLP;
	lv_obj_t * ui_Image_HourLP;
	lv_obj_t * ui_Image_MinLP;
} lv_ui;
//lv_ui guider_ui;

 LV_IMG_DECLARE(ui_img_img_bg_digital_png);    // assets\img_bg_digital.png
 LV_IMG_DECLARE(ui_img_icn_flash_png);    // assets\icn_flash.png
 LV_IMG_DECLARE(ui_img_icn_sport_png);    // assets\icn_sport.png
 LV_IMG_DECLARE(ui_img_text_sport_png);    // assets\text_sport.png
 LV_IMG_DECLARE(ui_img_text_message_png);    // assets\text_message.png
 LV_IMG_DECLARE(ui_img_icn_message_png);    // assets\icn_message.png
 LV_IMG_DECLARE(ui_img_icn_step_png);    // assets\icn_step.png
 LV_IMG_DECLARE(ui_img_icn_weather_1_png);    // assets\icn_weather_1.png
 LV_IMG_DECLARE(ui_img_img_clock_shadow_png);    // assets\img_clock_shadow.png
 LV_IMG_DECLARE(ui_img_img_nxp_png);    // assets\img_nxp.png
 LV_IMG_DECLARE(ui_img_img_menu_png);    // assets\img_menu.png
 LV_IMG_DECLARE(ui_img_img_bg_analog_png);    // assets\img_bg_analog.png
 LV_IMG_DECLARE(ui_img_img_clockwise_hour_png);    // assets\img_clockwise_hour.png
 LV_IMG_DECLARE(ui_img_img_clockwise_min_png);    // assets\img_clockwise_min.png
 LV_IMG_DECLARE(ui_img_img_clockwise_sec_png);    // assets\img_clockwise_sec.png
 LV_IMG_DECLARE(ui_img_icn_unmute_png);    // assets\icn_unmute.png
 LV_IMG_DECLARE(ui_img_icn_mute_png);    // assets\icn_mute.png
 LV_IMG_DECLARE(ui_img_img_call_erica_png);    // assets\img_call_erica.png
 LV_IMG_DECLARE(ui_img_icn_phone_png);    // assets\icn_phone.png
 LV_IMG_DECLARE(ui_img_text_endcall_png);    // assets\text_endcall.png
 LV_IMG_DECLARE(ui_img_text_home_png);    // assets\text_home.png
 LV_IMG_DECLARE(ui_img_icn_home_png);    // assets\icn_home.png
 LV_IMG_DECLARE(ui_img_text_volume_png);    // assets\text_volume.png
 LV_IMG_DECLARE(ui_img_img_bg_2_png);    // assets\img_bg_2.png
 LV_IMG_DECLARE(ui_img_img_avatar_1_png);    // assets\img_avatar_1.png
 LV_IMG_DECLARE(ui_img_img_avatar_2_png);    // assets\img_avatar_2.png
 LV_IMG_DECLARE(ui_img_img_avatar_3_png);    // assets\img_avatar_3.png
 LV_IMG_DECLARE(ui_img_img_avatar_4_png);    // assets\img_avatar_4.png
 LV_IMG_DECLARE(ui_img_img_header_bg_shadow_png);    // assets\img_header_bg_shadow.png
 LV_IMG_DECLARE(ui_img_img_header_bg_png);    // assets\img_header_bg.png
 LV_IMG_DECLARE(ui_img_text_favorites_png);    // assets\text_favorites.png
 LV_IMG_DECLARE(ui_img_img_cloud_png);    // assets\img_cloud.png
 LV_IMG_DECLARE(ui_img_img_sun_png);    // assets\img_sun.png
 LV_IMG_DECLARE(ui_img_text_select_png);    // assets\text_select.png
 LV_IMG_DECLARE(ui_img_icn_big_weather_cloud_png);    // assets\icn_big_weather_cloud.png

 LV_IMG_DECLARE(ui_img_img_line_1_png);    // assets\img_line_1.png
 LV_IMG_DECLARE(ui_img_icn_small_weather_1_png);    // assets\icn_small_weather_1.png
 LV_IMG_DECLARE(ui_img_icn_small_weather_2_png);    // assets\icn_small_weather_2.png
 LV_IMG_DECLARE(ui_img_img_arrow_right_png);    // assets\img_arrow_right.png
 LV_IMG_DECLARE(ui_img_img_arrow_left_png);    // assets\img_arrow_left.png
 LV_IMG_DECLARE(ui_img_icn_small_weather_3_png);    // assets\icn_small_weather_3.png
 LV_IMG_DECLARE(ui_img_text_ugm3_png);    // assets\text_ugm3.png
 LV_IMG_DECLARE(ui_img_icn_small_pulse_png);    // assets\icn_small_pulse.png
 LV_IMG_DECLARE(ui_img_icn_small_time_png);    // assets\icn_small_time.png
 LV_IMG_DECLARE(ui_img_icn_small_pos_png);    // assets\icn_small_pos.png
 LV_IMG_DECLARE(ui_img_icn_small_burn_png);    // assets\icn_small_burn.png
 LV_IMG_DECLARE(ui_img_text_start_stop_png);    // assets\text_start_stop.png
 LV_IMG_DECLARE(ui_img_img_line_2_png);    // assets\img_line_2.png
 LV_IMG_DECLARE(ui_img_img_audio_album_png);    // assets\img_audio_album.png
 LV_IMG_DECLARE(ui_img_icn_audio_play_png);    // assets\icn_audio_play.png
 LV_IMG_DECLARE(ui_img_img_pause_png);    // assets\img_pause.png
 LV_IMG_DECLARE(ui_img_icn_audio_back_png);    // assets\icn_audio_back.png
 LV_IMG_DECLARE(ui_img_icn_audio_next_png);    // assets\icn_audio_next.png
 LV_IMG_DECLARE(ui_img_text_audio_volume_png);    // assets\text_audio_volume.png
 LV_IMG_DECLARE(ui_img_icn_audio_rnd_png);    // assets\icn_audio_rnd.png
 LV_IMG_DECLARE(ui_img_img_bg_travel_png);    // assets\img_bg_travel.png
 LV_IMG_DECLARE(ui_img_img_plane_2_png);    // assets\img_plane_2.png
 LV_IMG_DECLARE(ui_img_img_line_3_png);    // assets\img_line_3.png
 LV_IMG_DECLARE(ui_img_img_qr_code_png);    // assets\img_qr_code.png
 LV_IMG_DECLARE(ui_img_img_nav_1_png);    // assets\img_nav_1.png
 LV_IMG_DECLARE(ui_img_img_map_png);    // assets\img_map.png
 LV_IMG_DECLARE(ui_img_img_small_nav_1_png);    // assets\img_small_nav_1.png
 LV_IMG_DECLARE(ui_img_img_card_1_png);    // assets\img_card_1.png
 LV_IMG_DECLARE(ui_img_img_card_2_png);    // assets\img_card_2.png
 LV_IMG_DECLARE(ui_img_img_payment_ok_png);    // assets\img_payment_ok.png
 LV_IMG_DECLARE(ui_img_icn_fitness_png);    // assets\icn_fitness.png
 LV_IMG_DECLARE(ui_img_icn_travel_png);    // assets\icn_travel.png
 LV_IMG_DECLARE(ui_img_img_chart_battery_png);    // assets\img_chart_battery.png
 LV_IMG_DECLARE(ui_img_img_find_device_png);    // assets\img_find_device.png
 LV_IMG_DECLARE(ui_img_img_find_device2_png);    // assets\img_find_device2.png
 LV_IMG_DECLARE(ui_img_icn_water_png);    // assets\icn_water.png
 LV_IMG_DECLARE(ui_img_img_bg_health_png);    // assets\img_bg_health.png
 LV_IMG_DECLARE(ui_img_img_ekg_png);    // assets\img_ekg.png
 LV_IMG_DECLARE(ui_img_img_heart_png);    // assets\img_heart.png
 LV_IMG_DECLARE(ui_img_img_stress_level_png);    // assets\img_stress_level.png
 LV_IMG_DECLARE(ui_img_icn_heart_png);    // assets\icn_heart.png
 LV_IMG_DECLARE(ui_img_img_chart_sleep_png);    // assets\img_chart_sleep.png
 LV_IMG_DECLARE(ui_img_img_bg_step_png);    // assets\img_bg_step.png
 LV_IMG_DECLARE(ui_img_img_step_small_png);    // assets\img_step_small.png
 LV_IMG_DECLARE(ui_img_img_menstrual_chart_png);    // assets\img_menstrual_chart.png
 LV_IMG_DECLARE(ui_img_img_whatsapp_png);    // assets\img_whatsapp.png
 LV_IMG_DECLARE(ui_img_icn_insta_png);    // assets\icn_insta.png
 LV_IMG_DECLARE(ui_img_icn_whatsapp_png);    // assets\icn_whatsapp.png
 LV_IMG_DECLARE(ui_img_img_stand_up_png);    // assets\img_stand_up.png
 LV_IMG_DECLARE(ui_img_img_car_lock_2_png);    // assets\img_car_lock_2.png
 LV_IMG_DECLARE(ui_img_img_car_lock_1_png);    // assets\img_car_lock_1.png
 LV_IMG_DECLARE(ui_img_img_car_png);    // assets\img_car.png
 LV_IMG_DECLARE(ui_img_img_bg_car_png);    // assets\img_bg_car.png
 LV_IMG_DECLARE(ui_img_img_red_btn_png);    // assets\img_red_btn.png
 LV_IMG_DECLARE(ui_img_img_green_btn_png);    // assets\img_green_btn.png
 LV_IMG_DECLARE(ui_img_img_mic_1_png);    // assets\img_mic_1.png
 LV_IMG_DECLARE(ui_img_img_mic_2_png);    // assets\img_mic_2.png
 LV_IMG_DECLARE(ui_img_img_mic_3_png);    // assets\img_mic_3.png
 LV_IMG_DECLARE(ui_img_icn_small_weather_1_png_data);
 LV_IMG_DECLARE(ui_img_icn_small_weather_2_png);
 LV_IMG_DECLARE(ui_img_icn_small_weather_3_png);
 LV_IMG_DECLARE(_coursewrkwavesfeb_dribbble_392x392);
 LV_IMG_DECLARE(_icn_weather_2_41x38);
 LV_IMG_DECLARE(_icn_weather_3_41x38);
 LV_IMG_DECLARE(_img_cloud_2_586x147);

LV_IMG_DECLARE(_img_clockwise_secLP_31x180);
LV_IMG_DECLARE(_img_clockwise_hourLP_18x98);
LV_IMG_DECLARE(_img_nxpLP_65x23);
LV_IMG_DECLARE(_img_clockwise_minLP_18x157);

LV_IMG_DECLARE(ui_img_img_squareline_png);
LV_IMG_DECLARE(ui_img_img_nxp_logo_big_png);
LV_IMG_DECLARE(ui_img_img_bg_png);
LV_IMG_DECLARE(_Zephyr_RTOS_logo_118x57);


 LV_FONT_DECLARE(ui_font_big_font);
 LV_FONT_DECLARE(ui_font_medium_font);
 LV_FONT_DECLARE(ui_font_number_bold);
 LV_FONT_DECLARE(ui_font_number_light);
 LV_FONT_DECLARE(ui_font_small_font);
 LV_FONT_DECLARE(lv_font_Montserrat_Light_40);

 
#ifdef __cplusplus
 "C" {
#endif

void setup_ui(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif
