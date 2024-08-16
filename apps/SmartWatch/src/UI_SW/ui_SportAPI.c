/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*********************
 *      INCLUDES
 *********************/
 #include "ui_SportAPI.h"
#include <lvgl.h>

 #include "gui_guider.h"
 /*********************
 *   GLOBAL VARIABLES
 *********************/
 extern lv_ui guider_ui;
 uint8_t u8Uni=EMPTYVALUECERO;
 uint8_t u8Dec=EMPTYVALUECERO;
 uint8_t u8Cen=EMPTYVALUECERO;
 uint8_t u8Mil=EMPTYVALUECERO;
 char strSetLabel[STRINGLENGTH5];
//#include "fsl_debug_console.h"
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
 * Called when a change in the value of a parameter of S9 Sport
 * @param ui_arc_names Parameter_Name Name of the Parameter defined in ui_parameters_names enum
 * @param uint16_t value from 0 to 1024
 * kSport_Calories Values between 0 and 1024
 * kSport_Distance Values between 0 and 50
 * kSport_Duration Values between 0 and 180
 * kSport_Pulse Values between 0 and 180
 */
 void  ui_Set_Parameter_Value(ui_parameters_names Parameter_Name, uint16_t value){

    switch (Parameter_Name) {
        case kSport_Calories:
            lv_arc_set_value(guider_ui.ui_Arc_Calorie, Set_Arc_Value(MAXIMUNVALUECALORIES, value));
            Cast_Int_to_String(value, kSport_Calories);
            lv_label_set_text(guider_ui.ui_Label_Calorie_Number, strSetLabel);
        break; 
        case kSport_Distance:
        	Cast_Int_to_String(value, kSport_Distance);
            lv_arc_set_value(guider_ui.ui_Arc_Distance, Set_Arc_Value(MAXIMUNVALUEDISTANCE, value));
            lv_label_set_text(guider_ui.ui_Label_Distance_Number, strSetLabel);
        break;
        case kSport_Duration:
        	 Cast_Int_to_String(value, kSport_Duration);
             lv_arc_set_value(guider_ui.ui_Arc_Duration, Set_Arc_Value(MAXIMUNVALUEDURATION, value));
        break; 
        case kSport_Pulse:
            lv_arc_set_value(guider_ui.ui_Arc_Pusle, Set_Arc_Value(MAXIMUNVALUEPULSE, value));
            Cast_Int_to_String(value, kSport_Pulse);
            lv_label_set_text(guider_ui.ui_Label_Pulse_Number, strSetLabel);
        break; 
        case kSport_Last:
        	//Nothing to do
        break; 
    }
    if(guider_ui.ui_S9_Sport == lv_disp_get_scr_act(NULL)){
    	lv_refr_now(NULL);
    }
 }
 /**
  * Called when a change in the value of a parameter of S9 Sport
  * @param uint16_t Value 0 to 1024
  * @param ui_arc_names Parameter_Name Name of the Parameter defined in ui_parameters_names enum
  */
 void Cast_Int_to_String(uint16_t Value, ui_parameters_names Parameter_Name){
        
        switch (Parameter_Name) {
        case kSport_Calories:
        	Cast_TempInt_ToString_Value(Value);
        break; 
        case kSport_Distance:
        	Cast_TempInt_ToString_Value(Value);
        	strSetLabel[FOURTHPOSITION]  = 'k';
        	strSetLabel[FIFTHPOSITION]  = 'm';
        break;
        case kSport_Duration:
        	Set_Time_Label(Value);
        break; 
        case kSport_Pulse:
        	Cast_TempInt_ToString_Value(Value);
        break; 
        case kSport_Last:
        	//Nothing to do
        break; 
    }

 }
 /**
  * Called when a cast in the Cast_Int_to_String is required
  * @param uint16_t value 0 to 1024
  */
 void Cast_TempInt_ToString_Value(uint16_t value){

	strSetLabel[FIRSTPOSITION] =   ' ';
	strSetLabel[SECONDPOSITION]=   ' ';
	strSetLabel[TIRDPOSITION]  =   ' ';
	strSetLabel[FOURTHPOSITION]=   ' ';
	strSetLabel[FIFTHPOSITION] =   ' ';

if(value > 999){
	u8Mil = value / CONVERTIONNUMBERMIL;
    value = value - (u8Mil*CONVERTIONNUMBERMIL);

	u8Cen = value / CONVERTIONNUMBERCEN;
    value = value - (u8Cen*CONVERTIONNUMBERCEN);

    u8Dec = value / CONVERTIONNUMBER;
    u8Uni =(value -(u8Dec*CONVERTIONNUMBER));


	strSetLabel[FIRSTPOSITION] =  u8Mil  +'0';
    strSetLabel[SECONDPOSITION]=  u8Cen  +'0';
    strSetLabel[TIRDPOSITION]  =  u8Dec  +'0';
    strSetLabel[FOURTHPOSITION]=  u8Uni  +'0';
}else
if(value > 99){

	u8Cen = value / CONVERTIONNUMBERCEN;
    value = value - (u8Cen*CONVERTIONNUMBERCEN);

    u8Dec = value / CONVERTIONNUMBER;
    u8Uni =(value -(u8Dec*CONVERTIONNUMBER));


	strSetLabel[FIRSTPOSITION] =  u8Cen  +'0';
    strSetLabel[SECONDPOSITION]=  u8Dec  +'0';
    strSetLabel[TIRDPOSITION]  =  u8Uni  +'0';
} else
if(value < 99){

    u8Dec = value / CONVERTIONNUMBER;
    u8Uni =(value -(u8Dec*CONVERTIONNUMBER));


	strSetLabel[FIRSTPOSITION] =  u8Dec  +'0';
    strSetLabel[SECONDPOSITION]=  u8Uni  +'0';

}

 }
 /**
  * Called when a convert of percentaje of use in Arcs is required
  * @param uint16_t u16Maximun 0 to 1024 Value Maximun to convert
  * @param uint16_t u16Value 0 to 1024 Value to convert
  * @return uint16_t u16Value Value converted
  */
 uint16_t Set_Arc_Value(uint16_t u16Maximun, uint16_t u16Value){

	 u16Value = (u16Value*CONVERTIONNUMBERCEN) / u16Maximun;

	 return u16Value;
 }
 /**
  * Called when a convertion from minutes to hours and minutes is required
  * @param uint16_t u16value 0 to 180
  */
 void Set_Time_Label(uint16_t u16value){
	 uint8_t u8Hours=0;
	 uint8_t u8Min=0;
	 u8Hours = u16value / HOURVALUE;
	 u8Min = u16value - (u8Hours * HOURVALUE);

	 Set_Hours_Minutes_To_String(u8Hours, u8Min);
     lv_label_set_text(guider_ui.ui_Label_Duration_Number, strSetLabel);
 }
 /**
  * Called when a cast int to string in Label Duration Number is required
  * @param uint8_t u8Hours 0 to 3
  * @param uint8_t u8Min 0 to 59
  */
 void Set_Hours_Minutes_To_String(uint8_t u8Hours, uint8_t u8Min){

		strSetLabel[FIRSTPOSITION] =   ' ';
		strSetLabel[SECONDPOSITION]=   ' ';
		strSetLabel[TIRDPOSITION]  =   ':';
		strSetLabel[FOURTHPOSITION]=   ' ';
		strSetLabel[FIFTHPOSITION] =   ' ';

		u8Dec = u8Hours / CONVERTIONNUMBER;
		u8Uni = u8Hours - u8Dec*CONVERTIONNUMBER;

		strSetLabel[FIRSTPOSITION] =  u8Dec  +'0';
	    strSetLabel[SECONDPOSITION]=  u8Uni  +'0';


		u8Dec = u8Min / CONVERTIONNUMBER;
		u8Uni = u8Min - u8Dec*CONVERTIONNUMBER;

		strSetLabel[FOURTHPOSITION] =  u8Dec  +'0';
	    strSetLabel[FIFTHPOSITION]  =  u8Uni  +'0';
 }
