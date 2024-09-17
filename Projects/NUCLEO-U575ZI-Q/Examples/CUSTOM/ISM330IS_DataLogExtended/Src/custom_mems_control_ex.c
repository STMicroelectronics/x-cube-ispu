/**
  ******************************************************************************
  * @file    custom_mems_control_ex.c
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

#include "custom_mems_control_ex.h"
#include "custom_ispu_mems_conf.h"
#include "custom_ispu_mems_conf_app.h"

/**
  * @brief  Get the register value from accelerometer
  * @param  Reg address to be read
  * @param  Data pointer where the value is written to
  * @retval None
  */
void BSP_SENSOR_ACC_Read_Register(uint8_t Reg, uint8_t *Data)
{
#if (defined BSP_ISPU_MOTION_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_ISPU_MOTION_SENSOR_Read_Register(CUSTOM_ACC_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#elif (defined BSP_HYBRID_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_HYBRID_SENSOR_Read_Register(CUSTOM_ACC_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#elif (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Read_Register(CUSTOM_ACC_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#endif /* BSP_ISPU_MOTION_SENSORS */
}

/**
  * @brief  Get the register value from gyroscope
  * @param  Reg address to be read
  * @param  Data pointer where the value is written to
  * @retval None
  */
void BSP_SENSOR_GYR_Read_Register(uint8_t Reg, uint8_t *Data)
{
#if (defined BSP_ISPU_MOTION_SENSORS)
#ifdef CUSTOM_GYR_INSTANCE_0
  (void)CUSTOM_ISPU_MOTION_SENSOR_Read_Register(CUSTOM_GYR_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_GYR_INSTANCE_0 */
#elif (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_GYR_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Read_Register(CUSTOM_GYR_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_GYR_INSTANCE_0 */
#endif /* BSP_ISPU_MOTION_SENSORS */
}

/**
  * @brief  Get the register value from magnetometer
  * @param  Reg address to be read
  * @param  Data pointer where the value is written to
  * @retval None
  */
void BSP_SENSOR_MAG_Read_Register(uint8_t Reg, uint8_t *Data)
{
#if (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_MAG_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Read_Register(CUSTOM_MAG_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_MAG_INSTANCE_0 */
#endif /* BSP_MOTION_SENSORS */
}

/**
  * @brief  Get the register value from pressure sensor
  * @param  Reg address to be read
  * @param  Data pointer where the value is written to
  * @retval None
  */
void BSP_SENSOR_PRESS_Read_Register(uint8_t Reg, uint8_t *Data)
{
#if (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_PRESS_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Read_Register(CUSTOM_PRESS_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_PRESS_INSTANCE_0 */
#endif /* BSP_ENV_SENSORS */
}

/**
  * @brief  Get the register value from temperature sensor
  * @param  Reg address to be read
  * @param  Data pointer where the value is written to
  * @retval None
  */
void BSP_SENSOR_TEMP_Read_Register(uint8_t Reg, uint8_t *Data)
{
#if (defined BSP_HYBRID_SENSORS)
#ifdef CUSTOM_TEMP_INSTANCE_0
  (void)CUSTOM_HYBRID_SENSOR_Read_Register(CUSTOM_TEMP_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_TEMP_INSTANCE_0 */
#elif (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_TEMP_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Read_Register(CUSTOM_TEMP_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_TEMP_INSTANCE_0 */
#endif /* BSP_HYBRID_SENSORS */
}

/**
  * @brief  Get the register value from humidity sensor
  * @param  Reg address to be read
  * @param  Data pointer where the value is written to
  * @retval None
  */
void BSP_SENSOR_HUM_Read_Register(uint8_t Reg, uint8_t *Data)
{
#if (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_HUM_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Read_Register(CUSTOM_HUM_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_HUM_INSTANCE_0 */
#endif /* BSP_ENV_SENSORS */
}

/**
  * @brief  Set the register value
  * @param  Reg address to be read
  * @param  Data value to be written
  * @retval None
  */
void BSP_SENSOR_ACC_Write_Register(uint8_t Reg, uint8_t Data)
{
#if (defined BSP_ISPU_MOTION_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_ISPU_MOTION_SENSOR_Write_Register(CUSTOM_ACC_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#elif (defined BSP_HYBRID_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_HYBRID_SENSOR_Write_Register(CUSTOM_ACC_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#elif (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Write_Register(CUSTOM_ACC_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#endif /* BSP_ISPU_MOTION_SENSORS */
}

/**
  * @brief  Set the register value
  * @param  Reg address to be read
  * @param  Data value to be written
  * @retval None
  */
void BSP_SENSOR_GYR_Write_Register(uint8_t Reg, uint8_t Data)
{
#if (defined BSP_ISPU_MOTION_SENSORS)
#ifdef CUSTOM_GYR_INSTANCE_0
  (void)CUSTOM_ISPU_MOTION_SENSOR_Write_Register(CUSTOM_GYR_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_GYR_INSTANCE_0 */
#elif (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_GYR_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Write_Register(CUSTOM_GYR_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_GYR_INSTANCE_0 */
#endif /* BSP_ISPU_MOTION_SENSORS */
}

/**
  * @brief  Set the register value
  * @param  Reg address to be read
  * @param  Data value to be written
  * @retval None
  */
void BSP_SENSOR_MAG_Write_Register(uint8_t Reg, uint8_t Data)
{
#if (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_MAG_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Write_Register(CUSTOM_MAG_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_MAG_INSTANCE_0 */
#endif /* BSP_MOTION_SENSORS */
}

/**
  * @brief  Set the register value in pressure sensor
  * @param  Reg address to be read
  * @param  Data value to be written
  * @retval None
  */
void BSP_SENSOR_PRESS_Write_Register(uint8_t Reg, uint8_t Data)
{
#if (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_PRESS_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Write_Register(CUSTOM_PRESS_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_PRESS_INSTANCE_0 */
#endif /* BSP_ENV_SENSORS */
}

/**
  * @brief  Set the register value in temperature sensor
  * @param  Reg address to be read
  * @param  Data value to be written
  * @retval None
  */
void BSP_SENSOR_TEMP_Write_Register(uint8_t Reg, uint8_t Data)
{
#if (defined BSP_HYBRID_SENSORS)
#ifdef CUSTOM_TEMP_INSTANCE_0
  (void)CUSTOM_HYBRID_SENSOR_Write_Register(CUSTOM_TEMP_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_TEMP_INSTANCE_0 */
#elif (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_TEMP_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Write_Register(CUSTOM_TEMP_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_TEMP_INSTANCE_0 */
#endif /* BSP_HYBRID_SENSORS */
}

/**
  * @brief  Set the register value in humidity sensor
  * @param  Reg address to be read
  * @param  Data value to be written
  * @retval None
  */
void BSP_SENSOR_HUM_Write_Register(uint8_t Reg, uint8_t Data)
{
#if (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_HUM_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Write_Register(CUSTOM_HUM_INSTANCE_0, Reg, Data);
#endif /* CUSTOM_HUM_INSTANCE_0 */
#endif /* BSP_ENV_SENSORS */
}

/**
  * @brief  Get the status of data ready bit
  * @param  Instance the device instance
  * @param  Status the pointer to the status
  * @retval None
  */
void BSP_SENSOR_ACC_Get_DRDY_Status(uint8_t *Status)
{
#if (defined BSP_ISPU_MOTION_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_ISPU_MOTION_SENSOR_Get_DRDY_Status(CUSTOM_ACC_INSTANCE_0, MOTION_ACCELERO, Status);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#elif (defined BSP_HYBRID_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_HYBRID_SENSOR_Get_DRDY_Status(CUSTOM_ACC_INSTANCE_0, HYBRID_ACCELERO, Status);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#elif (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_ACC_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Get_DRDY_Status(CUSTOM_ACC_INSTANCE_0, MOTION_ACCELERO, Status);
#endif /* CUSTOM_ACC_INSTANCE_0 */
#endif /* BSP_ISPU_MOTION_SENSORS */
}

/**
  * @brief  Get the status of data ready bit
  * @param  Instance the device instance
  * @param  Status the pointer to the status
  * @retval None
  */
void BSP_SENSOR_GYR_Get_DRDY_Status(uint8_t *Status)
{
#if (defined BSP_ISPU_MOTION_SENSORS)
#ifdef CUSTOM_GYR_INSTANCE_0
  (void)CUSTOM_ISPU_MOTION_SENSOR_Get_DRDY_Status(CUSTOM_GYR_INSTANCE_0, MOTION_GYRO, Status);
#endif /* CUSTOM_GYR_INSTANCE_0 */
#elif (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_GYR_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Get_DRDY_Status(CUSTOM_GYR_INSTANCE_0, MOTION_GYRO, Status);
#endif /* CUSTOM_GYR_INSTANCE_0 */
#endif /* BSP_ISPU_MOTION_SENSORS */
}

/**
  * @brief  Get the status of data ready bit
  * @param  Instance the device instance
  * @param  Status the pointer to the status
  * @retval None
  */
void BSP_SENSOR_MAG_Get_DRDY_Status(uint8_t *Status)
{
#if (defined BSP_MOTION_SENSORS)
#ifdef CUSTOM_MAG_INSTANCE_0
  (void)CUSTOM_MOTION_SENSOR_Get_DRDY_Status(CUSTOM_MAG_INSTANCE_0, MOTION_MAGNETO, Status);
#endif /* CUSTOM_MAG_INSTANCE_0 */
#endif /* BSP_MOTION_SENSORS */
}

/**
  * @brief  Get the status of data ready bit
  * @param  Instance the device instance
  * @param  Status the pointer to the status
  * @retval None
  */
void BSP_SENSOR_PRESS_Get_DRDY_Status(uint8_t *Status)
{
#if (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_PRESS_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Get_DRDY_Status(CUSTOM_PRESS_INSTANCE_0, ENV_PRESSURE, Status);
#endif /* CUSTOM_PRESS_INSTANCE_0 */
#endif /* BSP_ENV_SENSORS */
}

/**
  * @brief  Get the status of data ready bit
  * @param  Instance the device instance
  * @param  Status the pointer to the status
  * @retval None
  */
void BSP_SENSOR_TEMP_Get_DRDY_Status(uint8_t *Status)
{
#if (defined BSP_HYBRID_SENSORS)
#ifdef CUSTOM_TEMP_INSTANCE_0
  (void)CUSTOM_HYBRID_SENSOR_Get_DRDY_Status(CUSTOM_TEMP_INSTANCE_0, HYBRID_TEMPERATURE, Status);
#endif /* CUSTOM_TEMP_INSTANCE_0 */
#elif (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_TEMP_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Get_DRDY_Status(CUSTOM_TEMP_INSTANCE_0, ENV_TEMPERATURE, Status);
#endif /* CUSTOM_TEMP_INSTANCE_0 */
#endif /* BSP_HYBRID_SENSORS */
}

/**
  * @brief  Get the status of data ready bit
  * @param  Instance the device instance
  * @param  Status the pointer to the status
  * @retval None
  */
void BSP_SENSOR_HUM_Get_DRDY_Status(uint8_t *Status)
{
#if (defined BSP_ENV_SENSORS)
#ifdef CUSTOM_HUM_INSTANCE_0
  (void)CUSTOM_ENV_SENSOR_Get_DRDY_Status(CUSTOM_HUM_INSTANCE_0, ENV_HUMIDITY, Status);
#endif /* CUSTOM_HUM_INSTANCE_0 */
#endif /* BSP_ENV_SENSORS */
}
