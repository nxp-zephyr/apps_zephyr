/*
 *    Copyright (c) 2014 - 2020 Vivante Corporation
 *    Copyright 2023 NXP
 *
 *    Permission is hereby granted, free of charge, to any person obtaining
 *    a copy of this software and associated documentation files (the
 *    'Software'), to deal in the Software without restriction, including
 *    without limitation the rights to use, copy, modify, merge, publish,
 *    distribute, sub license, and/or sell copies of the Software, and to
 *    permit persons to whom the Software is furnished to do so, subject
 *    to the following conditions:
 *
 *    The above copyright notice and this permission notice (including the
 *    next paragraph) shall be included in all copies or substantial
 *    portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 *    IN NO EVENT SHALL VIVANTE AND/OR ITS SUPPLIERS BE LIABLE FOR ANY
 *    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. *
 */

/* VGLite specific includes */
#include "vg_lite_platform.h"
#include "vg_lite_kernel.h"
#include "vg_lite_hal.h"
#include "vg_lite_hw.h"
#include "vg_lite_os.h"
#include "vg_lite.h"

/* NXP hardware includes */
#include "fsl_clock.h"
#include "fsl_power.h"

/* Zephyr specific includes */
#include <zephyr/kernel.h>
#include <zephyr/device.h>

#define DT_DRV_COMPAT nxp_vglite

BUILD_ASSERT(DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 1,
            "VGLite driver currently only supports a single instance");

/* Use the first device defined with GPT HW timer compatible string */
#define VGLITE_DEV DT_INST(0, DT_DRV_COMPAT)

/* Single instance driver- use register address from first compatible */
static const uint32_t gpu_base = DT_REG_ADDR(VGLITE_DEV);

/* HAL support for delay */
void vg_lite_hal_delay(uint32_t ms)
{
    vg_lite_os_sleep(ms);
}

/* HAL memory barrier */
void vg_lite_hal_barrier(void)
{
    /* TODO- does this function need to flush cache?
     * freeRTOS implementation for RT595 doesn't
     */
    __asm__ volatile("DSB");
}

/* Initializes GPU and GPU clocks */
vg_lite_error_t vg_lite_hal_initialize(void)
{
    return (vg_lite_error_t)vg_lite_os_initialize();
}

void vg_lite_hal_deinitialize(void)
{
    /* Todo: turn off GPU power and clocks here */
    /* OS support is statically initialized */
}

/* Allocate a contiguous memory block for VGLite */
vg_lite_error_t vg_lite_hal_allocate_contiguous(unsigned long size,
                                                void ** logical,
                                                uint32_t * physical,
                                                void ** node)
{
    return (vg_lite_error_t)vg_lite_os_allocate_contiguous(size, logical, physical, node);
}

/* Free a contiguous memory block */
void vg_lite_hal_free_contiguous(void *memory_handle)
{
    vg_lite_os_free_contiguous(memory_handle);
}

/* Free OS heap, called during VGLite deinit */
void vg_lite_hal_free_os_heap(void)
{
    /* Cannot free kernel heap, as it was statically allocated. This
     * is currently a no-op
     */
}

/* Read register value from device */
uint32_t vg_lite_hal_peek(uint32_t address)
{
    return (uint32_t) (*(volatile uint32_t *)(gpu_base + address));
}

/* Write register in device */
void vg_lite_hal_poke(uint32_t address, uint32_t data)
{
    uint32_t *gpu_addr = (uint32_t *)(gpu_base + address);
    *gpu_addr = data;
}

/* Get free bytes on VGLite heap */
vg_lite_error_t vg_lite_hal_query_mem(vg_lite_kernel_mem_t *mem)
{
    int32_t ret;
    ret = vg_lite_os_query_free_mem();
    if (((vg_lite_error_t)ret) == VG_LITE_NO_CONTEXT) {
        return (vg_lite_error_t)ret;
    }
    mem->bytes = ret;
    return VG_LITE_SUCCESS;
}

/* GPU IRQ handler */
void vg_lite_IRQHandler(const struct device *dev)
{
    vg_lite_os_IRQHandler();
}


int32_t vg_lite_hal_wait_interrupt(uint32_t timeout, uint32_t mask, uint32_t * value)
{
    return vg_lite_os_wait_interrupt(timeout,mask,value);
}

void * vg_lite_hal_map(unsigned long bytes, void * logical, uint32_t physical, uint32_t * gpu)
{

    (void) bytes;
    (void) logical;
    (void) physical;
    (void) gpu;
    return (void *)0;
}

void vg_lite_hal_unmap(void * handle)
{

    (void) handle;
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
vg_lite_error_t vg_lite_hal_submit(uint32_t context,uint32_t physical, uint32_t offset, uint32_t size, vg_lite_os_async_event_t *event)
{
    return (vg_lite_error_t)vg_lite_os_submit(context,physical,offset,size,event);
}

vg_lite_error_t vg_lite_hal_wait(uint32_t timeout, vg_lite_os_async_event_t *event)
{
    return  (vg_lite_error_t)vg_lite_os_wait(timeout,event);
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */


#define VG_LITE_COMMAND_BUFFER_SIZE                     (128 << 10) /* 128 KB */

/* Default tessellation window width and height, in pixels */
#define DEFAULT_VG_LITE_TW_WIDTH                        128 /* pixels */
#define DEFAULT_VG_LITE_TW_HEIGHT                       128 /* pixels */

static int vglite_device_init(const struct device *unused)
{
    /* Install IRQ */
    IRQ_CONNECT(DT_IRQN(VGLITE_DEV), DT_IRQ(VGLITE_DEV, priority),
            vg_lite_IRQHandler, NULL, 0);
    irq_enable(DT_IRQN(VGLITE_DEV));

    /* Enable VGLite */
    if (vg_lite_init(DEFAULT_VG_LITE_TW_WIDTH, DEFAULT_VG_LITE_TW_HEIGHT) != VG_LITE_SUCCESS) {
        printk("VGLite init error\n");
        return -ENODEV;
    }

    if (vg_lite_set_command_buffer_size(VG_LITE_COMMAND_BUFFER_SIZE) != VG_LITE_SUCCESS) {
        printk("VGLite set command buffer fail\n");
        return -ENOTSUP;
    }
    return 0;
}

#define VGLITE_INIT(n)                                                          \
    DEVICE_DT_INST_DEFINE(n,                                                    \
                        vglite_device_init,                                     \
                        NULL,                                                   \
                        NULL,                                                   \
                        NULL,                                                   \
                        POST_KERNEL,                                            \
                        CONFIG_KERNEL_INIT_PRIORITY_DEVICE,                     \
                        NULL);

DT_INST_FOREACH_STATUS_OKAY(VGLITE_INIT)
