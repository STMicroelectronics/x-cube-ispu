/**
  ******************************************************************************
  * @file    custom_mems_control_ex.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains the MEMS sensors interface for custom board
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
#ifndef CUSTOM_MEMS_CONTROL_EX_H
#define CUSTOM_MEMS_CONTROL_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "RTE_Components.h"

#if (defined BSP_ISPU_MOTION_SENSORS)
#include "custom_ispu_motion_sensors.h"
#include "custom_ispu_motion_sensors_ex.h"
#endif /* BSP_ISPU_MOTION_SENSORS */

#if (defined BSP_MOTION_SENSORS)
#include "custom_motion_sensors.h"
#include "custom_motion_sensors_ex.h"
#endif /* BSP_MOTION_SENSORS */

#if (defined BSP_ENV_SENSORS)
#include "custom_env_sensors.h"
#include "custom_env_sensors_ex.h"
#endif /* BSP_ENV_SENSORS */

#if (defined BSP_HYBRID_SENSORS)
#include "custom_hybrid_sensors.h"
#include "custom_hybrid_sensors_ex.h"
#endif /* BSP_HYBRID_SENSORS */

void BSP_SENSOR_ACC_Read_Register(uint8_t Reg, uint8_t *Data);
void BSP_SENSOR_GYR_Read_Register(uint8_t Reg, uint8_t *Data);
void BSP_SENSOR_MAG_Read_Register(uint8_t Reg, uint8_t *Data);
void BSP_SENSOR_PRESS_Read_Register(uint8_t Reg, uint8_t *Data);
void BSP_SENSOR_TEMP_Read_Register(uint8_t Reg, uint8_t *Data);
void BSP_SENSOR_HUM_Read_Register(uint8_t Reg, uint8_t *Data);

void BSP_SENSOR_ACC_Write_Register(uint8_t Reg, uint8_t Data);
void BSP_SENSOR_GYR_Write_Register(uint8_t Reg, uint8_t Data);
void BSP_SENSOR_MAG_Write_Register(uint8_t Reg, uint8_t Data);
void BSP_SENSOR_PRESS_Write_Register(uint8_t Reg, uint8_t Data);
void BSP_SENSOR_TEMP_Write_Register(uint8_t Reg, uint8_t Data);
void BSP_SENSOR_HUM_Write_Register(uint8_t Reg, uint8_t Data);

void BSP_SENSOR_ACC_Get_DRDY_Status(uint8_t *Status);
void BSP_SENSOR_GYR_Get_DRDY_Status(uint8_t *Status);
void BSP_SENSOR_MAG_Get_DRDY_Status(uint8_t *Status);
void BSP_SENSOR_PRESS_Get_DRDY_Status(uint8_t *Status);
void BSP_SENSOR_TEMP_Get_DRDY_Status(uint8_t *Status);
void BSP_SENSOR_HUM_Get_DRDY_Status(uint8_t *Status);

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_MEMS_CONTROL_EX_H */
