/**
  ******************************************************************************
  * @file    bsp_ip_conf.h
  * @author  MEMS Software Solutions Team
  * @brief   BSP IP configuration file
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
#ifndef BSP_IP_CONF_H
#define BSP_IP_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported defines ----------------------------------------------------------*/
#define BOARD_NAME "IKS4A1"

/* Exported variables --------------------------------------------------------*/
/* Exported defines ----------------------------------------------------------*/

extern RTC_HandleTypeDef hrtc;

#ifdef __cplusplus
}
#endif

#endif /* BSP_IP_CONF_H */
