/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * @file ui_EKG.c
 */

/*********************
 *      INCLUDES
 *********************/
 #include "ui_EKG.h"
 #include <lvgl.h>

 #include "gui_guider.h"
 /*********************
 *      DEFINES
 *********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/
extern lv_ui guider_ui;
char strBPMValue[STRINGLENGTH3];
uint8_t u8Cen_BPM=EMPTYVALUE;
uint8_t u8Dec_BPM=EMPTYVALUE;
uint8_t u8Uni_BPM=EMPTYVALUE;

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
 * Called when a change in the BPM value is required.
 * @param uint16_t valueCourrent 0 to 99
 */
void ui_Change_BPM(uint16_t u8BPM_Value){
	uint16_t u8IntervalRR=0;

	castIntToString(u8BPM_Value);
	lv_label_set_text(guider_ui.ui_Label_Seat_Number2, strBPMValue);
	lv_label_set_text(guider_ui.ui_Label_EKG_Beat_Number, strBPMValue);

	u8IntervalRR = 60000/u8BPM_Value;
	castIntToString(u8IntervalRR);
	lv_label_set_text(guider_ui.ui_Label_EKG_Interval_Number, strBPMValue);
}
/**
 * Called when a cast in the ui_Change_BPM funcion is required.
 * @param uint16_t valueCourrent 0 to 99
 */
void castIntToString(uint16_t u8ValBPM){

	u8Cen_BPM = u8ValBPM / CONVERTIONNUMBERCEN;
	u8ValBPM = u8ValBPM - (u8Cen_BPM * CONVERTIONNUMBERCEN);

    u8Dec_BPM=u8ValBPM/CONVERTIONNUMBER;
    u8Uni_BPM=(u8ValBPM-(u8Dec_BPM * CONVERTIONNUMBER));

    strBPMValue[FIRSTPOSITION] =u8Cen_BPM + '0';
    strBPMValue[SECONDPOSITION]=u8Dec_BPM + '0';
    strBPMValue[TIRDPOSITION]  =u8Uni_BPM + '0';
}
