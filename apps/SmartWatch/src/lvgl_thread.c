/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 * Copyright 2023 NXP
 *
 * Originated from:
 * https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/subsys/display/lvgl/src/main.c
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef CONFIG_LVGL

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>

#ifdef CONFIG_SHELL
	#include <zephyr/shell/shell.h>

	static int time_change(const struct shell *shell, int32_t argc, char **argv);
#endif

#include <lvgl.h>
#include <zephyr/drivers/display.h>
#include "../../../../../modules/lib/gui/lvgl/src/core/lv_disp.h"

#include <screen_setup.h>
#include <gui_guider.h>
#include <events_init.h>

#include <animation.h>
#include <ui_helpers.h>

#include <ui_Weather.h>
#include <ui_SportAPI.h>
#include <ui_Watch_Face.h>
#include <ui_Music.h>
#include <ui_EKG.h>

#define MAIN_SCREENS 5
#define SUB_SCREENS 3

/**********************************************************************
 * Global Variables
 **********************************************************************/
lv_ui guider_ui;
int16_t MainScreenCnt = 0;
int16_t SubScreenCnt = 0;
lv_obj_t *ptrScreen[MAIN_SCREENS][SUB_SCREENS];
int16_t task_delay = 1;

/**********************************************************************
 * Prototypes
 **********************************************************************/
void ChangeScreen(lv_dir_t Dir);
static void IdentifyScreens (void);
void changedirectory(void);
void update_lvtask_delay(void);
void update_lvtask_delay_fast(void);

/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

K_SEM_DEFINE(touch_sem, 0, 1);

#ifdef CONFIG_GPIO
	#include <zephyr/drivers/gpio.h>

	static void touch_timer_expired(struct k_timer *timer);
	K_TIMER_DEFINE(touch_isr_enable, touch_timer_expired, NULL);

	/* Display touch INT pin */
	#define TOUCH_NODE DT_NODELABEL(ft3267_g1120b0mipi)
	const struct gpio_dt_spec touch_pin = GPIO_DT_SPEC_GET(TOUCH_NODE, int_gpios);
	struct gpio_callback touch_pin_cb;
	static void touch_pin_handler(const struct device *dev,
					struct gpio_callback *cb, uint32_t pins)
	{
		/*
		 * ------------------- WORKAROUND ---------------------------
		 * The FT3267 touch IC pulls the INT pin low continuously for
		 * ~5 ms after a touch input. The RT500 GPIO interrupt has
		 * a limitation where the GPIO interrupt only works in
		 * LEVEL mode when entering deep sleep. Since the GPIO
		 * driver reconfigures GPIO pins with edge mode to use
		 * level interrupts when entering sleep, the part will be
		 * awoken continuously during these 5 ms.

		 * To fix this, we disable the touch interrupt and set a 6ms
		 * kernel timer. When the timer expires, we will enable the
		 * touch interrupt again.
		 */
		gpio_pin_interrupt_configure_dt(&touch_pin, GPIO_INT_DISABLE);
		k_timer_start(&touch_isr_enable, K_MSEC(6), K_NO_WAIT);
		/* Signal to the application that touch data was sent */
		k_sem_give(&touch_sem);
	}


	static void touch_timer_expired(struct k_timer *timer) {
		gpio_pin_interrupt_configure_dt(&touch_pin,
			GPIO_INT_EDGE_TO_ACTIVE |
			GPIO_INT_WAKEUP);
	}
#endif

void changedirectory(void)
{
	 MainScreenCnt = 0;
	 SubScreenCnt = 0;
}

void changedirectoryMusic(void)
{
	lv_scr_load(guider_ui.ui_S11_Music);
	MainScreenCnt = 3;
	SubScreenCnt = 0;
}

void update_lvtask_delay(void)
{
	task_delay = 1000;
}

void update_lvtask_delay_fast(void)
{
	task_delay = 5;
}


void changedirectoryTime(void)
{
	lv_scr_load(guider_ui.ui_S1_Watch_Digital);
	MainScreenCnt = 0;
	SubScreenCnt = 0;
}

void changedirectoryWeather(void)
{
	lv_scr_load(guider_ui.ui_S5_Weather);
	MainScreenCnt = 1;
	SubScreenCnt = 0;
}

void changedirectoryFit(void)
{
	lv_scr_load(guider_ui.ui_S9_Sport);
	MainScreenCnt = 2;
	SubScreenCnt = 0;
}

void changedirectoryHeart(void)
{
	lv_scr_load(guider_ui.ui_S24_EKG);
	MainScreenCnt = 4;
	SubScreenCnt = 0;
}

