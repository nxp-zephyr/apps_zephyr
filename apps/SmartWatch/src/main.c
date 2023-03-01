/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include "board.h"
#include "fsl_power.h"

#ifdef CONFIG_LOG
	#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
	#include <zephyr/logging/log.h>
	LOG_MODULE_REGISTER(app);
#else
	#undef  LOG_ERR
	#define LOG_ERR(...)
#endif

#ifdef CONFIG_PM
	#include <zephyr/pm/pm.h>
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* for threads */
#define THREAD_STACKSIZE	4096
#define THREAD_PRIORITY_PVT	1	/* PVT Sensor thread highest priority */
#define THREAD_PRIORITY_LVGL	2

/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#ifdef CONFIG_LVGL
	/* lvgl_thread */
	extern void lvgl_thread(void *dummy1, void *dummy2, void *dummy3);

	K_THREAD_STACK_DEFINE(lvgl_thread_stack_area, THREAD_STACKSIZE);
	static struct k_thread lvgl_thread_data;
#endif

#ifdef CONFIG_SMARTWATCH_PVT_SENSOR
	#include "PVT_Sensor.h"

	K_THREAD_STACK_DEFINE(pvt_thread_stack_area, THREAD_STACKSIZE);
	static struct k_thread pvt_thread_data;
#endif

#ifdef CONFIG_GPIO
	static struct gpio_dt_spec button_gpio = GPIO_DT_SPEC_GET_OR(
			DT_ALIAS(sw0), gpios, {0});
	static struct gpio_callback button_callback;

	static void button_isr_callback(const struct device *port,
					struct gpio_callback *cb,
					uint32_t pins)
	{
		ARG_UNUSED(port);
		ARG_UNUSED(cb);
		ARG_UNUSED(pins);
	}

	/* GPIO pins for debugging and profiling */
	#define DBG_P1 DT_NODELABEL(debug_pin1)
	const struct gpio_dt_spec dbg_p1 = GPIO_DT_SPEC_GET(DBG_P1, gpios);
#endif

#ifdef CONFIG_PM
	/* Callbacks for PM subsystem */
	static void notify_pm_state_entry(enum pm_state state)
	{
	#ifdef CONFIG_GPIO
		gpio_pin_set_dt(&dbg_p1, 0);
	#endif
	}

	static void notify_pm_state_exit(enum pm_state state)
	{
	#ifdef CONFIG_GPIO
		gpio_pin_set_dt(&dbg_p1, 1);
	#endif
	}

	static struct pm_notifier notifier = {
		.state_entry = notify_pm_state_entry,
		.state_exit = notify_pm_state_exit,
	};
#endif /* CONFIG_PM */

static void App_HW_Optimizations(void)
{
	POWER_EnablePD(kPDRUNCFG_PD_OTP);

	/* Disable unused SRAMs */
	/* DSP is not used, disable AHB access to all SRAMs */
	SYSCTL0->DSP_SRAM_ACCESS_DISABLE = 0xFFFFFFFFU;

#ifdef CONFIG_SMARTWATCH_REDUCE_RAM
	#if (DT_REG_ADDR(DT_NODELABEL(sram_unpowered)) == 0x30300000)
		/* 3MB of SRAM used, power down remaining 2MB and reserved SRAM_ROM */
		uint32_t sram_pd_mask = 0xFF000006U;
	#elif (DT_REG_ADDR(DT_NODELABEL(sram_unpowered)) == 0x30400000)
		/* 4MB of SRAM used, power down remaining 3MB and reserved SRAM_ROM */
		uint32_t sram_pd_mask = 0xF0000006U;
	#else
		#error Amount of SRAM to power off is not configured
	#endif

	SYSCTL0->PDRUNCFG2		 = sram_pd_mask;
	SYSCTL0->PDRUNCFG3		 = sram_pd_mask;
	PMC->CTRL |= PMC_CTRL_APPLYCFG_MASK;
	SYSCTL0->AHB_SRAM_ACCESS_DISABLE = sram_pd_mask;
	SYSCTL0->AXI_SRAM_ACCESS_DISABLE = sram_pd_mask;
#endif /* CONFIG_SMARTWATCH_REDUCE_RAM */
}

