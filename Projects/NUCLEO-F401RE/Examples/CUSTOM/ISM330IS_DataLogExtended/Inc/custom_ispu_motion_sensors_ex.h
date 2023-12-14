/**
  ******************************************************************************
  * @file    custom_ispu_motion_sensors_ex.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains definitions for the BSP Motion Sensors Extended interface for custom boards
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
#ifndef CUSTOM_ISPU_MOTION_SENSORS_EX_H
#define CUSTOM_ISPU_MOTION_SENSORS_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "custom_ispu_motion_sensors.h"

int32_t CUSTOM_ISPU_MOTION_SENSOR_Read_Register(uint32_t Instance, uint8_t Reg, uint8_t *Data);
int32_t CUSTOM_ISPU_MOTION_SENSOR_Write_Register(uint32_t Instance, uint8_t Reg, uint8_t Data);
int32_t CUSTOM_ISPU_MOTION_SENSOR_Get_DRDY_Status(uint32_t Instance, uint32_t Function, uint8_t *Status);

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_ISPU_MOTION_SENSORS_EX_H */
