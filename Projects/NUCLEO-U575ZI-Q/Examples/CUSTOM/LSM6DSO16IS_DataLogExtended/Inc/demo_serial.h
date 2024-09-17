/**
  *******************************************************************************
  * @file    demo_serial.h
  * @author  MEMS Software Solutions Team
  * @brief   Header for demo_serial.c
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
#ifndef DEMO_SERIAL_H
#define DEMO_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h" /* Needed for __IO definition */
#include "serial_protocol.h"

/* Exported types ------------------------------------------------------------*/
/* Exported defines ----------------------------------------------------------*/
#define SENDER_UART  0x01
#define SENDER_USB   0x02
#define SENDER_SPI   0x03

#define DEV_ADDR                   50U
#define I2C_DATA_MAX_LENGTH_BYTES  16
#define STREAMING_MSG_LENGTH       150U

/* Enable sensor masks */
#define PRESSURE_SENSOR_ENABLED       0x00000001U
#define TEMPERATURE_SENSOR_ENABLED    0x00000002U
#define HUMIDITY_SENSOR_ENABLED       0x00000004U
#define UV_SENSOR_ENABLED             0x00000008U /* for future use */
#define ACCELEROMETER_SENSOR_ENABLED  0x00000010U
#define GYROSCOPE_SENSOR_ENABLED      0x00000020U
#define MAGNETIC_SENSOR_ENABLED       0x00000040U
#define INTERRUPTS_ENABLED            0x00000100U
#define FSM_ENABLED                   0x00000200U
#define MLC_ENABLED                   0x00000400U
#define ISPU_ENABLED                  0x00000800U

#define MIN(A,B) ((A)<(B)?(A):(B))

/* Exported variables --------------------------------------------------------*/
extern __IO uint8_t DataLoggerActive;
extern __IO uint32_t SensorsEnabled;
extern __IO uint32_t StartTime;
extern __IO uint8_t UpdateInterrupt;
extern __IO uint8_t IspuBytes;

/* Exported functions ------------------------------------------------------- */
void BUILD_REPLY_HEADER(TMsg_t *Msg);
void INIT_STREAMING_HEADER(TMsg_t *Msg);
void INIT_STREAMING_MSG(TMsg_t *Msg);
int32_t HandleMSG(TMsg_t *Msg);

void DWT_Start(void);
uint32_t DWT_Stop(void);
uint32_t DWT_GetTick(void);

#ifdef __cplusplus
}
#endif

#endif /* DEMO_SERIAL_H */