int main(void)
{
	int32_t ret;

	printk("SmartWatch Demo\r\n");

#ifdef CONFIG_PM
	pm_notifier_register(&notifier);
#endif
	ret = power_manager_set_profile(POWER_PROFILE_FRO192M_900MV);
	if (ret) {
		printk("ERROR: power_manager_set_profile() returned %d\r\n", ret);
		while(1);
	}

	App_HW_Optimizations();
	printk("Power Profile changed to POWER_PROFILE_FRO192M_900MV\r\n");

#ifdef CONFIG_GPIO
	int err;

	if (device_is_ready(button_gpio.port)) {
		err = gpio_pin_configure_dt(&button_gpio, GPIO_INPUT);
		if (err) {
			LOG_ERR("failed to configure button gpio: %d", err);
			return err;
		}

		gpio_init_callback(&button_callback, button_isr_callback,
					BIT(button_gpio.pin));

		err = gpio_add_callback(button_gpio.port, &button_callback);
		if (err) {
			LOG_ERR("failed to add button callback: %d", err);
			return err;
		}

		err = gpio_pin_interrupt_configure_dt(&button_gpio,
						      GPIO_INT_EDGE_TO_ACTIVE);
		if (err) {
			LOG_ERR("failed to enable button callback: %d", err);
			return err;
		}
	}

	if (device_is_ready(dbg_p1.port))
	{
		err = gpio_pin_configure_dt(&dbg_p1, GPIO_OUTPUT_ACTIVE);
		if (err) {
			LOG_ERR("failed to configure dbg_p1 gpio: %d", err);
			return err;
		}
	}
#endif

#ifdef CONFIG_SMARTWATCH_PVT_SENSOR
	set_PVT_max_voltage(VDDCORE_192MHZ_SAFE_VMIN);
	set_PVT_min_voltage(VDDCORE_MIPI_VMIN);

	/* Create pvt_thread */
	k_thread_create(&pvt_thread_data, pvt_thread_stack_area,
			K_THREAD_STACK_SIZEOF(pvt_thread_stack_area),
			pvt_thread, NULL, NULL, NULL,
			THREAD_PRIORITY_PVT, 0, K_FOREVER);
	k_thread_name_set(&pvt_thread_data, "pvt_thread");
	k_thread_start(&pvt_thread_data);
#endif

#ifdef CONFIG_LVGL
	/* Create lvgl_thread */
	k_thread_create(&lvgl_thread_data, lvgl_thread_stack_area,
			K_THREAD_STACK_SIZEOF(lvgl_thread_stack_area),
			lvgl_thread, NULL, NULL, NULL,
			THREAD_PRIORITY_LVGL, 0, K_FOREVER);
	k_thread_name_set(&lvgl_thread_data, "lvgl_thread");
	k_thread_start(&lvgl_thread_data);
#else /* CONFIG_LVGL not defined */
	while (1)
	{
		k_sleep(K_MSEC(1000));
	}
#endif /* CONFIG_LVGL */
}

void SystemInitHook(void)
{
	/* Initialize FlexSPI cache if not already */
	if (CACHE64_POLSEL0->POLSEL == 0U) /* set CAHCHE64 if not configured */
	{
		/* set command to invalidate all ways and write GO bit to initiate command */
		CACHE64_CTRL0->CCR = CACHE64_CTRL_CCR_INVW1_MASK | CACHE64_CTRL_CCR_INVW0_MASK;
		CACHE64_CTRL0->CCR |= CACHE64_CTRL_CCR_GO_MASK;
		/* Wait until the command completes */
		while ((CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0U)
		{
		}
		/* Enable cache, enable write buffer */
		CACHE64_CTRL0->CCR = (CACHE64_CTRL_CCR_ENWRBUF_MASK | CACHE64_CTRL_CCR_ENCACHE_MASK);

		/* Set whole FlexSPI0 space to write through. */
		CACHE64_POLSEL0->REG0_TOP = 0x07FFFC00U;
		CACHE64_POLSEL0->REG1_TOP = 0x0U;
		CACHE64_POLSEL0->POLSEL   = 0x1U;

		__ISB();
		__DSB();
	}
}
