/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * This feature leverages the PVT_Sensor hardware of the NXP i.MX RT500 MCU.
 * For details, see https://www.nxp.com/design/software/embedded-software/application-software-pack-dynamic-voltage-scaling-using-pvt-sensor:APP-SW-PACK-DVS-PVT-SENSOR]
 *
 * This usage of the PVT Sensor is for demo purposes only.  To use in a product,
 * refer to Appnote AN13695 at https://www.nxp.com/webapp/Download?colCode=AN13695.
 * The demo usage of the PVT Sensor is limited, including:
 *	- The demo assumes operation at room temperature; it does not monitor
 *	  the temp, and it has not been tested over the temp range.
 *	- The demo uses Deep Sleep mode with the PVT Sensor, and it assumes
 *	  no ambient conditions change while in Deep Sleep, so it can wake to 
 *	  the same VDDCORE voltage before Deep Sleep.
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/regulator.h>

#include "pvt.h"
#include "PVT_Sensor.h"

#ifdef CONFIG_PM
	#include <zephyr/pm/pm.h>
	#include <zephyr/pm/policy.h>
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * How often for PVT task to check if VDDCORE can go lower.
 */
#define PVT_TASK_WAIT_MS		10000U
/**
 * Amount of time it takes the PMIC SW1_OUT to stabilize after decreasing it 1 step.
 */
#define PMIC_SETTLING_TIME_MS		5U
/**
 * Time to wait between enabling the PVT ring oscillator and reading the delay.
 */
#define PVT_RING_OSC_WAIT_TIME_MS	500U
/**
 * VDDCORE voltage required to read ring oscillator 0.9V
 */
#define VDDCORE_RINGO_VOLTAGE		900000U
/**
 * pvt_event flags
 */
#define PVT_EVENT_SENSOR_IRQ		(1 << 0)
#define PVT_EVENT_TIMER			(1 << 1)
#define PVT_EVENT_NEW_MIN		(1 << 2)
#define PVT_EVENT_NEW_MAX		(1 << 3)
#define PVT_EVENT_MASK	(PVT_EVENT_SENSOR_IRQ	| PVT_EVENT_TIMER |		\
			 PVT_EVENT_NEW_MIN	| PVT_EVENT_NEW_MAX)
/**
 * PVT IRQ priority
 */
#define PVT_IRQ_PRIORITY		0	/* Highest Priority */
/**
 * PMIC
 */
#define NODE_SW1	DT_NODELABEL(pca9420_sw1)
#define PMIC_SW1_STEP			25000	/* in micro-Volts*/
/**
 * Allowed VDDCORE range with PVT, in micro-Volts
 */
#define PVT_VDDCORE_MIN			700000
#define PVT_VDDCORE_MAX			900000

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile bool ring_osc_ready = false;
static uint32_t PVT_min_voltage = 0;
static uint32_t PVT_max_voltage = 0;
static const struct device *sw1 = DEVICE_DT_GET(NODE_SW1);

struct k_event pvt_event;
struct k_timer pvt_timer;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void pvt_wait_timer_callback(struct k_timer *timer_id);
static bool pvt_adjust_vddcore(void);
static void config_pvt(void);
static void read_pvt_delay_from_ring_osc(uint8_t *delay);

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * PVT0 interrupt handler that disables PVT sensing and signals/yields to the
 * PVT task to immediately increase VDDCORE.
 */
void PVT_isr(void *arg)
{
	NVIC_ClearPendingIRQ((IRQn_Type) PVT0_IRQn);
	/* Disable the PVT sensor so it doesn't keep interrupting while we try to increase VDDCORE */
	PVT_Stop();
	/* trigger PVT task to increase VDDCORE immediately */
	k_event_post(&pvt_event, PVT_EVENT_SENSOR_IRQ);
}

/**
 * Sets PVT_min_voltage
 */
void set_PVT_min_voltage(uint32_t min)
{
	assert(min >= PVT_VDDCORE_MIN);
	assert(min <= PVT_max_voltage);

	PVT_min_voltage = min;
	/* trigger PVT task */
	k_event_post(&pvt_event, PVT_EVENT_NEW_MIN);
}

/**
 * Sets PVT_max_voltage
 */
