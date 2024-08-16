# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

# If SMARTWATCH_IN_RAM_APP is defined, pull in dts and kconfig overlays for
# this feature
if (DEFINED SMARTWATCH_IN_RAM_APP)
	list(APPEND EXTRA_DTC_OVERLAY_FILE smartwatch_ram.overlay)
	list(APPEND EXTRA_CONF_FILE smartwatch_ram.conf)
	# Manually cache variable, so CMake does not warn it it unused
	set(SMARTWATCH_IN_RAM_APP CACHE BOOL "Smartwatch app in RAM")
endif()

# If SMARTWATCH_REDUCE_RAM is defined, pull in dts and kconfig overlays for
# this feature
if (DEFINED SMARTWATCH_REDUCE_RAM)
	list(APPEND EXTRA_DTC_OVERLAY_FILE reduce_ram.overlay)
	list(APPEND EXTRA_CONF_FILE reduce_ram.conf)
	# Manually cache variable, so CMake does not warn it it unused
	set(SMARTWATCH_REDUCE_RAM CACHE BOOL "Reduce SRAM utilization")
endif()

set(SHIELD g1120b0mipi)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Include VGLite port
add_subdirectory(vglite-port)

FILE(GLOB app_sources src/*.c)

if (DEFINED CONFIG_SMARTWATCH_PVT_SENSOR)
        set(LIB_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/../../../modules/hal/appswpacks-dvs-pvt-sensor/dvs_pvt_sensor/app)
        add_library(libpvt STATIC IMPORTED GLOBAL)
        set_target_properties(libpvt PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/evkmimxrt595/pvt_lib/libpvt.a)
        target_link_libraries(app PUBLIC libpvt)
        include_directories(app ${LIB_DIR}/common/pvt_lib)
        include_directories(app ${LIB_DIR}/evkmimxrt595/pvt_lib)
        include_directories(app src/PVT)
        FILE(GLOB pvt_sources src/PVT/*.c)
        list(APPEND app_sources ${pvt_sources})
      endif()

if (DEFINED CONFIG_LVGL)
        project(lvgl)

 	set(UI_PATH UI_SW)

        include_directories(app src/${UI_PATH})
        include_directories(app src/${UI_PATH}/custom)
        include_directories(app src/${UI_PATH}/generated)
        include_directories(app src/${UI_PATH}/generated/guider_customer_fonts)
        include_directories(app src/${UI_PATH}/generated/guider_fonts)
        include_directories(app src/${UI_PATH}/generated/images)

	FILE(GLOB gfx_sources src/${UI_PATH}/*.c src/${UI_PATH}/generated/*.c src/${UI_PATH}/generated/guider_fonts/*.c src/${UI_PATH}/generated/guider_customer_fonts/*.c src/${UI_PATH}/generated/images/*.c src/${UI_PATH}/custom/*.c)
	list(APPEND app_sources ${gfx_sources})

  add_library(libLogos STATIC IMPORTED GLOBAL)
  set_target_properties(libLogos PROPERTIES IMPORTED_LOCATION
      ${CMAKE_CURRENT_SOURCE_DIR}/src/${UI_PATH}/generated/images/logos_lib/libLogos.a)
  target_link_libraries(app PUBLIC libLogos)
endif()

# Relocate GFX data into a FlexSPI region. This is required because not
# all assets for the demo can fit in SRAM.
set(gfx_path src/${UI_PATH})
if(NOT CONFIG_SMARTWATCH_IN_RAM_DIGITAL_SCREEN)
  zephyr_code_relocate(FILES
    ${gfx_path}/generated/images/lv_font_Montserrat_Light_40.c
    ${gfx_path}/generated/images/ui_font_medium_font.c
    ${gfx_path}/generated/images/ui_font_number_bold.c
    ${gfx_path}/generated/images/ui_font_number_light.c
    ${gfx_path}/generated/images/ui_img_icn_flash_png.c
    ${gfx_path}/generated/images/ui_img_icn_message_png.c
    ${gfx_path}/generated/images/ui_img_icn_sport_png.c
    ${gfx_path}/generated/images/ui_img_icn_weather_1_png.c
    ${gfx_path}/generated/images/ui_img_img_bg_digital_png.c
    ${gfx_path}/generated/images/ui_img_img_clock_shadow_png.c
    ${gfx_path}/generated/images/ui_img_img_menu_png.c
    ${gfx_path}/generated/images/ui_img_img_nxp_png.c
    ${gfx_path}/generated/images/ui_img_text_message_png.c
    ${gfx_path}/generated/images/ui_img_text_sport_png.c
    LOCATION GFX_RODATA NOCOPY)
endif()

zephyr_code_relocate(FILES
  ${gfx_path}/generated/images/ui_font_big_font.c
  ${gfx_path}/generated/images/ui_font_small_font.c
  ${gfx_path}/generated/images/ui_img_icn_home_png.c
  ${gfx_path}/generated/images/ui_img_icn_small_burn_png.c
  ${gfx_path}/generated/images/ui_img_icn_small_pos_png.c
  ${gfx_path}/generated/images/ui_img_icn_small_pulse_png.c
  ${gfx_path}/generated/images/ui_img_icn_small_time_png.c
  ${gfx_path}/generated/images/ui_img_icn_small_weather_1_png.c
  ${gfx_path}/generated/images/ui_img_icn_small_weather_2_png.c
  ${gfx_path}/generated/images/ui_img_icn_small_weather_3_png.c
  ${gfx_path}/generated/images/ui_img_img_arrow_left_png.c
  ${gfx_path}/generated/images/ui_img_img_arrow_right_png.c
  ${gfx_path}/generated/images/ui_img_icn_audio_back_png.c
  ${gfx_path}/generated/images/ui_img_icn_audio_next_png.c
  ${gfx_path}/generated/images/ui_img_icn_audio_play_png.c
  ${gfx_path}/generated/images/ui_img_icn_audio_rnd_png.c
  ${gfx_path}/generated/images/ui_img_img_audio_album_png.c
  ${gfx_path}/generated/images/ui_img_img_bg_2_png.c
  ${gfx_path}/generated/images/ui_img_img_bg_analog_png.c
  ${gfx_path}/generated/images/ui_img_img_bg_health_png.c
  ${gfx_path}/generated/images/ui_img_img_clockwise_hour_png.c
  ${gfx_path}/generated/images/ui_img_img_clockwise_min_png.c
  ${gfx_path}/generated/images/ui_img_img_clockwise_sec_png.c
  ${gfx_path}/generated/images/ui_img_img_cloud_png.c
  ${gfx_path}/generated/images/ui_img_img_ekg_png.c
  ${gfx_path}/generated/images/ui_img_img_header_bg_png.c
  ${gfx_path}/generated/images/ui_img_img_header_bg_shadow_png.c
  ${gfx_path}/generated/images/ui_img_img_heart_png.c
  ${gfx_path}/generated/images/ui_img_img_nxp_logo_big_png.c
  ${gfx_path}/generated/images/ui_img_img_pause_png.c
  ${gfx_path}/generated/images/ui_img_img_squareline_png.c
  ${gfx_path}/generated/images/ui_img_img_sun_png.c
  ${gfx_path}/generated/images/ui_img_text_audio_volume_png.c
  ${gfx_path}/generated/images/ui_img_text_home_png.c
  ${gfx_path}/generated/images/ui_img_text_select_png.c
  ${gfx_path}/generated/images/ui_img_text_start_stop_png.c
  ${gfx_path}/generated/images/_coursewrkwavesfeb_dribbble_392x392.c
  ${gfx_path}/generated/images/_icn_weather_2_41x38.c
  ${gfx_path}/generated/images/_icn_weather_3_41x38.c
  ${gfx_path}/generated/images/_img_clockwise_hourLP_18x98.c
  ${gfx_path}/generated/images/_img_clockwise_minLP_18x157.c
  ${gfx_path}/generated/images/_img_clockwise_secLP_31x180.c
  ${gfx_path}/generated/images/_img_cloud_2_586x147.c
  ${gfx_path}/generated/images/_img_nxpLP_65x23.c
  ${gfx_path}/generated/images/_Zephyr_RTOS_logo_118x57.c
  LOCATION GFX_RODATA NOCOPY)

# Relocate SDMA firmware back to flash, as the driver copies it to RAM
zephyr_code_relocate(FILES
  ${ZEPHYR_BASE}/../modules/hal/nxp/mcux/mcux-sdk/drivers/smartdma/fsl_smartdma.c
  LOCATION GFX_RODATA NOCOPY)

# The following snippet modifies the objcopy relocate command the build system
# will run to relocate the built ELF file, so that the GFX section will not
# be relocated. When combined with the zephyr_code_relocate macro, this will
# result in the GFX RODATA section being relocated to flash, and not
# affecting the total image size. This means that the ROM will not attempt
# to copy the GFX data to SRAM, and it can be read directly from FlexSPI.
if(CONFIG_BUILD_OUTPUT_ADJUST_LMA)
  math(EXPR adjustment "${CONFIG_BUILD_OUTPUT_ADJUST_LMA}" OUTPUT_FORMAT DECIMAL)
  set(excluded_sections
	  ".gfx_rodata_reloc")
  set(lma_adjust --change-section-lma *+${adjustment})
  foreach(section ${excluded_sections})
    list(APPEND lma_adjust --change-section-lma !${section}+1)
  endforeach()
  set_property(TARGET bintools PROPERTY elfconvert_flag_lma_adjust ${lma_adjust})
endif()

target_sources(app PRIVATE ${app_sources})