void ChangeScreen(lv_dir_t Dir)
{
	uint8_t main_val=MainScreenCnt;
	uint8_t sub_val=SubScreenCnt;

	if(Dir == LV_DIR_TOP)
	{

		MainScreenCnt++;

		if((ptrScreen[MainScreenCnt][SubScreenCnt] == NULL) || (MainScreenCnt >= MAIN_SCREENS))
		{
			MainScreenCnt = 0;
			SubScreenCnt = 0;

		}
	}
	else if(Dir == LV_DIR_BOTTOM)
	{
		MainScreenCnt--;
		if((ptrScreen[MainScreenCnt][SubScreenCnt] == NULL) || (MainScreenCnt < 0))
		{
			MainScreenCnt = MAIN_SCREENS - 1;
			SubScreenCnt = 0;
		}
	}
	else if(Dir == LV_DIR_LEFT)
	{
		SubScreenCnt++;
		if((ptrScreen[MainScreenCnt][SubScreenCnt] == NULL) || (SubScreenCnt >= SUB_SCREENS))
		{
			SubScreenCnt = 0;
		}
	}
	else if(Dir == LV_DIR_RIGHT)
	{
		if((ptrScreen[MainScreenCnt][SubScreenCnt - 1] != NULL) && ((SubScreenCnt - 1) >= 0))
		{
			SubScreenCnt--;
		}
	}
	else
	{
		/* Do nothing, no valid direction */
	}

	if(main_val!=MainScreenCnt||sub_val!=SubScreenCnt)
	{
		lv_scr_load_anim(ptrScreen[MainScreenCnt][SubScreenCnt], LV_SCR_LOAD_ANIM_FADE_OUT, 10, 0, false);
	}
}

static void IdentifyScreens(void)
{
	ptrScreen[0][0] = guider_ui.ui_S1_Watch_Digital;
	ptrScreen[0][1] = guider_ui.ui_S2_Watch_Analog;
	ptrScreen[1][0] = guider_ui.ui_S5_Weather;
	ptrScreen[2][0] = guider_ui.ui_S9_Sport;
	ptrScreen[3][0] = guider_ui.ui_S24_EKG ;
	ptrScreen[4][0] = guider_ui.ui_S11_Music;
	ptrScreen[0][2] = guider_ui.ui_SLowPower;
}

#ifdef CONFIG_SHELL
static int time_change(const struct shell *shell, int32_t argc, char **argv){

	uint16_t u16Hours = ((int16_t)atoi(argv[1]));
	uint16_t u16Minutes = ((int8_t)atoi(argv[2]));

	updateTIMERS(u16Minutes, u16Hours);
	if(u16Hours > 23 || u16Minutes > 59)
	{
	} else
	{
		lv_label_set_text(guider_ui.ui_Label_Hour, argv[1]);
		lv_label_set_text(guider_ui.ui_Label_Minute, argv[2]);
	}

	return 0;
}

SHELL_CMD_REGISTER(time, NULL, "Toggle LED command", time_change);
#endif /* CONFIG_SHELL */

void lvgl_thread(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);

#ifdef CONFIG_GPIO
	if (device_is_ready(touch_pin.port)) {
		gpio_init_callback(&touch_pin_cb, touch_pin_handler,
				BIT(touch_pin.pin));
		gpio_add_callback(touch_pin.port, &touch_pin_cb);

	}
#endif

	const struct device *display_dev;
	int ret;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		printk("Device not ready, aborting test");
		return;
	}

	lv_task_handler();
	display_blanking_off(display_dev);

	complete_set();
	lv_scr_load(guider_ui.ui_S0_Splash);
	IdentifyScreens();

	while (1) 
	{
		/* Take from the touch interrupt semaphore.
			* We timeout after 1000ms, as we still want to
			* refresh the display at least this often.
			*/

		ret = k_sem_take(&touch_sem, K_MSEC(task_delay));
		if (ret == -EAGAIN) {
			/* Semaphore timed out. Without any new
				* touch data, we only need to refresh the
				* display once.
				*/

			if(ptrScreen[MainScreenCnt][SubScreenCnt] == guider_ui.ui_S2_Watch_Analog || ptrScreen[MainScreenCnt][SubScreenCnt] == guider_ui.ui_S1_Watch_Digital || ptrScreen[MainScreenCnt][SubScreenCnt] == guider_ui.ui_SLowPower){
				update_lvtask_delay();
			}
			
			lv_task_handler();
		} else
		{
			update_lvtask_delay_fast();
		}
	}
}

#endif /* CONFIG_LVGL*/
