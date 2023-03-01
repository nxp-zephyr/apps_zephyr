/*
 * Copyright 2023 NXP
 *
 * SPDX-LICENSE-IDENTIFIER: BSD-3-Clause
 *
 */

/**
 * @file ui_EKG.h
 *
 */
#ifndef _UI_EKG_H_
#define _UI_EKG_H_
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
/*! @brief Defines used in ui_EKG.c */
#define FIRSTPOSITION 	     0
#define SECONDPOSITION 	 	 1
#define TIRDPOSITION 	 	 2
#define STRINGLENGTH3		 3
#define EMPTYVALUE			 0
#define CONVERTIONNUMBERCEN  100
#define CONVERTIONNUMBER	 10
/**********************
 *      TYPEDEFS
 **********************/


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/
void ui_Change_BPM(uint16_t u8BPM_Value);
void castIntToString(uint16_t u8ValBPM);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_UI_EKG_H_*/
