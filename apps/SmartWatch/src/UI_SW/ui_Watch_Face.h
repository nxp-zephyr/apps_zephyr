/*
 * Copyright 2023 NXP
 *
 * SPDX-LICENSE-IDENTIFIER: BSD-3-Clause
 *
 */

/**
 * @file ui_Watch_Face.h
 *
 */
#ifndef _UI_WATCH_FACE_H_
#define _UI_WATCH_FACE_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/
 /*! @brief Macros used in code. */
 #define FIRSTPOSITION 	      0
 #define SECONDPOSITION       1
 #define TIRDPOSITION         2
 #define FOURTHPOSITION       3
 #define FIFTHPOSITION        4
 #define STRINGLENGTH2	      2
 #define STRINGLENGTHTEMP	  4	
 #define EMPTYVALUE		      0	
 #define MAXIMUNHOURSVALUE    24
 #define MAXIMUNMINUTESVALUE  59
 #define STRINGLENGTHDATE	  5
 #define CONVERTIONNUMBER	  10

/**********************
 *      TYPEDEFS
 **********************/
 /*! @brief Enumerate the icons to use in S1 Watch Face.*/
 typedef enum {
	kIconSun,
	kIconCloud,
	kIconRain,
    kIcon_Last,
}ui_icons_names;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

 /**
 * Called when a change in the time is required 
 * @param uint16_t Hours 0 to 24
 * @param uint16_t Minutes 0 to 59
 */
 void ui_Label_Set_Time(uint16_t Hours, uint16_t Minutes);
 /**
 * Called when a cast in ui_Label_Set_Time is required 
 * @param uint16_t value1 0 to 24
 * @param uint16_t value2 0 to 59
 */
 void Cast_TempInt_ToString(uint16_t value1, uint16_t value2);
 /**
 * Called when a change in ARC battery percentage is required
 * @param uint16_t Hours 0 to 100
 */
 void ui_Battery_Set_Percentage(uint16_t value);
  /**
 * Called when a change in ARC Step Count percentage is required 
 * @param uint16_t Hours 0 to 100
 */
void ui_arc_Set_StepCount(uint16_t value);
/**
 * Called when a change in the icon of the weather is required 
 * @param ui_icons_names IconName of the icons defined in ui_icons_names enum
 */
void ui_Change_Wheather_Icon(ui_icons_names IconName);
/**
 * Called when a change in the date is required 
 * @param uint8_t Mont value between 1 and 12
 * @param uint8_t Day value between 1 and 31
 * @param char weekday string leg maximum 3 day of the week
 */
void ui_Set_Date(uint8_t Month, uint8_t Day, char Weekday[]);
 /**
 * Called when a cast in ui_Set_Date is required 
 * @param uint8_t value1 0 to 12
 * @param uint8_t value2 0 to 31
 */
void Cast_TempInt_ToString_Date(uint8_t value1, uint8_t value2);
 /**
 * Called when a change is required in the courrent temperature 
 * @param uint8t value0 to 99
 */
void ui_Set_CurrentTemperature(uint8_t value);
 /**
 * Called when a cast in ui_Label_Set_Time is required 
 * @param uint16_t value1 0 to 99
 */
void Cast_TempInt_ToString_Temp(uint8_t value1);
void set_angle_clock(uint16_t Hours, uint16_t Minutes);
void cast_int_string(uint16_t value);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_UI_WATCH_FACE_H_*/
