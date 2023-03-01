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

#include "vg_lite_os.h"
#include "vg_lite_hw.h"
#include "vg_lite_hal.h"

#include <zephyr/kernel.h>
#ifdef CONFIG_PM
#include <zephyr/pm/policy.h>
#endif

/* VG Lite command queue entry */
struct vg_lite_queue {
    uint32_t  cmd_physical;
    uint32_t  cmd_offset;
    uint32_t  cmd_size;
    vg_lite_os_async_event_t *event;
};

/* If bit31 is activated this indicates a bus error */
#define IS_AXI_BUS_ERR(x) ((x)&(1U << 31))


/* TODO: Values to move to KConfigs */
/* Alignment of VGLite allocations */
#define Z_VGLITE_ALIGNMENT 64

/* Memory heap for VGLite */
K_HEAP_DEFINE(vglite_heap, CONFIG_VGLITE_HEAP_SIZE);

/* Variable tracking VGLite context */
static uint32_t curContext;
/* Thread local storage variable */
static __thread void *thread_tls;
/* lock semaphore */
static struct k_sem vglite_lock;
/* Interrupt semaphore */
static struct k_sem int_sem;
/* Current interrupt flags */
volatile uint32_t int_flags;
/* Command thread */
K_THREAD_STACK_DEFINE(command_thread_stack,
            CONFIG_VGLITE_COMMAND_THREAD_STACK_SIZE);
static struct k_thread command_thread;
/* Message queue */
K_MSGQ_DEFINE(command_queue, sizeof(struct vg_lite_queue),
            CONFIG_VGLITE_COMMAND_QUEUE_LEN, 4);
/* Message queue event semaphores */
static struct k_sem command_sems[TASK_LENGTH];


#if !defined(VG_DRIVER_SINGLE_THREAD)

void command_thread_entry(void *arg1, void *arg2, void* arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    uint32_t event_got;
    struct vg_lite_queue node;

    while (1) {
        /* Get a queue entry */
        k_msgq_get(&command_queue, &node, K_FOREVER);
        vg_lite_hal_poke(VG_LITE_HW_CMDBUF_ADDRESS, node.cmd_physical + node.cmd_offset);
        vg_lite_hal_poke(VG_LITE_HW_CMDBUF_SIZE, (node.cmd_size + 7)/8);

        /* Wait for interrupt. Long delay of 0x1FFFF ms */
        if (vg_lite_hal_wait_interrupt(0x1FFFF, (uint32_t)~0, &event_got)) {
            node.event->signal =VG_LITE_HW_FINISHED;
        } else {
            node.event->signal = VG_LITE_IDLE;
        }

        k_sem_give(&command_sems[node.event->semaphore_id]);
    }

}

/* Sets task local storage pointer */
int32_t vg_lite_os_set_tls(void* tls)
{
	if (tls == NULL) {
		return VG_LITE_INVALID_ARGUMENT;
	}
	thread_tls = tls;
    return VG_LITE_SUCCESS;
}

/* Gets task local storage pointer */
void *vg_lite_os_get_tls()
{
	return thread_tls;
}

#endif /* !DEFINED(VG_DRIVER_SINGLE_THREAD)*/

/* OS allocate */
void *vg_lite_os_malloc(uint32_t size)
{
	return k_heap_alloc(&vglite_heap, size, K_NO_WAIT);
}

/* OS free */
void vg_lite_os_free(void *memory)
{
	k_heap_free(&vglite_heap, memory);
}

/* Allocate a contiguous memory block for VGLite */
int32_t vg_lite_os_allocate_contiguous(unsigned long size,
                                                void ** logical,
                                                uint32_t * physical,
                                                void ** node)
{
    void *ptr;

    ptr = k_heap_aligned_alloc(&vglite_heap, CONFIG_VGLITE_ALLOC_ALIGNMENT,
                                size, K_NO_WAIT);
    if (ptr == NULL) {
        return VG_LITE_OUT_OF_MEMORY;
    }

    *logical = ptr;
    /* Physical address will always be same as logical, MMU not supported. */
    *physical = (uint32_t)(*logical);
    return VG_LITE_SUCCESS;
}

/* Free a contiguous memory block */
void vg_lite_os_free_contiguous(void *memory_handle)
{
    k_heap_free(&vglite_heap, memory_handle);
}

