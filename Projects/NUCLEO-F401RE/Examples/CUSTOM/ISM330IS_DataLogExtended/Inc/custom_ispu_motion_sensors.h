/**
  ******************************************************************************
  * @file    custom_ispu_motion_sensors.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains definitions for the BSP Motion Sensors interface for custom boards
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CUSTOM_ISPU_MOTION_SENSORS_H
#define CUSTOM_ISPU_MOTION_SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "custom_ispu_mems_conf.h"
#include "motion_sensor.h"

#if (USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 == 1)
#include "ism330is.h"
#endif /* USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 */

#if (USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 == 1)
#define CUSTOM_ISM330IS_0 (0)
#endif /* USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 */

typedef struct
{
  int32_t x;
  int32_t y;
  int32_t z;
} CUSTOM_ISPU_MOTION_SENSOR_Axes_t;

typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
} CUSTOM_ISPU_MOTION_SENSOR_AxesRaw_t;

/* Motion Sensor instance Info */
typedef struct
{
  uint8_t  Acc;
  uint8_t  Gyro;
  uint8_t  Magneto;
  uint8_t  LowPower;
  uint32_t GyroMaxFS;
  uint32_t AccMaxFS;
  uint32_t MagMaxFS;
  float_t  GyroMaxOdr;
  float_t  AccMaxOdr;
  float_t  MagMaxOdr;
} CUSTOM_ISPU_MOTION_SENSOR_Capabilities_t;

typedef struct
{
  uint32_t Functions;
} CUSTOM_ISPU_MOTION_SENSOR_Ctx_t;

#ifndef MOTION_GYRO
#define MOTION_GYRO             1U
#endif /* MOTION_GYRO */
#ifndef MOTION_ACCELERO
#define MOTION_ACCELERO         2U
#endif /* MOTION_ACCELERO */
#ifndef MOTION_MAGNETO
#define MOTION_MAGNETO          4U
#endif /* MOTION_MAGNETO */

#ifndef CUSTOM_MOTION_FUNCTIONS_NBR
#define CUSTOM_MOTION_FUNCTIONS_NBR    3U
#endif /* CUSTOM_MOTION_FUNCTIONS_NBR */

#define CUSTOM_ISPU_MOTION_INSTANCES_NBR    (USE_CUSTOM_MOTION_SENSOR_ISM330IS_0)

#if (CUSTOM_ISPU_MOTION_INSTANCES_NBR == 0)
#error "No motion sensor instance has been selected"
#endif /* CUSTOM_ISPU_MOTION_INSTANCES_NBR */

int32_t CUSTOM_ISPU_MOTION_SENSOR_Init(uint32_t Instance, uint32_t Functions);
int32_t CUSTOM_ISPU_MOTION_SENSOR_DeInit(uint32_t Instance);
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetCapabilities(uint32_t Instance,
                                                  CUSTOM_ISPU_MOTION_SENSOR_Capabilities_t *Capabilities);
int32_t CUSTOM_ISPU_MOTION_SENSOR_ReadID(uint32_t Instance, uint8_t *Id);
int32_t CUSTOM_ISPU_MOTION_SENSOR_Enable(uint32_t Instance, uint32_t Function);
int32_t CUSTOM_ISPU_MOTION_SENSOR_Disable(uint32_t Instance, uint32_t Function);
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetAxes(uint32_t Instance, uint32_t Function, CUSTOM_ISPU_MOTION_SENSOR_Axes_t *Axes);
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetAxesRaw(uint32_t Instance, uint32_t Function,
                                             CUSTOM_ISPU_MOTION_SENSOR_AxesRaw_t *Axes);
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetSensitivity(uint32_t Instance, uint32_t Function, float_t *Sensitivity);
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetOutputDataRate(uint32_t Instance, uint32_t Function, float_t *Odr);
int32_t CUSTOM_ISPU_MOTION_SENSOR_SetOutputDataRate(uint32_t Instance, uint32_t Function, float_t Odr);
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetFullScale(uint32_t Instance, uint32_t Function, int32_t *Fullscale);
int32_t CUSTOM_ISPU_MOTION_SENSOR_SetFullScale(uint32_t Instance, uint32_t Function, int32_t Fullscale);

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_ISPU_MOTION_SENSORS_H */
