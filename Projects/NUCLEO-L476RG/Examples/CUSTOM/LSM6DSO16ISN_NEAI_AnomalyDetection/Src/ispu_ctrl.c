/**
  ******************************************************************************
  * @file    ispu_ctrl.c
  * @author  MEMS Application Team
  * @brief   This file contains code for the NEAI ISPU examples
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

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#include "ispu_ctrl.h"

static int toggle = 0;
static enum ispu_cmd current_cmd = NOP;

void initialize_ctrl_interface(void)
{
  ispu_write(ISPU_CTRL_1, NOP);
  ispu_write(ISPU_CTRL_2, NOP);
}

void acknowledge_cmd_done(void)
{
  ispu_write(toggle ? ISPU_CTRL_2 : ISPU_CTRL_1, NOP);
  current_cmd = NOP;

  toggle = 1 - toggle;
}

enum ispu_comm _ispu_send_cmd(size_t argc, enum ispu_cmd cmd, ...)
{
  if (current_cmd != NOP)
  {
    return ISPU_COMM_BUSY;
  }
  va_list ap;
  int i;

  va_start(ap, cmd);
  for (i = 0; i < argc; i++)
  {
    uint16_t arg;
    arg = va_arg(ap, int);
    ispu_write(ISPU_ARG(i), arg);
  }
  va_end(ap);
  ispu_write(toggle ? ISPU_CTRL_2 : ISPU_CTRL_1, cmd);
  current_cmd = cmd;
  return ISPU_COMM_OK;
}

extern enum ispu_mode ispu_mode;
extern int anomaly_detected;
extern int fetch_in_progress;
extern int learn_count;
extern int ad_nr;

void set_ispu_mode(enum ispu_mode mode)
{
  ispu_mode = mode;
}

void inspect_buffer(float *buf)
{
  int i;

  for (i = 0; i < SAMPLES * AXES; i++)
  {
    printf(" %10.2f", buf[i]);
    if (!((i + 1) % AXES))
    {
      printf("\n");
    }
  }
}

void process_answer(void)
{
  uint8_t status;

  int nr;
  static float ad_buf[SAMPLES * AXES];

  ispu_enable_cfg_access();

  ispu_read(ISPU_TO_HOST, &status, 1);

  switch (current_cmd)
  {
    case FETCH_DATA:
      fetch_in_progress = 0;
      nr = status;
      if (nr == 0)
      {
        inspect_buffer(ad_buf);
        anomaly_detected = 0;
        ad_nr = 0;
        break;
      }
      ispu_read(ISPU_TO_HOST + ISPU_BUF_OFFSET, (uint8_t *) ad_buf + ad_nr, nr);
      ad_nr += nr;
      break;
    case SET_MODE:
      set_ispu_mode((enum ispu_mode) status);
      break;
    default:
      break;
  }

  ispu_disable_cfg_access();
  acknowledge_cmd_done();
}

void get_accelerometer_samples(int16_t *acc_x, int16_t *acc_y, int16_t *acc_z)
{
  ispu_enable_cfg_access();
  ispu_read(ISPU_TO_HOST + 2, (uint8_t *) acc_x, 2);
  ispu_read(ISPU_TO_HOST + 4, (uint8_t *) acc_y, 2);
  ispu_read(ISPU_TO_HOST + 6, (uint8_t *) acc_z, 2);
  ispu_disable_cfg_access();
}

enum neai_state get_neai_status()
{
  enum neai_state state;
  ispu_enable_cfg_access();
  ispu_read(ISPU_TO_HOST + 1, (uint8_t *) &state, 1);
  ispu_disable_cfg_access();
  return state;
}
