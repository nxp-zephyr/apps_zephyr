# Copyright 2024, NXP
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

# Add shields for displays and cameras
if("${BOARD}" MATCHES "mimxrt1060_evk")
	set(SHIELD dvp_fpc24_mt9m114;rk043fn66hs_ctg)
elseif("${BOARD}" MATCHES "frdm_mcxn947")
	set(SHIELD lcd_par_s035_8080)
endif()

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(facialdetect)

list(APPEND app_sources src/main.c)

list(APPEND app_sources src/face_det.cpp)
FILE(GLOB model_sources src/model/*.cpp)
list(APPEND app_sources ${model_sources})
list(APPEND app_sources img/image_draw.c)
list(APPEND app_sources img/image_conv.c)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/model)
set(TFLITE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../modules/lib/tflite-micro")
zephyr_include_directories(${TFLITE_DIR})
zephyr_include_directories(${TFLITE_DIR}/third_party/flatbuffers/include)
zephyr_include_directories(${TFLITE_DIR}/third_party/gemmlowp)
zephyr_include_directories(${TFLITE_DIR}/third_party/ruy)

add_library(libtflm STATIC IMPORTED GLOBAL)
if (DEFINED CONFIG_CPU_CORTEX_M7)
	set_target_properties(libtflm PROPERTIES IMPORTED_LOCATION ${TFLITE_DIR}/lib/cm7/armgcc/libtflm.a)
elseif (DEFINED CONFIG_CPU_CORTEX_M33)
	set_target_properties(libtflm PROPERTIES IMPORTED_LOCATION ${TFLITE_DIR}/lib/cm33/armgcc/libtflm.a)
else()
	message(FATAL_ERROR "libtflm.a for this core not supported")
endif()

if (DEFINED CONFIG_MCUX_HAS_NPU)
	zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/model/model_npu)
	zephyr_include_directories(${TFLITE_DIR}/tensorflow/lite/micro/kernels/neutron)
	zephyr_include_directories(${TFLITE_DIR}/third_party/neutron/common/include)
	zephyr_include_directories(${TFLITE_DIR}/third_party/neutron/driver/include)

	FILE(GLOB modelnpu_sources src/model/model_npu/*.cpp)
	list(APPEND app_sources ${modelnpu_sources})
	list(APPEND app_sources src/model/model_npu/model_data.s)
	list(APPEND app_sources ${TFLITE_DIR}/tensorflow/lite/micro/kernels/neutron/neutron.cpp)

	add_library(libNeutronDriver STATIC IMPORTED GLOBAL)
	set_target_properties(libNeutronDriver PROPERTIES IMPORTED_LOCATION ${TFLITE_DIR}/third_party/neutron/mcxn/libNeutronDriver.a)
	add_library(libNeutronFirmware STATIC IMPORTED GLOBAL)
	set_target_properties(libNeutronFirmware PROPERTIES IMPORTED_LOCATION ${TFLITE_DIR}/third_party/neutron/mcxn/libNeutronFirmware.a)
	target_link_libraries(app PUBLIC libNeutronDriver libNeutronFirmware)
else() # CONFIG_MCUX_HAS_NPU not defined
	zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/model/model_sw)

	FILE(GLOB modelsw_sources src/model/model_sw/*.cpp)
	list(APPEND app_sources ${modelsw_sources})
	list(APPEND app_sources img/image_resize_nearest.c)
endif() # CONFIG_MCUX_HAS_NPU
target_link_libraries(app PUBLIC libtflm)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/img)
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/font)
list(APPEND app_sources src/display.c)
list(APPEND app_sources src/convert.c)

target_compile_definitions(app PRIVATE TF_LITE_STATIC_MEMORY)
target_compile_options(app PRIVATE -Wno-psabi)
target_sources(app PRIVATE ${app_sources})
