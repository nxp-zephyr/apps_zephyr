# Copyright 2023-2024 NXP
# SPDX-License-Identifier: Apache-2.0


if(CONFIG_VGLITE)

set(VGLITE_BASE ${ZEPHYR_HAL_NXP_MODULE_DIR}/mcux/middleware/vglite)

# VGLite middleware files
target_sources(app PRIVATE
	${VGLITE_BASE}/VGLite/vg_lite.c
    	${VGLITE_BASE}/VGLite/vg_lite_image.c
    	${VGLITE_BASE}/VGLite/vg_lite_matrix.c
    	${VGLITE_BASE}/VGLite/vg_lite_path.c
    	${VGLITE_BASE}/VGLite/vg_lite_flat.c
    	${VGLITE_BASE}/font/buf_reader.c
    	${VGLITE_BASE}/font/rle_font_read.c
    	${VGLITE_BASE}/font/vft_debug.c
    	${VGLITE_BASE}/font/vft_draw.c
    	${VGLITE_BASE}/font/vg_lite_text.c
    	${VGLITE_BASE}/font/mcufont/decoder/mf_bwfont.c
    	${VGLITE_BASE}/font/mcufont/decoder/mf_encoding.c
    	${VGLITE_BASE}/font/mcufont/decoder/mf_font.c
    	${VGLITE_BASE}/font/mcufont/decoder/mf_justify.c
    	${VGLITE_BASE}/font/mcufont/decoder/mf_kerning.c
    	${VGLITE_BASE}/font/mcufont/decoder/mf_rlefont.c
    	${VGLITE_BASE}/font/mcufont/decoder/mf_scaledfont.c
    	${VGLITE_BASE}/font/mcufont/decoder/mf_wordwrap.c
    	${VGLITE_BASE}/VGLiteKernel/vg_lite_kernel.c
)

# VGLite port files
target_sources(app PRIVATE
	VGLite/rtos/vg_lite_os.c
	VGLiteKernel/rtos/vg_lite_hal.c
)

target_include_directories(app PRIVATE
	VGLite/rtos
	VGLiteKernel/rtos
)

target_include_directories(app PRIVATE
	${VGLITE_BASE}/inc
	${VGLITE_BASE}/font
	${VGLITE_BASE}/font/mcufont/decoder
	${VGLITE_BASE}/VGLite/rtos
	${VGLITE_BASE}/VGLiteKernel
	${VGLITE_BASE}/VGLiteKernel/rtos
)

# Only the "inc" directory has public headers
zephyr_include_directories(${VGLITE_BASE}/inc)

endif() # CONFIG_VGLITE
