/**
  ******************************************************************************
  * File Name          : app_x-cube-ispu.c
  * Description        : This file provides code for the configuration
  *                      of the STMicroelectronics.X-CUBE-ISPU.1.1.0 instances.
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

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_x-cube-ispu.h"
#include "main.h"
#include <stdio.h>

#include "com.h"
#include "demo_serial.h"
#include "custom_mems_control.h"
#include "custom_mems_control_ex.h"
#include "custom_ispu_mems_conf_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DWT_LAR_KEY  0xC5ACCE55 /* DWT register unlock key */

/* Public variables ----------------------------------------------------------*/
__IO uint8_t DataLoggerActive = 0;
__IO uint8_t UpdateInterrupt = 0;
__IO uint32_t SensorsEnabled = 0;
__IO uint32_t StartTime = 0;
__IO uint8_t IspuBytes = 64;

/* Private variables ---------------------------------------------------------*/
static __IO uint8_t AutoInit = 0;
static __IO uint32_t IntCurrentTime1 = 0;
static __IO uint32_t IntCurrentTime2 = 0;
static uint8_t NewData = 0;
static uint16_t NewDataFlags = 0;
static uint8_t MsgIndex = 0;

/* Private function prototypes -----------------------------------------------*/
static void MX_DataLogExtended_Init(void);
static void MX_DataLogExtended_Process(void);
static void Enable_Disable_Sensors(void);
static void Time_Handler(TMsg_t *Msg);
static void Pressure_Sensor_Handler(TMsg_t *Msg);
static void Temperature_Sensor_Handler(TMsg_t *Msg);
static void Humidity_Sensor_Handler(TMsg_t *Msg);
static void Accelero_Sensor_Handler(TMsg_t *Msg);
static void Gyro_Sensor_Handler(TMsg_t *Msg);
static void Magneto_Sensor_Handler(TMsg_t *Msg);
static void ISPU_Handler(TMsg_t *Msg);
static void DWT_Init(void);

void MX_X_CUBE_ISPU_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN X_CUBE_ISPU_Init_PreTreatment */

  /* USER CODE END X_CUBE_ISPU_Init_PreTreatment */

  /* Initialize the peripherals and the MEMS components */

  MX_DataLogExtended_Init();

  /* USER CODE BEGIN X_CUBE_ISPU_Init_PostTreatment */

  /* USER CODE END X_CUBE_ISPU_Init_PostTreatment */
}

/*
 * LM background task
 */
void MX_X_CUBE_ISPU_Process(void)
{
  /* USER CODE BEGIN X_CUBE_ISPU_Process_PreTreatment */

  /* USER CODE END X_CUBE_ISPU_Process_PreTreatment */

  MX_DataLogExtended_Process();

  /* USER CODE BEGIN X_CUBE_ISPU_Process_PostTreatment */

  /* USER CODE END X_CUBE_ISPU_Process_PostTreatment */
}

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Start counting clock cycles
  * @param  None
  * @retval None
  */
void DWT_Start(void)
{
  DWT->CYCCNT = 0; /* Clear count of clock cycles */
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; /* Enable counter */
}

/**
  * @brief  Stop counting clock cycles and calculate elapsed time in [us]
  * @param  None
  * @retval Elapsed time in [us]
  */
uint32_t DWT_Stop(void)
{
  __IO uint32_t cycles_count = 0U;
  uint32_t system_core_clock_mhz;
  uint32_t ret;

  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; /* Disable counter */
  cycles_count = DWT->CYCCNT; /* Read count of clock cycles */

  /* Calculate elapsed time in [us] */
  system_core_clock_mhz = SystemCoreClock / 1000000U;
  if (system_core_clock_mhz == 0U)
  {
    ret = 0U;
  }
  else
  {
    ret = cycles_count / system_core_clock_mhz;
  }

  return ret;
}

/**
  * @brief  Calculate elapsed time in [us]
  * @param  None
  * @retval Elapsed time in [us]
  */
