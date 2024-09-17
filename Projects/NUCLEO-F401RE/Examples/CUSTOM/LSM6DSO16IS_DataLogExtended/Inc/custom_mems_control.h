/**
  ******************************************************************************
  * @file    custom_mems_control.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains the MEMS sensors interface for custom board
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CUSTOM_MEMS_CONTROL_H
#define CUSTOM_MEMS_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "RTE_Components.h"

#if (defined BSP_ISPU_MOTION_SENSORS)
#include "custom_ispu_motion_sensors.h"
#endif /* BSP_ISPU_MOTION_SENSORS */

#if (defined BSP_MOTION_SENSORS)
#include "custom_motion_sensors.h"
#endif /* BSP_MOTION_SENSORS */

#if (defined BSP_ENV_SENSORS)
#include "custom_env_sensors.h"
#endif /* BSP_ENV_SENSORS */

#if (defined BSP_HYBRID_SENSORS)
#include "custom_hybrid_sensors.h"
#endif /* BSP_HYBRID_SENSORS */

typedef struct
{
  int32_t x;
  int32_t y;
  int32_t z;
} ISPU_MOTION_SENSOR_Axes_t;

int32_t BSP_SENSOR_ACC_Init(void);
int32_t BSP_SENSOR_GYR_Init(void);
int32_t BSP_SENSOR_MAG_Init(void);
int32_t BSP_SENSOR_PRESS_Init(void);
int32_t BSP_SENSOR_TEMP_Init(void);
int32_t BSP_SENSOR_HUM_Init(void);

void BSP_SENSOR_ACC_Enable(void);
void BSP_SENSOR_GYR_Enable(void);
void BSP_SENSOR_MAG_Enable(void);
void BSP_SENSOR_PRESS_Enable(void);
void BSP_SENSOR_TEMP_Enable(void);
void BSP_SENSOR_HUM_Enable(void);

void BSP_SENSOR_ACC_Disable(void);
void BSP_SENSOR_GYR_Disable(void);
void BSP_SENSOR_MAG_Disable(void);
void BSP_SENSOR_PRESS_Disable(void);
void BSP_SENSOR_TEMP_Disable(void);
void BSP_SENSOR_HUM_Disable(void);

void BSP_SENSOR_ACC_GetAxes(ISPU_MOTION_SENSOR_Axes_t *Axes);
void BSP_SENSOR_GYR_GetAxes(ISPU_MOTION_SENSOR_Axes_t *Axes);
void BSP_SENSOR_MAG_GetAxes(ISPU_MOTION_SENSOR_Axes_t *Axes);
void BSP_SENSOR_PRESS_GetValue(float_t *Value);
void BSP_SENSOR_TEMP_GetValue(float_t *Value);
void BSP_SENSOR_HUM_GetValue(float_t *Value);

void BSP_SENSOR_ACC_SetOutputDataRate(float_t Odr);
void BSP_SENSOR_GYR_SetOutputDataRate(float_t Odr);
void BSP_SENSOR_MAG_SetOutputDataRate(float_t Odr);
void BSP_SENSOR_PRESS_SetOutputDataRate(float_t Odr);
void BSP_SENSOR_TEMP_SetOutputDataRate(float_t Odr);
void BSP_SENSOR_HUM_SetOutputDataRate(float_t Odr);

void BSP_SENSOR_ACC_GetOutputDataRate(float_t *Odr);
void BSP_SENSOR_GYR_GetOutputDataRate(float_t *Odr);
void BSP_SENSOR_MAG_GetOutputDataRate(float_t *Odr);
void BSP_SENSOR_PRESS_GetOutputDataRate(float_t *Odr);
void BSP_SENSOR_TEMP_GetOutputDataRate(float_t *Odr);
void BSP_SENSOR_HUM_GetOutputDataRate(float_t *Odr);

void BSP_SENSOR_ACC_SetFullScale(int32_t Fullscale);
void BSP_SENSOR_GYR_SetFullScale(int32_t Fullscale);
void BSP_SENSOR_MAG_SetFullScale(int32_t Fullscale);

void BSP_SENSOR_ACC_GetFullScale(int32_t *Fullscale);
void BSP_SENSOR_GYR_GetFullScale(int32_t *Fullscale);
void BSP_SENSOR_MAG_GetFullScale(int32_t *Fullscale);

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_MEMS_CONTROL_H */