void set_PVT_max_voltage(uint32_t max)
{
	assert(max <= PVT_VDDCORE_MAX);
	assert(max >= PVT_min_voltage);

	PVT_max_voltage = max;
	/* trigger PVT task */
	k_event_post(&pvt_event, PVT_EVENT_NEW_MAX);
}

/**
 * Timer callback for PVT task to adjust VDDCORE.
 */
static void pvt_wait_timer_callback(struct k_timer *timer_id) {
	/* Trigger the PVT task to increase VDDCORE immediately */
	k_event_post(&pvt_event, PVT_EVENT_TIMER);
}

/**
 * Finds the optimal VDDCORE for the application.
 * Runs when one of the following conditions is met:
 *     (a) First time running
 *     (b) PVT Interrupt triggered
 *     (c) VDDCORE > PVT_min_voltage and WAIT_TIMER expired
 *     (d) PVT_min_voltage/PVT_max_voltage changed by app
 */
void pvt_thread(void *dummy1, void *dummy2, void *dummy3)
{
	bool at_min_vddcore = false;

	printk("PVT Lib Version = 0x%06x\r\n", PVT_GetLibVersion());

	/* Confirm PVT min and max were configured, and valid */
	assert(PVT_min_voltage >= PVT_VDDCORE_MIN);
	assert(PVT_max_voltage <= PVT_VDDCORE_MAX);

	/* connect ISR to PVT IRQ */
	IRQ_CONNECT(PVT0_IRQn, PVT_IRQ_PRIORITY, PVT_isr, 0, 0);

	k_event_init(&pvt_event);
	k_timer_init(&pvt_timer, pvt_wait_timer_callback, NULL);

	/* Start the pvt sensor */
	config_pvt();

	while(1)
	{
	#ifdef CONFIG_PM
		/* Prevent Deep Sleep mode while adjusting VDDCORE*/
		pm_policy_state_lock_get(PM_STATE_SUSPEND_TO_IDLE,
					 PM_ALL_SUBSTATES);
	#endif
		at_min_vddcore = pvt_adjust_vddcore();
	#ifdef CONFIG_PM
		pm_policy_state_lock_put(PM_STATE_SUSPEND_TO_IDLE,
					 PM_ALL_SUBSTATES);
	#endif

		if (at_min_vddcore)
		{
		#ifdef CONFIG_SMARTWATCH_FOR_MEASUREMENTS
			/* To allow consistent power measurements, disable the
			 * PVT interrupt after pvt_thread() settles on the
			 * minimum voltage.  This prevents the PVT Sensor from
			 * increasing VDDCORE during the measurements.
			 * Disabling the IRQ can lead to issues in some
			 * conditions, and only works in warmer temperatures. */
			DisableIRQ((IRQn_Type) PVT0_IRQn);
		#endif
		} else
		{
			/* Only enable periodic timer if it's possible for
			   VDDCORE to go lower */
			k_timer_start(&pvt_timer, K_MSEC(PVT_TASK_WAIT_MS),
					K_NO_WAIT);
		}

		/* Wait for pvt_thread event */
		k_event_wait(&pvt_event, PVT_EVENT_MASK, true, K_FOREVER);
	}
}

/**
 * Increases VDDCORE if the PVT interrupt triggered, else it tries
 * to decrease VDDCORE as much as possible.
 *
 * Returns true if VDDCORE == PVT_min_voltage, false otherwise.
 * ToDo leverage PVT_max_voltage:
 * 	- PVT interrupt can be disable if VDDCORE >= PVT_max_voltage
 * 	- handle when the app changes PVT_max_voltage after PVT initialized
 */
