/**
  ******************************************************************************
  * @file    int_pins_interface.c
  * @author  MEMS Software Solutions Team
  * @brief   This file contains the INT pins interface
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
#include "main.h"

/* Exported variables --------------------------------------------------------*/
uint8_t INT1Detected = 0U;
uint8_t INT2Detected = 0U;
EXTI_HandleTypeDef hexti0 = {.Line = EXTI_LINE_0};
EXTI_HandleTypeDef hexti15 = {.Line = EXTI_LINE_15};

/* Private function prototypes -----------------------------------------------*/
static void Int1_Pin_Isr(void);
static void Int2_Pin_Isr(void);

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Set INT pins EXTI
  * @param  None
  * @retval None
  */
void Set_Int_Pins_Exti(void)
{
  /* Register event IRQ handler */
  (void)HAL_EXTI_GetHandle(&hexti0, EXTI_LINE_0);
  (void)HAL_EXTI_RegisterCallback(&hexti0, HAL_EXTI_COMMON_CB_ID, Int1_Pin_Isr);
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
  (void)HAL_EXTI_GetHandle(&hexti15, EXTI_LINE_15);
  (void)HAL_EXTI_RegisterCallback(&hexti15, HAL_EXTI_COMMON_CB_ID, Int2_Pin_Isr);
  HAL_NVIC_SetPriority(EXTI15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_IRQn);
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  INT1 pin interrupt service routine
  * @param  None
  * @retval None
  */
static void Int1_Pin_Isr(void)
{
  INT1Detected = 1;
}

/**
  * @brief  INT2 pin interrupt service routine
  * @param  None
  * @retval None
  */
static void Int2_Pin_Isr(void)
{
  INT2Detected = 1;
}
