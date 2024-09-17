/**
  ******************************************************************************
  * @file    demo_serial.c
  * @author  MEMS Software Solutions Team
  * @brief   Handle the Serial Protocol
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
#include <stdint.h>
#include <stdio.h> /* MISRAC2012-Rule-21.6 violation for purpose, the associated issues are understood */
#include "bsp_ip_conf.h"
#include "com.h"
#include "demo_serial.h"
#include "fw_version.h"
#include "sensor_commands.h"
#include "serial_cmd.h"
#include "custom_mems_control.h"
#include "custom_mems_control_ex.h"
#include "custom_ispu_mems_conf_app.h"

/** @addtogroup ISPU_APPLICATIONS ISPU APPLICATIONS
  * @{
  */

/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint8_t DataStreamingDest = 1;

/* Private function prototypes -----------------------------------------------*/
static void RTC_DateRegulate(uint8_t y, uint8_t m, uint8_t d, uint8_t dw);
static void RTC_TimeRegulate(uint8_t hh, uint8_t mm, uint8_t ss);
static void Get_PresentationString(uint8_t *PresentationString, uint32_t *Length);

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Build the reply header
  * @param  Msg the pointer to the message to be built
  * @retval None
  */
void BUILD_REPLY_HEADER(TMsg_t *Msg)
{
  Msg->Data[0] = Msg->Data[1];
  Msg->Data[1] = DEV_ADDR;
  Msg->Data[2] += CMD_REPLY_ADD;
}

/**
  * @brief  Initialize the streaming header
  * @param  Msg the pointer to the header to be initialized
  * @retval None
  */
void INIT_STREAMING_HEADER(TMsg_t *Msg)
{
  Msg->Data[0] = DataStreamingDest;
  Msg->Data[1] = DEV_ADDR;
  Msg->Data[2] = CMD_START_DATA_STREAMING;
  Msg->Len = 3;
}

/**
  * @brief  Initialize the streaming message
  * @param  Msg the pointer to the message to be initialized
  * @retval None
  */
void INIT_STREAMING_MSG(TMsg_t *Msg)
{
  uint32_t i;

  Msg->Data[0] = DataStreamingDest;
  Msg->Data[1] = DEV_ADDR;
  Msg->Data[2] = CMD_START_DATA_STREAMING;
  for (i = 3U; i < (STREAMING_MSG_LENGTH + 3U); i++)
  {
    Msg->Data[i] = 0;
  }

  Msg->Len = 3;
}