static bool pvt_adjust_vddcore(void)
{
	int ret;
	uint32_t cur_vddcore;

	ret = regulator_get_voltage(sw1, &cur_vddcore);
	assert(ret == 0);

	if (PVT_GetAlertCount() > 0) {
		/* PVT interrupt fired, so we increase VDDCORE */
		cur_vddcore += PMIC_SW1_STEP;
		ret = regulator_set_voltage(sw1, cur_vddcore, cur_vddcore);
		assert(ret == 0);

		PVT_ClearAlertCount();
		PVT_Start();
		return false;
	}

	/* Try to decrease VDDCORE as much as possible until we reach 
	 * PVT_min_voltage or PVT interrupt fires */
	while (cur_vddcore > PVT_min_voltage) {
		cur_vddcore -= PMIC_SW1_STEP;
		ret = regulator_set_voltage(sw1, cur_vddcore, cur_vddcore);
		assert(ret == 0);

		k_timer_start(&pvt_timer, K_MSEC(PMIC_SETTLING_TIME_MS),
					K_NO_WAIT);
		k_event_wait(&pvt_event, PVT_EVENT_MASK, true, K_FOREVER);
		k_timer_stop(&pvt_timer);
		if (PVT_GetAlertCount() > 0)
		{
			cur_vddcore += PMIC_SW1_STEP;
			ret = regulator_set_voltage(sw1, cur_vddcore, cur_vddcore);
			assert(ret == 0);

			PVT_ClearAlertCount();
			PVT_Start();
			break;
		}
	}

	/* If PVT_min_voltage was increased, raise VDDCORE to new min */
	if(cur_vddcore < PVT_min_voltage)
	{
		cur_vddcore = PVT_min_voltage;
		ret = regulator_set_voltage(sw1, cur_vddcore, cur_vddcore);
		assert(ret == 0);
	}

	return (cur_vddcore <= PVT_min_voltage);
}

/**
 * Enables the PVT ring oscillator, reads and sets the PVT delay,
 * enables the PVT alert counter, enables the PVT interrupt,
 * and finally starts the PVT sensing.
 * */
static void config_pvt(void)
{
	pvt_delay_t delay;
	status_t status;
	bool read_from_otp = true;
	uint32_t prev_vddcore;
	int ret;

	PVT_Init();

	/* Disable LVD interrupt and reset, and set it to the lowest setting */
	PMC->CTRL &= ~(PMC_CTRL_LVDCORERE_MASK | PMC_CTRL_LVDCOREIE_MASK);
	PMC->LVDCORECTRL = 0;

	/* Try to read delay from OTP. If unsuccessful, try to read from 
	 * ring oscillator */
	status = PVT_ReadDelayFromOTP(false, CLOCK_GetFreq(kCLOCK_CoreSysClk),
					&delay);
	if (status != kStatus_Success)
	{
		/* VDDCORE must == 0.9V and and temp. == 25C before calling 
		 * PVT_ReadDelayFromRingOsc() */
		printk( "\033[35;1m"						\
			"WARNING: "						\
			"\033[0m"						\
			"Reading delay from Ring Osc. "				\
			"Make sure the following are met:\r\n"			\
			"    VDDCORE     == 0.9V\r\n"				\
			"    Temperature == 25C\r\n\n");
		ret = regulator_get_voltage(sw1, &prev_vddcore);
		assert(ret == 0);
		assert(prev_vddcore <= VDDCORE_RINGO_VOLTAGE);

		read_pvt_delay_from_ring_osc(&delay);
		read_from_otp = false;

		if(prev_vddcore != VDDCORE_RINGO_VOLTAGE)
		{
			/* Restore previous voltage level */
			ret = regulator_set_voltage(sw1, prev_vddcore,
							 prev_vddcore);
			assert(ret == 0);
		}
	}

	printk("%s%u\r\n\n", (read_from_otp == true) ? 
		"OTP Delay = " : "Ring Osc. Delay = ", delay);

	/* Enable interrupt */
	NVIC_ClearPendingIRQ((IRQn_Type) PVT0_IRQn);
	EnableIRQ((IRQn_Type) PVT0_IRQn);

	/* Checks if the PVT interrupt triggered when trying to optimize VDDCORE */
	PVT_EnableAlertCount();

	/* Set the delay and start sensing */
	PVT_SetDelay(delay);
	PVT_Start();
}

/**
 * Follows the specific sequence as defined in the pvt.h documentation to read 
 * the delay from the ring oscillator.
 */
static void read_pvt_delay_from_ring_osc(uint8_t *delay)
{
	status_t status;

	PVT_EnableRingOsc();
	ring_osc_ready = false;

	/* Wait to measure ring oscillator frequency, API takes micro-seconds */
	k_busy_wait(PVT_RING_OSC_WAIT_TIME_MS * 1000U);

	status = PVT_ReadDelayFromRingOsc(PVT_RING_OSC_WAIT_TIME_MS, delay);
	PVT_DisableRingOsc();
	assert(status == kStatus_Success);
}
