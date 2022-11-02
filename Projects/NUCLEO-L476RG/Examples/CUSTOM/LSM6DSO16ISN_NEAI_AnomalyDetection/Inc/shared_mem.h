/**
  ******************************************************************************
  * @file    shared_mem.h
  * @author  MEMS Application Team
  * @brief   This file contains definitions for the NEAI ISPU examples
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

#ifndef __SHARED_MEM_H__
#define __SHARED_MEM_H__

enum ispu_cmd
{
  NOP = 0,
  RESERVED_0,
  RESERVED_1,
  SET_TRIGGER_PERCENTAGE,
  FETCH_DATA,
  RESERVED_4,
  RESERVED_5,
  RESERVED_6,
  SET_MODE,
};

enum ispu_mode
{
  MODE_IDLE = 0,
  MODE_SAMPLING,
  MODE_LEARNING,
  MODE_DETECT,
  MODE_DETECT_CONSECUTIVE,
  MODE_MAX,
};

#define HOST_TO_ISPU_SIZE   8
#define ISPU_TO_HOST_SIZE  64

struct ispu_exchange
{
  uint8_t ispu_status;
  uint8_t neai_status;
  int16_t acc_x;
  int16_t acc_y;
  int16_t acc_z;
} __attribute__((packed));

#define ispu_x ((volatile struct ispu_exchange *) ISPU_TO_HOST)

#define ISPU_DBG_OVERFLOW  (1 << 15)

#define ISPU_BUF_OFFSET (sizeof (struct ispu_exchange))
#define ISPU_BUF_SIZE  (ISPU_TO_HOST_SIZE - ISPU_BUF_OFFSET)

#ifdef TARGET_ISPU
#define HOST_TO_ISPU  (__ctrl_reg_ext  + 0x74)
#define ISPU_TO_HOST  (__ctrl_reg_base + 0x10)
#else
#define HOST_TO_ISPU  (0x73)
#define ISPU_TO_HOST  (0x10)
#endif

#define ISPU_CTRL (HOST_TO_ISPU + 0x00)
#define ISPU_CTRL_1 (HOST_TO_ISPU + 0x00)
#define ISPU_CTRL_2 (HOST_TO_ISPU + 0x01)

#define ISPU_ARG(n) (HOST_TO_ISPU + 0x02 + (n * sizeof (uint16_t)))

#endif /* __SHARED_MEM_H__ */
