/**
  ******************************************************************************
  * @file    user_int_interface.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains definitions for the USER_INT pin interface
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
#ifndef USER_INT_INTERFACE_H
#define USER_INT_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_exti.h"

/* Exported variables --------------------------------------------------------*/
extern uint32_t IspuElapsedTimeUs;
extern EXTI_HandleTypeDef hexti10;

#define H_EXTI_10 hexti10

/* Exported Functions --------------------------------------------------------*/
void Set_User_Int_Exti(void);

#ifdef __cplusplus
}
#endif

#endif /* USER_INT_INTERFACE_H*/
