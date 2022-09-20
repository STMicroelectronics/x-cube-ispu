/**
  ******************************************************************************
  * @file    custom_mems_conf.h
  * @author  MEMS Application Team
  * @brief   This file contains definitions of the MEMS components bus interfaces for custom boards
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CUSTOM_MEMS_CONF_H__
#define __CUSTOM_MEMS_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_bus.h"
#include "stm32f4xx_nucleo_errno.h"

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#define USE_CUSTOM_MOTION_SENSOR_LIS2MDL_0        1U

#define USE_CUSTOM_ENV_SENSOR_HTS221_0            1U

#define USE_CUSTOM_ENV_SENSOR_LPS22HH_0           1U

#define CUSTOM_LIS2MDL_0_I2C_Init BSP_I2C1_Init
#define CUSTOM_LIS2MDL_0_I2C_DeInit BSP_I2C1_DeInit
#define CUSTOM_LIS2MDL_0_I2C_ReadReg BSP_I2C1_ReadReg
#define CUSTOM_LIS2MDL_0_I2C_WriteReg BSP_I2C1_WriteReg

#define CUSTOM_HTS221_0_I2C_Init BSP_I2C1_Init
#define CUSTOM_HTS221_0_I2C_DeInit BSP_I2C1_DeInit
#define CUSTOM_HTS221_0_I2C_ReadReg BSP_I2C1_ReadReg
#define CUSTOM_HTS221_0_I2C_WriteReg BSP_I2C1_WriteReg

#define CUSTOM_LPS22HH_0_I2C_Init BSP_I2C1_Init
#define CUSTOM_LPS22HH_0_I2C_DeInit BSP_I2C1_DeInit
#define CUSTOM_LPS22HH_0_I2C_ReadReg BSP_I2C1_ReadReg
#define CUSTOM_LPS22HH_0_I2C_WriteReg BSP_I2C1_WriteReg

#ifdef __cplusplus
}
#endif

#endif /* __CUSTOM_MEMS_CONF_H__*/