/**
  * @brief  Handle a message
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
int32_t HandleMSG(TMsg_t *Msg)
/*  DestAddr | SouceAddr | CMD | PAYLOAD
 *      1          1        1       N
 */
{
  int32_t ret = 1;
  uint32_t i;
  uint8_t ps[64];
  uint32_t ps_len = 0;

  if ((Msg->Len >= 2U) && (Msg->Data[0] == DEV_ADDR))
  {
    switch (Msg->Data[2])   /* CMD */
    {
      case CMD_PING:
        if (Msg->Len != 3U)
        {
          ret = 0;
          break;
        }

        BUILD_REPLY_HEADER(Msg);
        Msg->Len = 3;
        UART_SendMsg(Msg);
        break;

      case CMD_ENTER_DFU_MODE:
        if (Msg->Len != 3U)
        {
          ret = 0;
          break;
        }

        BUILD_REPLY_HEADER(Msg);
        Msg->Len = 3;
        break;

      case CMD_READ_PRES_STRING:
        if (Msg->Len != 3U)
        {
          ret = 0;
          break;
        }

        BUILD_REPLY_HEADER(Msg);

        Get_PresentationString(ps, &ps_len);

        i = 0;
        while (i < ps_len)
        {
          Msg->Data[3U + i] = ps[i];
          i++;
        }

        Msg->Len = 3U + i;
        UART_SendMsg(Msg);
        break;

      case CMD_CHECK_MODE_SUPPORT:
        if (Msg->Len < 3U)
        {
          ret = 0;
          break;
        }

        BUILD_REPLY_HEADER(Msg);
        Serialize_s32(&Msg->Data[3], DATALOG_EXT_MODE, 4);
        Msg->Len = 3 + 4;
        UART_SendMsg(Msg);
        break;

      case CMD_SENSOR:
        if (Msg->Len < 5U)
        {
          ret = 0;
          break;
        }

        (void)Handle_Sensor_Command(Msg);
        break;

      case CMD_START_DATA_STREAMING:
        if (Msg->Len < 3U)
        {
          ret = 0;
          break;
        }

        SensorsEnabled = Deserialize(&Msg->Data[3], 4);
        DataLoggerActive = 1;
        UpdateInterrupt = 1;
        DataStreamingDest = Msg->Data[1];

        DWT_Start();

        BUILD_REPLY_HEADER(Msg);
        Msg->Len = 3;
        UART_SendMsg(Msg);
        break;

      case CMD_STOP_DATA_STREAMING:
        if (Msg->Len < 3U)
        {
          ret = 0;
          break;
        }

        SensorsEnabled = 0;
        DataLoggerActive = 0;

        (void)DWT_Stop();

        BUILD_REPLY_HEADER(Msg);
        UART_SendMsg(Msg);
        break;

      case CMD_ENABLE_DISABLE_SENSOR:
        if (Msg->Len < 4U)
        {
          ret = 0;
          break;
        }

        SensorsEnabled = Deserialize(&Msg->Data[3], 4);

        BUILD_REPLY_HEADER(Msg);
        Msg->Len = 4;
        UART_SendMsg(Msg);
        break;

      case CMD_SET_DATE_TIME:
        if (Msg->Len < 3U)
        {
          ret = 0;
          break;
        }

        BUILD_REPLY_HEADER(Msg);
        Msg->Len = 3;
        RTC_TimeRegulate(Msg->Data[3], Msg->Data[4], Msg->Data[5]);
        RTC_DateRegulate(Msg->Data[6], Msg->Data[7], Msg->Data[8], Msg->Data[9]);
        UART_SendMsg(Msg);
        break;

      case CMD_SET_ISPU_DATA_LENGTH:
        if (Msg->Len != 4U)
        {
          ret = 0;
          break;
        }

        IspuBytes = Msg->Data[3];

        BUILD_REPLY_HEADER(Msg);
        Msg->Len = 3;
        UART_SendMsg(Msg);
        break;

      default:
        ret = 0;
        break;
    }
  }
  else
  {
    ret = 0;
  }

  return ret;
}

/* Private functions -------------------------------------------------------- */
/**
  * @brief  Configures the current date
  * @param  y the year value to be set
  * @param  m the month value to be set
  * @param  d the day value to be set
  * @param  dw the day-week value to be set
  * @retval None
  */
static void RTC_DateRegulate(uint8_t y, uint8_t m, uint8_t d, uint8_t dw)
{
  RTC_DateTypeDef sdatestructure;

  sdatestructure.Year    = y;
  sdatestructure.Month   = m;
  sdatestructure.Date    = d;
  sdatestructure.WeekDay = dw;

  if (HAL_RTC_SetDate(&hrtc, &sdatestructure, FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Configures the current time
  * @param  hh the hour value to be set
  * @param  mm the minute value to be set
  * @param  ss the second value to be set
  * @retval None
  */
static void RTC_TimeRegulate(uint8_t hh, uint8_t mm, uint8_t ss)
{
  RTC_TimeTypeDef stimestructure;

  stimestructure.Hours          = hh;
  stimestructure.Minutes        = mm;
  stimestructure.Seconds        = ss;
  stimestructure.SubSeconds     = 0;
  stimestructure.TimeFormat     = RTC_HOURFORMAT12_AM;
  stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;

  if (HAL_RTC_SetTime(&hrtc, &stimestructure, FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Gets Presentation string
  * @param  PresentationString the Presentation string
  * @param  Length the length of Presentation string
  * @retval None
  */
static void Get_PresentationString(uint8_t *PresentationString, uint32_t *Length)
{
  const uint8_t lib_version_string[] = {"0.0.0"};
  const char ps[] = {"MEMS shield demo,103,"FW_VERSION",%s,"BOARD_NAME};

  /* MISRAC2012-Dir-4.6_a violation in order to use snprintf function without warning in STM32CubeIDE */
  *Length = (uint32_t)snprintf((char *)PresentationString, 64, ps, lib_version_string);
}

/**
  * @}
  */