uint32_t DWT_GetTick(void)
{
  __IO uint32_t cycles_count = 0U;
  uint32_t system_core_clock_mhz;
  uint32_t ret;

  cycles_count = DWT->CYCCNT; /* Read count of clock cycles */

  /* Calculate elapsed time in [us] */
  system_core_clock_mhz = SystemCoreClock / 1000000U;
  if (system_core_clock_mhz == 0U)
  {
    ret = 0U;
  }
  else
  {
    ret = cycles_count / system_core_clock_mhz;
  }

  return ret;
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initialize the application
  * @retval None
  */
static void MX_DataLogExtended_Init(void)
{
  /* Initialize LED */
  (void)BSP_LED_Init(LED2);

  /* Set EXTI settings for User Interrupt */
  Set_Int_Pins_Exti();

  /* Initialize Virtual COM Port */
  (void)BSP_COM_Init(COM1);

  DWT_Init();

  (void)BSP_LED_On(LED2);
  HAL_Delay(500);
  (void)BSP_LED_Off(LED2);

  /* Start receiving messages via DMA */
  UART_StartReceiveMsg();
}

/**
  * @brief  Process of the application
  * @retval None
  */
static void MX_DataLogExtended_Process(void)
{
  static TMsg_t msg_dat;
  static TMsg_t msg_cmd;
  static uint32_t previous_sensors_enabled = 0U;

  if (UART_ReceivedMSG((TMsg_t *)&msg_cmd) == 1)
  {
    if (msg_cmd.Data[0] == DEV_ADDR)
    {
      (void)HandleMSG((TMsg_t *)&msg_cmd);
    }
  }

  /* Enable/Disable sensors */
  if (previous_sensors_enabled != SensorsEnabled)
  {
    previous_sensors_enabled = SensorsEnabled;
    Enable_Disable_Sensors();
  }

  /* Read data from enabled sensors and prepare data stream */
  if (DataLoggerActive != 0U)
  {
    (void)BSP_LED_Toggle(LED2);

    Time_Handler(&msg_dat);

    if ((SensorsEnabled & PRESSURE_SENSOR_ENABLED) == PRESSURE_SENSOR_ENABLED)
    {
      Pressure_Sensor_Handler(&msg_dat);
    }

    if ((SensorsEnabled & TEMPERATURE_SENSOR_ENABLED) == TEMPERATURE_SENSOR_ENABLED)
    {
      Temperature_Sensor_Handler(&msg_dat);
    }

    if ((SensorsEnabled & HUMIDITY_SENSOR_ENABLED) == HUMIDITY_SENSOR_ENABLED)
    {
      Humidity_Sensor_Handler(&msg_dat);
    }

    if ((SensorsEnabled & ACCELEROMETER_SENSOR_ENABLED) == ACCELEROMETER_SENSOR_ENABLED)
    {
      Accelero_Sensor_Handler(&msg_dat);
    }

    if ((SensorsEnabled & GYROSCOPE_SENSOR_ENABLED) == GYROSCOPE_SENSOR_ENABLED)
    {
      Gyro_Sensor_Handler(&msg_dat);
    }

    if ((SensorsEnabled & MAGNETIC_SENSOR_ENABLED) == MAGNETIC_SENSOR_ENABLED)
    {
      Magneto_Sensor_Handler(&msg_dat);
    }

    if ((SensorsEnabled & ISPU_ENABLED) == ISPU_ENABLED)
    {
      ISPU_Handler(&msg_dat);
    }

    /* Send data stream if new data are available */
    if (NewData != 0U)
    {
      INIT_STREAMING_HEADER(&msg_dat);
      (void)memcpy(&msg_dat.Data[7], (void *)&NewDataFlags, sizeof(uint16_t));
      msg_dat.Len = MsgIndex;
      UART_SendMsg(&msg_dat);
      NewData = 0;
      NewDataFlags = 0;
    }
  }
  else
  {
    (void)BSP_LED_Off(LED2);
  }
}

/**
  * @brief  Enable/disable desired sensors
  * @param  None
  * @retval None
  */
static void Enable_Disable_Sensors(void)
{
  if ((SensorsEnabled & PRESSURE_SENSOR_ENABLED) == PRESSURE_SENSOR_ENABLED)
  {
    BSP_SENSOR_PRESS_Enable();
  }
  else
  {
    BSP_SENSOR_PRESS_Disable();
  }
  if ((SensorsEnabled & TEMPERATURE_SENSOR_ENABLED) == TEMPERATURE_SENSOR_ENABLED)
  {
    BSP_SENSOR_TEMP_Enable();
  }
  else
  {
    BSP_SENSOR_TEMP_Disable();
  }
  if ((SensorsEnabled & HUMIDITY_SENSOR_ENABLED) == HUMIDITY_SENSOR_ENABLED)
  {
    BSP_SENSOR_HUM_Enable();
  }
  else
  {
    BSP_SENSOR_HUM_Disable();
  }
  if ((SensorsEnabled & ACCELEROMETER_SENSOR_ENABLED) == ACCELEROMETER_SENSOR_ENABLED)
  {
    BSP_SENSOR_ACC_Enable();
  }
  else
  {
    BSP_SENSOR_ACC_Disable();
  }
  if ((SensorsEnabled & GYROSCOPE_SENSOR_ENABLED) == GYROSCOPE_SENSOR_ENABLED)
  {
    BSP_SENSOR_GYR_Enable();
  }
  else
  {
    BSP_SENSOR_GYR_Disable();
  }
  if ((SensorsEnabled & MAGNETIC_SENSOR_ENABLED) == MAGNETIC_SENSOR_ENABLED)
  {
    BSP_SENSOR_MAG_Enable();
  }
  else
  {
    BSP_SENSOR_MAG_Disable();
  }
}

/**
  * @brief  Handles the precise time
  * @param  Msg the time part of the stream
  * @retval None
  */
static void Time_Handler(TMsg_t *Msg)
{
  uint32_t time_us;

  time_us = DWT_GetTick();
  Serialize(&Msg->Data[3], time_us, sizeof(uint32_t));
  MsgIndex = 9;
}

/**
  * @brief  Handles the PRESS sensor data getting/sending.
  * @param  Msg the PRESS part of the stream
  * @retval None
  */
static void Pressure_Sensor_Handler(TMsg_t *Msg)
{
  uint8_t status = 0U;
  float_t press_value = 0.0f;

  BSP_SENSOR_PRESS_Get_DRDY_Status(&status);

  if (status == 1U)
  {
    NewData++;
    NewDataFlags |= 1U;

    BSP_SENSOR_PRESS_GetValue(&press_value);

    (void)memcpy((void *)&Msg->Data[MsgIndex], (void *)&press_value, sizeof(float_t));
    MsgIndex += (uint8_t)sizeof(float_t);
  }
}

/**
  * @brief  Handles the TEMP axes data getting/sending
  * @param  Msg the TEMP part of the stream
  * @retval None
  */
static void Temperature_Sensor_Handler(TMsg_t *Msg)
{
  uint8_t status = 0U;
  float_t temp_value = 0.0f;

  BSP_SENSOR_TEMP_Get_DRDY_Status(&status);

  if (status == 1U)
  {
    NewData++;
    NewDataFlags |= 2U;

    BSP_SENSOR_TEMP_GetValue(&temp_value);

    (void)memcpy((void *)&Msg->Data[MsgIndex], (void *)&temp_value, sizeof(float_t));
    MsgIndex += (uint8_t)sizeof(float_t);
  }
}

/**
  * @brief  Handles the HUM axes data getting/sending
  * @param  Msg the HUM part of the stream
  * @retval None
  */
static void Humidity_Sensor_Handler(TMsg_t *Msg)
{
  uint8_t status = 0U;
  float_t hum_value = 0.0f;

  BSP_SENSOR_HUM_Get_DRDY_Status(&status);

  if (status == 1U)
  {
    NewData++;
    NewDataFlags |= 4U;

    BSP_SENSOR_HUM_GetValue(&hum_value);

    (void)memcpy((void *)&Msg->Data[MsgIndex], (void *)&hum_value, sizeof(float_t));;
    MsgIndex += (uint8_t)sizeof(float_t);
  }
}

/**
  * @brief  Handles the ACC axes data getting/sending
  * @param  Msg the ACC part of the stream
  * @retval None
  */
static void Accelero_Sensor_Handler(TMsg_t *Msg)
{
  uint8_t status = 0U;
  ISPU_MOTION_SENSOR_Axes_t acc_value;

  BSP_SENSOR_ACC_Get_DRDY_Status(&status);

  if (status == 1U)
  {
    NewData++;
    NewDataFlags |= 8U;

    BSP_SENSOR_ACC_GetAxes(&acc_value);

    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 0U)], (int32_t)acc_value.x, sizeof(int32_t));
    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 1U)], (int32_t)acc_value.y, sizeof(int32_t));
    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 2U)], (int32_t)acc_value.z, sizeof(int32_t));
    MsgIndex += (uint8_t)(sizeof(int32_t) * 3U);
  }
}

