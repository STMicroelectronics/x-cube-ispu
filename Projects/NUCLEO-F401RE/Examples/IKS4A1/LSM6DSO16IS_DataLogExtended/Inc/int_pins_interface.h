/**
  ******************************************************************************
  * @file    int_pins_interface.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains definitions for the INT pins interface
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
#ifndef INT_PINS_INTERFACE_H
#define INT_PINS_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_exti.h"

/* Exported variables --------------------------------------------------------*/
extern uint32_t IspuElapsedTimeUs;
extern EXTI_HandleTypeDef hexti8;

#define H_EXTI_8 hexti8

/* Exported Functions --------------------------------------------------------*/
void Set_Int_Pins_Exti(void);

#ifdef __cplusplus
}
#endif

#endif /* INT_PINS_INTERFACE_H*/
