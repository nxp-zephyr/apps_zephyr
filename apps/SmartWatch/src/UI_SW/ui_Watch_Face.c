/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*********************
 *      INCLUDES
 *********************/
 #include "ui_Watch_Face.h"
 #include <lvgl.h>

 #include "gui_guider.h"
 /*********************
 *    GLOBAL VARIABLES
 *********************/
 extern lv_ui guider_ui;
 uint8_t u8Dec_Time=EMPTYVALUE;
 uint8_t u8Uni_Time=EMPTYVALUE;
 uint8_t u8Dec_batt=EMPTYVALUE;
 uint8_t u8Uni_batt=EMPTYVALUE;
 char strVal_Temp_Watch_Face[STRINGLENGTHTEMP];
 char strVal_TimeHours[STRINGLENGTH2];
 char strVal_TimeMinutes[STRINGLENGTH2];
 char StrDate[STRINGLENGTHDATE];
 char Strbatt[STRINGLENGTHDATE];
 uint32_t HourAngle=EMPTYVALUE;
 uint32_t MinAngle=EMPTYVALUE;

/**********************
 *      TYPEDEFS
 **********************/
 
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
 * Called when a change in the time is required 
 * @param uint16_t Hours 0 to 24
 * @param uint16_t Minutes 0 to 59
 */
 void ui_Label_Set_Time(uint16_t Hours, uint16_t Minutes){
     if(Hours <= MAXIMUNHOURSVALUE && Minutes <= MAXIMUNMINUTESVALUE){
		Cast_TempInt_ToString(Hours, Minutes);
    
       lv_label_set_text(guider_ui.ui_Label_Hour, strVal_TimeHours);
     
       strVal_TimeHours[0]=strVal_TimeMinutes[0];
       strVal_TimeHours[1]=strVal_TimeMinutes[1];

       //lv_label_set_text(guider_ui. ui_Label_Minute, strVal_TimeMinutes);
        

        set_angle_clock(Hours,  Minutes);
        lv_img_set_angle(guider_ui.ui_Image_Hour, HourAngle);
        lv_img_set_angle(guider_ui.ui_Image_Min, (MinAngle));

     }
 }
 /**
 * Called when a change in ARC battery percentage is required 
 * @param uint16_t Hours 0 to 100
 */
 void ui_Battery_Set_Percentage(uint16_t value){
  lv_arc_set_value(guider_ui.ui_Arc_Battery, value);
  //lv_arc_set_value(guider_ui.ui_Arc_Battery1, value);
  cast_int_string(value);
  lv_label_set_text(guider_ui.ui_Label_Power1, Strbatt);
  lv_label_set_text(guider_ui.ui_Label_Power, Strbatt);
  if(guider_ui.ui_S1_Watch_Digital == lv_disp_get_scr_act(NULL)){
  	lv_refr_now(NULL);
  }


 }
 /**
 * Called when a cast in ui_Label_Set_Time is required 
 * @param uint16_t value1 0 to 24
 * @param uint16_t value2 0 to 59
 */
 void Cast_TempInt_ToString(uint16_t value1, uint16_t value2){
   
    u8Dec_Time=value1/CONVERTIONNUMBER;
    u8Uni_Time=(value1-(u8Dec_Time*CONVERTIONNUMBER));

    strVal_TimeHours[FIRSTPOSITION]=u8Dec_Time+'0';
    strVal_TimeHours[SECONDPOSITION]=u8Uni_Time+'0';

    u8Dec_Time=value2/CONVERTIONNUMBER;
    u8Uni_Time=(value2-(u8Dec_Time*CONVERTIONNUMBER));

    strVal_TimeMinutes[FIRSTPOSITION]=u8Dec_Time+'0';
    strVal_TimeMinutes[SECONDPOSITION]=u8Uni_Time+'0';

}
 /**
 * Called when a change in ARC Step Count percentage is required 
 * @param uint16_t Hours 0 to 100
 */
void ui_arc_Set_StepCount(uint16_t value){
    lv_arc_set_value(guider_ui.ui_Arc_Step_Count, value);
    lv_arc_set_value(guider_ui.ui_Arc_Step_Count1, value);
    //lv_event_send(guider_ui.ui_Arc_Step_Count, LV_EVENT_REFRESH, NULL);
    if(guider_ui.ui_S1_Watch_Digital == lv_disp_get_scr_act(NULL)){
    	lv_refr_now(NULL);
    }
    if( guider_ui.ui_S2_Watch_Analog == lv_disp_get_scr_act(NULL)){
    	 lv_scr_load(guider_ui.ui_S2_Watch_Analog);
    }

}
/**
 * Called when a change in the icon of the weather is required 
 * @param ui_icons_names IconName of the icons defined in ui_icons_names enum
 */