int32_t vg_lite_os_query_free_mem(void)
{
    struct sys_memory_stats stats;
    if (sys_heap_runtime_stats_get(&vglite_heap.heap, &stats) < 0) {
        return VG_LITE_NO_CONTEXT;
    }
    return stats.free_bytes;
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
/* Reset TLS */
void vg_lite_os_reset_tls(void)
{
	thread_tls = NULL;
}
#endif /* !DEFINED(VG_DRIVER_SINGLE_THREAD)*/

/* OS delay primitive */
void vg_lite_os_sleep(uint32_t msec)
{
	k_msleep(msec);
}

/* Initialize OSA layer */
int32_t vg_lite_os_initialize(void)
{
#if !defined(VG_DRIVER_SINGLE_THREAD)
    static bool init_done = false;

    if (k_sem_init(&vglite_lock, 1, 1) < 0) {
        return VG_LITE_MULTI_THREAD_FAIL;
    }
    if (init_done == false) {
        if (k_sem_take(&vglite_lock, K_MSEC(100)) == 0) {
            k_thread_create(&command_thread, command_thread_stack,
                        K_THREAD_STACK_SIZEOF(command_thread_stack),
                        command_thread_entry, NULL, NULL, NULL,
                        0, 0, K_NO_WAIT);
            init_done = true;
            k_sem_give(&vglite_lock);
        }
    }

#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */
    int_flags = 0;
    k_sem_init(&int_sem, 0, 1);

    return VG_LITE_SUCCESS;
}


#if !defined(VG_DRIVER_SINGLE_THREAD)
/* lock OSA mutex */
int32_t vg_lite_os_lock()
{
    if (k_sem_take(&vglite_lock, K_MSEC(100)) < 0) {
        return VG_LITE_MULTI_THREAD_FAIL;
    }
    return VG_LITE_SUCCESS;
}

/* Release OSA mutex */
int32_t vg_lite_os_unlock()
{
    k_sem_give(&vglite_lock);
    return VG_LITE_SUCCESS;
}


/* Submit command to VGLite command queue thread */
int32_t vg_lite_os_submit(uint32_t context,
                    uint32_t physical,
                    uint32_t offset,
                    uint32_t size,
                    vg_lite_os_async_event_t *event)
{
    struct vg_lite_queue node;
    int ret;

    node.cmd_physical = physical;
    node.cmd_offset = offset;
    node.cmd_size = size;
    node.event = event;
    curContext = context;

    /* Send event to queue */
    ret = k_msgq_put(&command_queue, &node, K_FOREVER);
    if (ret != 0) {
        return VG_LITE_MULTI_THREAD_FAIL;
    }
    event->signal = VG_LITE_IN_QUEUE;

    return VG_LITE_SUCCESS;
}


/* Wait for event completion */
int32_t vg_lite_os_wait(uint32_t timeout, vg_lite_os_async_event_t *event)
{
    k_sem_take(&command_sems[event->semaphore_id], K_FOREVER);
    return VG_LITE_SUCCESS;
}

#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

/* OSA GPU IRQ handler */
void vg_lite_os_IRQHandler(void)
{
    uint32_t flags = vg_lite_hal_peek(VG_LITE_INTR_STATUS);
    if (flags) {
        /* Combine with current interrupt flags. */
        int_flags |= flags;

        /* Wake up any waiting users */
        k_sem_give(&int_sem);
    }
}

/* Wait for interrupt to occur, and report all interrupts since last call
 * of this function
 */
int32_t vg_lite_os_wait_interrupt(uint32_t timeout, uint32_t mask, uint32_t * value)
{
    int ret;
#ifdef CONFIG_PM
    pm_policy_state_lock_get(PM_STATE_SUSPEND_TO_IDLE, PM_ALL_SUBSTATES);
#endif
    ret = k_sem_take(&int_sem, K_MSEC(timeout));
#ifdef CONFIG_PM
    pm_policy_state_lock_put(PM_STATE_SUSPEND_TO_IDLE, PM_ALL_SUBSTATES);
#endif
    if (ret < 0) {
        return 0;
    }
    if (value != NULL) {
        *value = int_flags & mask;
        if (IS_AXI_BUS_ERR(*value)) {
            /* TODO- create a more permanent way to handle this */
            printk("AXI BUS ERROR!\n");
        }
        /* Clear int flags */
        int_flags = 0;
        return 1;
    }
    return 0;
}


#if !defined(VG_DRIVER_SINGLE_THREAD)

/* Initialize a VGLite event for submission to queue */
int32_t vg_lite_os_init_event(vg_lite_os_async_event_t *event,
                                      uint32_t semaphore_id,
                                      int32_t state)
{
    if (event->semaphore_id >= TASK_LENGTH) {
        return VG_LITE_INVALID_ARGUMENT;
    }

    event->semaphore_id = semaphore_id;
    event->signal = state;

    k_sem_init(&command_sems[event->semaphore_id], 0, 1);
    return VG_LITE_SUCCESS;
}

/* Cleanup a VGLite event */
int32_t vg_lite_os_delete_event(vg_lite_os_async_event_t *event)
{
    if (event->semaphore_id >= TASK_LENGTH) {
        return VG_LITE_INVALID_ARGUMENT;
    }

    k_sem_reset(&command_sems[event->semaphore_id]);

    return VG_LITE_SUCCESS;
}

/* Check if a context switch has occurred */
int8_t vg_lite_os_query_context_switch(uint32_t context)
{
   if(!curContext || curContext == context)
        return 0;
    return 1;
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */
