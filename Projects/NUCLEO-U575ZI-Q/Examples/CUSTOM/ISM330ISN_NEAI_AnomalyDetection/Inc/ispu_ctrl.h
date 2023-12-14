/**
  ******************************************************************************
  * @file    ispu_ctrl.h
  * @author  MEMS Application Team
  * @brief   This file contains definitions for the NEAI ISPU examples
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

#ifndef __ISPU_CTL_H__
#define __ISPU_CTL_H__

#include "shared_mem.h"

#define SAMPLES 104
#define AXES 3

void ispu_write(uint8_t reg, uint8_t val);
void ispu_read(uint8_t reg, uint8_t *val, uint16_t len);
void initialize_ctrl_interface(void);

enum ispu_comm
{
  ISPU_COMM_OK,
  ISPU_COMM_BUSY
};

enum neai_state
{
  NEAI_OK = 0,
  NEAI_BOARD_ERROR = 124,
  DISCARD,
  NEAI_NOT_ENOUGH_CALL_TO_LEARNING,
  NEAI_UNKNOWN_ERROR
};

static inline void ispu_enable_cfg_access(void)
{
  ispu_write(0x01, 0x80);
}

static inline void ispu_disable_cfg_access(void)
{
  ispu_write(0x01, 0x00);
}

// https://stackoverflow.com/a/35693080
#define PP_NARG(...)        \
  PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...)       \
  PP_5_ARG(__VA_ARGS__)
#define PP_5_ARG(dummy, _1, _2, _3, N, ...) N
#define PP_RSEQ_N()       \
  3, 2, 1, 0

enum ispu_comm _ispu_send_cmd(size_t argc, enum ispu_cmd cmd, ...);
#define ispu_send_cmd(...) _ispu_send_cmd(PP_NARG(__VA_ARGS__), __VA_ARGS__)

void process_answer(void);
void get_accelerometer_samples(int16_t *acc_x, int16_t *acc_y, int16_t *acc_z);
enum neai_state get_neai_status(void);

#endif /* __ISPU_CTL_H__ */
