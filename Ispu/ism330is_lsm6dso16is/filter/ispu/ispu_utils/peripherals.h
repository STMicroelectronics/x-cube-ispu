/**
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

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

#include <stdint.h>

#define cast_uint32_t(add) (*((volatile uint32_t *)(add))) /* to read/write an unsigned 32 bit integer */
#define cast_uint16_t(add) (*((volatile uint16_t *)(add))) /* to read/write an unsigned 16 bit integer */
#define cast_uint8_t(add)  (*((volatile uint8_t *)(add)))  /* to read/write an unsigned  8 bit integer */

#define cast_sint32_t(add) (*((volatile int32_t *)(add)))  /* to read/write a signed 32 bit integer */
#define cast_sint16_t(add) (*((volatile int16_t *)(add)))  /* to read/write a signed 16 bit integer */
#define cast_sint8_t(add)  (*((volatile int8_t *)(add)))   /* to read/write a signed  8 bit integer */

#define cast_float(add)    (*((volatile float *)(add)))    /* to read/write a float 32 bit value */

#define stop_and_wait_start_pulse do { STOP_CLOCK; asm(""); } while (0)

extern volatile uint8_t STOP_CLOCK;

#endif

