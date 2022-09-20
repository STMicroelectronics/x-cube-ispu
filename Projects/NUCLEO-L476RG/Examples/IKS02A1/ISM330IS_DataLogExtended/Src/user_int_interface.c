/**
  ******************************************************************************
  * @file    user_int_interface.c
  * @author  MEMS Software Solutions Team
  * @brief   This file contains the USER_INT pin interface
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

/* Includes ------------------------------------------------------------------*/
#include "demo_serial.h"
#include "main.h"

/* Exported variables --------------------------------------------------------*/
uint32_t IspuElapsedTimeUs = 0U;
EXTI_HandleTypeDef hexti10 = {.Line = EXTI_LINE_10};

/* Private function prototypes -----------------------------------------------*/
static void User_Int_Isr(void);

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Set USER_INT EXTI
  * @param  None
  * @retval None
  */
void Set_User_Int_Exti(void)
{
  /* Register event IRQ handler */
  (void)HAL_EXTI_GetHandle(&hexti10, EXTI_LINE_10);
  (void)HAL_EXTI_RegisterCallback(&hexti10, HAL_EXTI_COMMON_CB_ID, User_Int_Isr);
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  USER_INT interrupt service routine
  * @param  None
  * @retval None
  */
static void User_Int_Isr(void)
{
  GPIO_PinState pin_state;
  static uint32_t reset_state_tick_us = 0U;
  static uint32_t set_state_tick_us = 0U;

  pin_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);

  if (pin_state == GPIO_PIN_RESET)
  {
    reset_state_tick_us = DWT_GetTick();
  }
  else
  {
    set_state_tick_us = DWT_GetTick();
  }

  if ((reset_state_tick_us != 0U) && (set_state_tick_us != 0U) && (set_state_tick_us > reset_state_tick_us))
  {
    IspuElapsedTimeUs = set_state_tick_us - reset_state_tick_us;
  }
}
