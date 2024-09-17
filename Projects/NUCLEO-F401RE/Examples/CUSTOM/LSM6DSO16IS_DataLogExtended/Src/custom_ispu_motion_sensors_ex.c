/**
  ******************************************************************************
  * @file    custom_ispu_motion_sensors_ex.c
  * @author  MEMS Software Solutions Team
  * @brief   This file provides BSP Motion Sensors Extended interface for custom boards
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

/* Includes ------------------------------------------------------------------*/
#include "custom_ispu_motion_sensors_ex.h"

extern void *IspuMotionCompObj[CUSTOM_ISPU_MOTION_INSTANCES_NBR];

/* MISRAC2012-Rule-11.5 violations due to compatibility with external MEMS1 package */

/**
  * @brief  Get the register value
  * @param  Instance the device instance
  * @param  Reg address to be read
  * @param  Data pointer where the value is written to
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_Read_Register(uint32_t Instance, uint8_t Reg, uint8_t *Data)
{
  int32_t ret;

  switch (Instance)
  {

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO16IS_0 == 1)
    case CUSTOM_LSM6DSO16IS_0:
      if (LSM6DSO16IS_Read_Reg((LSM6DSO16IS_Object_t *)IspuMotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif /* USE_CUSTOM_MOTION_SENSOR_LSM6DSO16IS_0 */

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
  * @brief  Set the register value
  * @param  Instance the device instance
  * @param  Reg address to be read
  * @param  Data value to be written
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_Write_Register(uint32_t Instance, uint8_t Reg, uint8_t Data)
{
  int32_t ret;

  switch (Instance)
  {

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO16IS_0 == 1)
    case CUSTOM_LSM6DSO16IS_0:
      if (LSM6DSO16IS_Write_Reg((LSM6DSO16IS_Object_t *)IspuMotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif /* USE_CUSTOM_MOTION_SENSOR_LSM6DSO16IS_0 */

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
  * @brief  Get the status of data ready bit
  * @param  Instance the device instance
  * @param  Function Motion sensor function
  * @param  Status the pointer to the status
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_Get_DRDY_Status(uint32_t Instance, uint32_t Function, uint8_t *Status)
{
  int32_t ret;

  switch (Instance)
  {

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO16IS_0 == 1)
    case CUSTOM_LSM6DSO16IS_0:
      if ((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
      {
        if (LSM6DSO16IS_ACC_Get_DRDY_Status((LSM6DSO16IS_Object_t *)IspuMotionCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else if ((Function & MOTION_GYRO) == MOTION_GYRO)
      {
        if (LSM6DSO16IS_GYRO_Get_DRDY_Status((LSM6DSO16IS_Object_t *)IspuMotionCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      break;
#endif /* USE_CUSTOM_MOTION_SENSOR_LSM6DSO16IS_0 */

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}