/**
  * @brief  Handles the GYR axes data getting/sending
  * @param  Msg the GYR part of the stream
  * @retval None
  */
static void Gyro_Sensor_Handler(TMsg_t *Msg)
{
  uint8_t status = 0U;
  ISPU_MOTION_SENSOR_Axes_t gyr_value;

  BSP_SENSOR_GYR_Get_DRDY_Status(&status);

  if (status == 1U)
  {
    NewData++;
    NewDataFlags |= 16U;

    BSP_SENSOR_GYR_GetAxes(&gyr_value);

    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 0U)], (int32_t)gyr_value.x, sizeof(int32_t));
    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 1U)], (int32_t)gyr_value.y, sizeof(int32_t));
    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 2U)], (int32_t)gyr_value.z, sizeof(int32_t));
    MsgIndex += (uint8_t)(sizeof(int32_t) * 3U);
  }
}

/**
  * @brief  Handles the MAG axes data getting/sending
  * @param  Msg the MAG part of the stream
  * @retval None
  */
static void Magneto_Sensor_Handler(TMsg_t *Msg)
{
  uint8_t status = 0U;
  ISPU_MOTION_SENSOR_Axes_t mag_value;

  BSP_SENSOR_MAG_Get_DRDY_Status(&status);

  if (status == 1U)
  {
    NewData++;
    NewDataFlags |= 32U;

    BSP_SENSOR_MAG_GetAxes(&mag_value);

    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 0U)], (int32_t)mag_value.x, sizeof(int32_t));
    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 1U)], (int32_t)mag_value.y, sizeof(int32_t));
    Serialize_s32(&Msg->Data[MsgIndex + (sizeof(int32_t) * 2U)], (int32_t)mag_value.z, sizeof(int32_t));
    MsgIndex += (uint8_t)(sizeof(int32_t) * 3U);
  }
}

