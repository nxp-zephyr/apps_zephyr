/*
 * Copyright 2023 NXP
 *
 * SPDX-LICENSE-IDENTIFIER: BSD-3-Clause
 *
 */

/**
 * @file ui_SportAPI.h
 *
 */
#ifndef _UI_SPORT_H_
#define _UI_SPORT_H_
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
/*!
 * @brief Defines used in ui_SportAPI.c
 */
 #define FIRSTPOSITION 		  0
 #define SECONDPOSITION       1
 #define TIRDPOSITION         2
 #define FOURTHPOSITION       3
 #define FIFTHPOSITION        4
 #define CONVERTIONNUMBER	  10
 #define CONVERTIONNUMBERCEN  100
 #define CONVERTIONNUMBERMIL  1000
 #define STRINGLENGTH5		  5
 #define EMPTYVALUECERO	      0
 #define MAXIMUNVALUECALORIES 1024
 #define MAXIMUNVALUEPULSE    180
 #define MAXIMUNVALUEDISTANCE 50
 #define MAXIMUNVALUEDURATION 180
 #define HOURVALUE			  60
/**********************
 *      TYPEDEFS
 **********************/

/*! @brief Enumerate the arcs from S9_Sport.*/
typedef enum {
	kSport_Calories,
	kSport_Distance,
	kSport_Duration,
	kSport_Pulse,
    kSport_Last,
}ui_parameters_names;

/**********************
 * GLOBAL PROTOTYPES
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
void ui_Set_Parameter_Value(ui_parameters_names Parameter_Name, uint16_t value);
/**
 * Called when a change in the value of a parameter of S9 Sport
 * @param uint16_t Value 0 to 1024
 * @param ui_arc_names Parameter_Name Name of the Parameter defined in ui_parameters_names enum
 */
void Cast_Int_to_String(uint16_t Value, ui_parameters_names Parameter_Name);
/**
 * Called when a cast in the Cast_Int_to_String is required
 * @param uint16_t value 0 to 1024
 */
void Cast_TempInt_ToString_Value(uint16_t value);
/**
 * Called when a convert of percentaje of use in Arcs is required
 * @param uint16_t u16Maximun 0 to 1024 Value Maximun to convert
 * @param uint16_t u16Value 0 to 1024 Value to convert
 * @return uint16_t u16Value Value converted
 */
uint16_t Set_Arc_Value(uint16_t u16Maximun, uint16_t u16Value);
/**
 * Called when a convertion from minutes to hours and minutes is required
 * @param uint16_t u16value 0 to 180
 */
void Set_Time_Label(uint16_t u8value);
/**
 * Called when a cast int to string in Label Duration Number is required
 * @param uint8_t u8Hours 0 to 3
 * @param uint8_t u8Min 0 to 59
 */
void Set_Hours_Minutes_To_String(uint8_t u8Hours, uint8_t u8Min);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_UI_SPORT_H_*/
