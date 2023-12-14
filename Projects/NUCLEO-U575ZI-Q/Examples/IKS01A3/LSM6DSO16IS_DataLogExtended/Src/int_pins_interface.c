/**
  ******************************************************************************
  * @file    int_pins_interface.c
  * @author  MEMS Software Solutions Team
  * @brief   This file contains the INT pins interface
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

/* Includes ------------------------------------------------------------------*/
#include "demo_serial.h"
#include "main.h"

/* Exported variables --------------------------------------------------------*/
uint32_t IspuElapsedTimeUs = 0U;
EXTI_HandleTypeDef hexti15 = {.Line = EXTI_LINE_15};

/* Private function prototypes -----------------------------------------------*/
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
  (void)HAL_EXTI_GetHandle(&hexti15, EXTI_LINE_15);
  (void)HAL_EXTI_RegisterCallback(&hexti15, HAL_EXTI_COMMON_CB_ID, Int2_Pin_Isr);
  HAL_NVIC_SetPriority(EXTI15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_IRQn);
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  INT2 pin interrupt service routine
  * @param  None
  * @retval None
  */
static void Int2_Pin_Isr(void)
{
  GPIO_PinState pin_state;
  static uint32_t reset_state_tick_us = 0U;
  static uint32_t set_state_tick_us = 0U;

  pin_state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_15);

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
