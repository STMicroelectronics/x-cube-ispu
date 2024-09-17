/**
  ******************************************************************************
  * @file    lsm6dso16is_settings.h
  * @author  MEMS Application Team
  * @brief   This file contains definitions for the LSM6DSO16IS settings
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
#ifndef LSM6DSO16IS_SETTINGS_H
#define LSM6DSO16IS_SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#define LSM6DSO16IS_ACC_ODR 104.0f /* ODR = 104Hz */

#define LSM6DSO16IS_ACC_FS 4 /* FS = 4g */

#define LSM6DSO16IS_GYRO_ODR 104.0f /* ODR = 104Hz */

#define LSM6DSO16IS_GYRO_FS 2000 /* FS = 2000dps */

#ifdef __cplusplus
}
#endif

#endif /* LSM6DSO16IS_SETTINGS_H*/
