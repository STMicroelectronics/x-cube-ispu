/**
  *******************************************************************************
  * @file    serial_cmd.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains serial commands code
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
#ifndef SERIAL_CMD_H
#define SERIAL_CMD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported constants --------------------------------------------------------*/
#define DATALOG_EXT_MODE           101

/* GENERIC  CMD  (0x00 - 0x0F) -------*/
#define CMD_PING                   0x01U
#define CMD_READ_PRES_STRING       0x02U
#define CMD_NACK                   0x03U
#define CMD_CHECK_MODE_SUPPORT     0x04U
#define CMD_UPLOAD_AR              0x05U
#define CMD_UPLOAD_CP              0x06U
#define CMD_START_DATA_STREAMING   0x08U
#define CMD_STOP_DATA_STREAMING    0x09U
#define CMD_START_DEMO             0x0AU
#define CMD_SLEEP_SEC              0x0BU
#define CMD_SET_DATE_TIME          0x0CU
#define CMD_GET_DATE_TIME          0x0DU
#define CMD_ENTER_DFU_MODE         0x0EU
#define CMD_RESET                  0x0FU
#define CMD_ENABLE_DISABLE_SENSOR  0x10U
#define CMD_SET_ISPU_DATA_LENGTH   0x11U
#define CMD_SENSOR                 0x50U
#define CMD_REPLY_ADD              0x80U

#ifdef __cplusplus
}
#endif

#endif /* SERIAL_CMD_H */
