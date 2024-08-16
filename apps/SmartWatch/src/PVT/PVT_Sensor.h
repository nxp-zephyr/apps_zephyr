/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 */

#ifndef _PVT_SENSOR_H
#define _PVT_SENSOR_H

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* VDDCORE voltage levels in micro-volts */
#define VDDCORE_192MHZ_SAFE_VMIN	900000
#define VDDCORE_MIPI_VMIN		850000

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void set_PVT_min_voltage(uint32_t min);
void set_PVT_max_voltage(uint32_t max);
void pvt_thread(void *dummy1, void *dummy2, void *dummy3);

#endif /* _PVT_SENSOR_H */
