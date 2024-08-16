/*
 * Copyright 2023 NXP
 *
 * SPDX-LICENSE-IDENTIFIER: BSD-3-Clause
 *
 */

/**
 * @file ui_Music.h
 *
 */
#ifndef _UI_MUSIC_H_
#define _UI_MUSIC_H_
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

/**********************
 *      TYPEDEFS
 **********************/
  typedef enum {
	kDance_onTheMoon,
	kSong_2,
    kLast_Song,
}ui_names_songs;




/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/


void ui_Change_Song(ui_names_songs SongName);
void ui_Change_Volume(uint8_t u8Volume);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_UI_MUSIC_H_*/