/**
  * @brief  Handles the ISPU data
  * @param  Msg the ISPU part of the stream
  * @retval None
  */
static void ISPU_Handler(TMsg_t *Msg)
{
  uint8_t i;
  uint8_t new_status = 0;
  uint8_t int_status = 0;
  uint8_t ispu_status[64];
  static uint8_t mem_ispu_status[64];

  /* Enable routing ISPU sleep state to INT2 pin */
  BSP_SENSOR_ACC_Write_Register(ISM330IS_INT2_CTRL, 0x80);

  BSP_SENSOR_ACC_Read_Register(ISM330IS_ISPU_INT_STATUS0_MAINPAGE, &int_status);

  if (int_status != 0U)
  {
    BSP_SENSOR_ACC_Write_Register(ISM330IS_FUNC_CFG_ACCESS, 0x80);

    for (i = 0; i < IspuBytes; i++)
    {
      BSP_SENSOR_ACC_Read_Register(ISM330IS_ISPU_DOUT_00_L + i, &ispu_status[i]);
    }

    BSP_SENSOR_ACC_Write_Register(ISM330IS_FUNC_CFG_ACCESS, 0x00);
  }

  if (int_status != 0U)
  {
    for (i = 0U; i < IspuBytes; i++)
    {
      if (ispu_status[i] != mem_ispu_status[i])
      {
        new_status = 1;
        break;
      }
    }
  }

  if (new_status == 1U)
  {
    (void)memcpy((void *)&Msg->Data[MsgIndex], (void *)ispu_status, IspuBytes);
    (void)memcpy((void *)mem_ispu_status, (void *)ispu_status, IspuBytes);
    MsgIndex += IspuBytes;

    /* Add ISPU algorithm execution time in [us] to the stream */
    (void)memcpy((void *)&Msg->Data[MsgIndex], (void *)&IspuElapsedTimeUs, sizeof(IspuElapsedTimeUs));
    MsgIndex += (uint8_t)sizeof(IspuElapsedTimeUs);

    NewData++;
    NewDataFlags |= 512U;
  }
}

/**
  * @brief  Initialize DWT register for counting clock cycles purpose
  * @param  None
  * @retval None
  */
static void DWT_Init(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; /* Disable counter */
}

#ifdef __cplusplus
}
#endif
