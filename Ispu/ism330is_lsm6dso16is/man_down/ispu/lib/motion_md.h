/**
  *******************************************************************************
  * @file    motion_md.h
  * @author  MEMS Application Team
  * @version V1.0.0
  * @brief   Header for motion_md module
  *******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *******************************************************************************
  */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef _MOTION_MD_H_
#define _MOTION_MD_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>

/** @addtogroup MIDDLEWARES
 *  @{
 */

/** @defgroup MOTION_MD MOTION_MD
 *  @{
 */

/* Exported types ----------------------------------------------------------- */
typedef struct
{
  float acc[3];  /* Accelerometer sensor output [g] */
  float prs;     /* Pressure sensor output [hPa] */
} MMD_input_t;

typedef struct
{
  float alt;             /* Threshold on altitude difference [m] */
  float shock;           /* Threshold on shock measured by accelerometer [g] */
  float shock_time;      /* Threshold on shock duration [s] */
  float alt_var_steady;  /* Altitude variance threshold [m^2] */
  float acc_var_steady;  /* Accelerometer variance threshold [g^2] */
  float steady_time;     /* Threshold on steady duration [s] */
} MMD_conf_t;

typedef enum
{
  MMD_NONE,
  MMD_MANDOWN
} MMD_output_t;

/**
 *  @}
 */

/* Exported constants ------------------------------------------------------- */
/* Exported variables ------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */

/** @defgroup MOTION_MD_Exported_Functions MOTION_MD_Exported_Functions
 *  @{
 */

/* Exported functions ------------------------------------------------------- */

/**
 * @brief  Initialize the MotionMD engine
 * @retval none
 */
void MotionMD_initialize(void);

/**
 * @brief  Get the algorithm configuration.
 * @param  conf pointer to the structure where the current configuration will be written to
 * @retval none
 */
void MotionMD_get_configuration(MMD_conf_t *conf);

/**
 * @brief  Set the algorithm configuration.
 * @param  conf pointer to the structure containing the configuration to be set
 * @retval none
 */
void MotionMD_set_configuration(MMD_conf_t *conf);

/**
 * @brief  Run mandown algorithm.
 * @param  data_in pointer to the structure containing the input data
 * @param  data_out pointer to the enum containing the output data
 * @retval none
 */
void MotionMD_update(MMD_output_t *data_out, MMD_input_t *data_in);

/**
  * @brief  Get the library version
  * @param  version pointer to an array of 35 char
  * @retval number of characters in the version string
  */
uint8_t MotionMD_get_lib_version(char *version);

/**
 *  @}
 */

/**
 *  @}
 */

/**
 *  @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _MOTION_MD_H_ */

