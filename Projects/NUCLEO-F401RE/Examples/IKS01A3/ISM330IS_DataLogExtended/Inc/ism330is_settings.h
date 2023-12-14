/**
  ******************************************************************************
  * @file    ism330is_settings.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains definitions for the ISM330IS settings
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ISM330IS_SETTINGS_H
#define ISM330IS_SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#define ISM330IS_ACC_ODR 104.0f /* ODR = 104Hz */

#define ISM330IS_ACC_FS 4 /* FS = 4g */

#define ISM330IS_GYRO_ODR 104.0f /* ODR = 104Hz */

#define ISM330IS_GYRO_FS 2000 /* FS = 2000dps */

#ifdef __cplusplus
}
#endif

#endif /* ISM330IS_SETTINGS_H*/