void ui_Change_Wheather_Icon(ui_icons_names IconName){
    switch(IconName){
    case kIconSun:
    lv_img_set_src(guider_ui.ui_Image_Weather, &_icn_weather_2_41x38);
    lv_img_set_src(guider_ui.ui_Image_Weather1, &_icn_weather_2_41x38);
    break;
    case kIconCloud:
    lv_img_set_src(guider_ui.ui_Image_Weather, &ui_img_icn_weather_1_png);
    lv_img_set_src(guider_ui.ui_Image_Weather1, &ui_img_icn_weather_1_png);
    break;
    case kIconRain:
        lv_img_set_src(guider_ui.ui_Image_Weather, &_icn_weather_3_41x38);
        lv_img_set_src(guider_ui.ui_Image_Weather1, &_icn_weather_3_41x38);
    break;
    case kIcon_Last:
    //Nothing to do
    break;
    }
}
/**
 * Called when a change in the date is required 
 * @param uint8_t Mont value between 1 and 12
 * @param uint8_t Day value between 1 and 31
 * @param char weekday string leg maximum 3 day of the week
 */
void ui_Set_Date(uint8_t Month, uint8_t Day, char Weekday[]){
     lv_label_set_text(guider_ui.ui_Label_Week, Weekday);
     lv_label_set_text(guider_ui.ui_Label_Week1, Weekday);
     Cast_TempInt_ToString_Date(Month, Day);
     lv_label_set_text(guider_ui.ui_Label_Date, StrDate);
     lv_label_set_text(guider_ui.ui_Label_Date1, StrDate);

}
 /**
 * Called when a cast in ui_Set_Date is required 
 * @param uint8_t value1 0 to 12
 * @param uint8_t value2 0 to 31
 */
void Cast_TempInt_ToString_Date(uint8_t value1, uint8_t value2){
    u8Dec_Time=value1/CONVERTIONNUMBER;
    u8Uni_Time=(value1-(u8Dec_Time*CONVERTIONNUMBER));
    StrDate[FIRSTPOSITION]=u8Dec_Time+'0';
    StrDate[SECONDPOSITION]=u8Uni_Time+'0';

    u8Dec_Time=value2/CONVERTIONNUMBER;
    u8Uni_Time=(value2-(u8Dec_Time*CONVERTIONNUMBER));

    StrDate[FOURTHPOSITION]=u8Dec_Time+'0';
    StrDate[FIFTHPOSITION]=u8Uni_Time+'0';
    StrDate[TIRDPOSITION]='/';
}
 /**
 * Called when a change is required in the courrent temperature 
 * @param uint8t value0 to 99
 */
void ui_Set_CurrentTemperature(uint8_t value){
    Cast_TempInt_ToString_Temp(value);
    lv_label_set_text(guider_ui.ui_Label_Degree, strVal_Temp_Watch_Face);
    lv_label_set_text(guider_ui.ui_Label_Degree1, strVal_Temp_Watch_Face);
}

 /**
 * Called when a cast in ui_Label_Set_Time is required 
 * @param uint8_t value1 0 to 99
 */
 void Cast_TempInt_ToString_Temp(uint8_t value1){
   
    u8Dec_Time=value1/CONVERTIONNUMBER;
    u8Uni_Time=(value1-(u8Dec_Time*CONVERTIONNUMBER));

    strVal_Temp_Watch_Face[FIRSTPOSITION]=u8Dec_Time+'0';
    strVal_Temp_Watch_Face[SECONDPOSITION]=u8Uni_Time+'0';
    //causing warnings: strVal_Temp_Watch_Face[TIRDPOSITION]='°';
    strcpy(&(strVal_Temp_Watch_Face[TIRDPOSITION]), "°");
}
 void set_angle_clock(uint16_t Hours, uint16_t Minutes){
	 if(Hours>12){
		 Hours = Hours - 12;
	 }
	 HourAngle = Hours*300;
	 MinAngle = Minutes*60;

	 if(HourAngle > 360){HourAngle = HourAngle - 3600;}
	 if(MinAngle > 360){MinAngle = MinAngle - 3600;}
 }
 void cast_int_string(uint16_t value){
	 Strbatt[FIRSTPOSITION] = 00;
	 Strbatt[SECONDPOSITION]= 00;
	 Strbatt[TIRDPOSITION]  = 00;
	 Strbatt[FOURTHPOSITION]= 00;
	 if(value<99){
	    u8Dec_batt=value/CONVERTIONNUMBER;
	    u8Uni_batt=( (char)value -(u8Dec_batt*CONVERTIONNUMBER));
	    Strbatt[FIRSTPOSITION] =u8Dec_batt + '0';
	    Strbatt[SECONDPOSITION]=u8Uni_batt + '0';
	    Strbatt[TIRDPOSITION]  = '%';
	 }else{
		 Strbatt[FIRSTPOSITION] = '1';
		 Strbatt[SECONDPOSITION]= '0';
		 Strbatt[TIRDPOSITION]  = '0';
		 Strbatt[FOURTHPOSITION]  = '%';
	 }
 }
