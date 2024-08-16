/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*********************
 *      INCLUDES
 *********************/
 #include "ui_Weather.h"
#include <lvgl.h>

 #include "gui_guider.h"
 /*********************
 *      DEFINES
 *********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/
extern lv_ui guider_ui;
uint8_t u8Dec_Temp=EMPTYVALUE;
uint8_t u8Uni_Temp=EMPTYVALUE;
char strVal_Temp[STRINGLENGTH];
/**********************
 *  STATIC PROTOTYPES
 **********************/

 /**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
/**
 * Called when a change in the Temp label value is required
 * @param uint16_t valueCourrent 0 to 99
 * @param uint16_t valueMax 0 to 99
 * @param uint16_t valueMin 0 to 99
 */

 void ui_Set_Temperature_Value(uint16_t valueCourrent, uint16_t valueMax, uint16_t valueMin){
	Cast_TempValue_IntToString(valueCourrent);
    lv_label_set_text(guider_ui.ui_Label_Deg, strVal_Temp);

	Cast_TempValue_IntToString(valueMax);
    lv_label_set_text(guider_ui.ui_Label_Max_Number, strVal_Temp);

	Cast_TempValue_IntToString(valueMin);
    lv_label_set_text(guider_ui.ui_Label_Min_Number, strVal_Temp);

 }

/**
 * Called when a cast is required in ui_Set_Temperature_Value funtion
 * @param uint16_t value 0 to 99
 */

void Cast_TempValue_IntToString(uint16_t value){
   
    u8Dec_Temp=value/10;
    u8Uni_Temp=(value-(u8Dec_Temp*10));

    strVal_Temp[FIRSTPOSITION]=u8Dec_Temp+'0';
    strVal_Temp[SECONDPOSITION]=u8Uni_Temp+'0';
    strVal_Temp[TIRDPOSITION]=248;
}
/**
 * Called when a change in the icon image is required
 * @param ui_names_weathers WeatherName names in ui_names_weathers enum
 */
void ui_Change_Wheather_ScreenWeather(ui_names_weathers WeatherName){
    switch(WeatherName){
    case kSun_SWeather:
     lv_img_set_src(guider_ui.ui_Image_Weather_Icon, &ui_img_icn_small_weather_3_png);
     lv_label_set_text(guider_ui.ui_Label_Mostly, "Mostly Sunny");
    break;
    case kCloud_SWeather:
    lv_img_set_src(guider_ui.ui_Image_Weather_Icon, &ui_img_icn_small_weather_1_png);
    lv_label_set_text(guider_ui.ui_Label_Mostly, "Mostly Cloudy");
    break;
    case kRain_SWeather:
      lv_img_set_src(guider_ui.ui_Image_Weather_Icon, &ui_img_icn_small_weather_2_png);
      lv_label_set_text(guider_ui.ui_Label_Mostly, "Mostly Rainy");
    break;
    case kLast_SWeather:
    //Nothing to do
    break;
    }
}
/**
 * Called when a change in the position label is required
 * @param char strLocationName[] String type
 */
void Set_Position(char strLocationName[]){

	 lv_label_set_text(guider_ui.ui_Label_Call_Name6, strLocationName);
	    lv_obj_set_width(guider_ui.ui_Label_Call_Name6, LV_SIZE_CONTENT);
	    lv_obj_set_height(guider_ui.ui_Label_Call_Name6, LV_SIZE_CONTENT);

}
