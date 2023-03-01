/*
 * Copyright 2023 NXP
 *
 * SPDX-LICENSE-IDENTIFIER: BSD-3-Clause
 *
 */

/**
 * @file ui_Weather.h
 *
 */
#ifndef _UI_WHEATHER_H_
#define _UI_WHEATHER_H_
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
/*! @brief Defines for length of the strings.*/
#define FIRSTPOSITION 	0
#define SECONDPOSITION 	1
#define TIRDPOSITION 	2
#define STRINGLENGTH	3
#define EMPTYVALUE		0	
/**********************
 *      TYPEDEFS
 **********************/
  typedef enum {
	kSun_SWeather,
	kCloud_SWeather,
	kRain_SWeather,
    kLast_SWeather,
}ui_names_weathers;




/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * Called when a change in the Temp label value is required
 * @param uint16_t valueCourrent 0 to 99
 * @param uint16_t valueMax 0 to 99
 * @param uint16_t valueMin 0 to 99
 */
 void ui_Set_Temperature_Value(uint16_t valueCourrent, uint16_t valueMax, uint16_t valueMin);
 /**
  * Called when a cast is required in ui_Set_Temperature_Value funtion
  * @param uint16_t value 0 to 99
  */
 void Cast_TempValue_IntToString(uint16_t value);
 /**
  * Called when a change in the icon image is required
  * @param ui_names_weathers WeatherName names in ui_names_weathers enum
  */
 void ui_Change_Wheather_ScreenWeather(ui_names_weathers IconName);

 void Set_Position(char strLocationName[]);
/**********************
 * GLOBAL VARIABLES
 **********************/




#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_UI_WHEATHER_H_*/
