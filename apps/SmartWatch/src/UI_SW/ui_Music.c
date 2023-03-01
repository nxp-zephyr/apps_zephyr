/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * @file ui_Music.c
 */

/*********************
 *      INCLUDES
 *********************/
 #include "ui_Music.h"
 #include <lvgl.h>

 #include "gui_guider.h"
 /*********************
 *      DEFINES
 *********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/
extern lv_ui guider_ui;

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
 * Called when a change in the courrent song
 * @param ui_names_songs SongName names in ui_names_songs enum
 */
void ui_Change_Song(ui_names_songs SongName){

	switch(SongName){
	case kDance_onTheMoon:
		lv_img_set_src(guider_ui.ui_Image_Audio_Album_1, &ui_img_img_audio_album_png);
		lv_label_set_text(guider_ui.ui_Label_Audio_Arist, "Erica Smith");
		lv_label_set_text(guider_ui.ui_Label_Audio_Title, "Dance on the moon");
	break;
	case kSong_2:
		lv_img_set_src(guider_ui.ui_Image_Audio_Album_1, &_coursewrkwavesfeb_dribbble_392x392);
		lv_label_set_text(guider_ui.ui_Label_Audio_Arist, "Jair Gudino");
		lv_label_set_text(guider_ui.ui_Label_Audio_Title, "New Music");

	break;
	case kLast_Song:
	//Nothing to do
	break;
	}
    if(guider_ui.ui_S11_Music == lv_disp_get_scr_act(NULL)){
    	lv_refr_now(NULL);
    }
}
/**
 * Called when a change in the ARC_Volume is required.
 * @param uint8_t u8Volume 0 to 100
 */
void ui_Change_Volume(uint8_t u8Volume){
    lv_arc_set_value(guider_ui.ui_Arc_Volume1, u8Volume);
    if(guider_ui.ui_S11_Music == lv_disp_get_scr_act(NULL)){
    	lv_refr_now(NULL);
    }
}

