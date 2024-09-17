/**
  ******************************************************************************
  * @file    custom_ispu_motion_sensors.c
  * @author  MEMS Software Solutions Team
  * @brief   This file provides BSP Motion Sensors interface for custom boards
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
#include "custom_ispu_motion_sensors.h"

/* This "redundant" line is here to fulfil MISRA C-2012 rule 8.4 */
extern void *IspuMotionCompObj[CUSTOM_ISPU_MOTION_INSTANCES_NBR];
void *IspuMotionCompObj[CUSTOM_ISPU_MOTION_INSTANCES_NBR];

/* We define a jump table in order to get the correct index from the desired function. */
/* This table should have a size equal to the maximum value of a function plus 1.      */
static uint32_t FunctionIndex[] = {0, 0, 1, 1, 2, 2, 2, 2};
static MOTION_SENSOR_FuncDrv_t *MotionFuncDrv[CUSTOM_ISPU_MOTION_INSTANCES_NBR][CUSTOM_MOTION_FUNCTIONS_NBR];
static MOTION_SENSOR_CommonDrv_t *MotionDrv[CUSTOM_ISPU_MOTION_INSTANCES_NBR];
static CUSTOM_ISPU_MOTION_SENSOR_Ctx_t MotionCtx[CUSTOM_ISPU_MOTION_INSTANCES_NBR];

#if (USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 == 1)
static int32_t ISM330IS_0_Probe(uint32_t Functions);
#endif /* USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 */

/* MISRAC2012-Rule-11.5 violations due to compatibility with external MEMS1 package */

/**
  * @brief  Initializes the motion sensors
  * @param  Instance Motion sensor instance
  * @param  Functions Motion sensor functions. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_Init(uint32_t Instance, uint32_t Functions)
{
  int32_t ret = BSP_ERROR_NONE;
  uint32_t function = MOTION_GYRO;
  uint32_t i;
  uint32_t component_functions = 0;
  CUSTOM_ISPU_MOTION_SENSOR_Capabilities_t cap;

  switch (Instance)
  {
#if (USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 == 1)
    case CUSTOM_ISM330IS_0:
      if (ISM330IS_0_Probe(Functions) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_NO_INIT;
        break;
      }
      if (MotionDrv[Instance]->GetCapabilities(IspuMotionCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_UNKNOWN_COMPONENT;
        break;
      }
      if (cap.Acc == 1U)
      {
        component_functions |= MOTION_ACCELERO;
      }
      if (cap.Gyro == 1U)
      {
        component_functions |= MOTION_GYRO;
      }
      if (cap.Magneto == 1U)
      {
        component_functions |= MOTION_MAGNETO;
      }
      break;
#endif /* USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 */

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  if (ret == BSP_ERROR_NONE)
  {
    for (i = 0; i < CUSTOM_MOTION_FUNCTIONS_NBR; i++)
    {
      if (((Functions & function) == function) && ((component_functions & function) == function))
      {
        if (MotionFuncDrv[Instance][FunctionIndex[function]]->Enable(IspuMotionCompObj[Instance]) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
          break;
        }
      }
      function = function << 1;
    }
  }

  return ret;
}

/**
  * @brief  Deinitialize Motion sensor
  * @param  Instance Motion sensor instance
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_DeInit(uint32_t Instance)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (MotionDrv[Instance]->DeInit(IspuMotionCompObj[Instance]) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get motion sensor instance capabilities
  * @param  Instance Motion sensor instance
  * @param  Capabilities pointer to motion sensor capabilities
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetCapabilities(uint32_t Instance,
                                                  CUSTOM_ISPU_MOTION_SENSOR_Capabilities_t *Capabilities)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (MotionDrv[Instance]->GetCapabilities(IspuMotionCompObj[Instance], Capabilities) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get WHOAMI value
  * @param  Instance Motion sensor instance
  * @param  Id WHOAMI value
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_ReadID(uint32_t Instance, uint8_t *Id)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (MotionDrv[Instance]->ReadID(IspuMotionCompObj[Instance], Id) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Enable Motion sensor
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_Enable(uint32_t Instance, uint32_t Function)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->Enable(IspuMotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
  * @brief  Disable Motion sensor
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_Disable(uint32_t Instance, uint32_t Function)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->Disable(IspuMotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
  * @brief  Get motion sensor axes data
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @param  Axes pointer to axes data structure
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetAxes(uint32_t Instance, uint32_t Function,
                                          CUSTOM_ISPU_MOTION_SENSOR_Axes_t *Axes)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetAxes(IspuMotionCompObj[Instance], Axes)
          != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
  * @brief  Get motion sensor axes raw data
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @param  Axes pointer to axes raw data structure
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetAxesRaw(uint32_t Instance, uint32_t Function,
                                             CUSTOM_ISPU_MOTION_SENSOR_AxesRaw_t *Axes)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetAxesRaw(IspuMotionCompObj[Instance], Axes)
          != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
  * @brief  Get motion sensor sensitivity
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @param  Sensitivity pointer to sensitivity read value
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetSensitivity(uint32_t Instance, uint32_t Function, float_t *Sensitivity)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetSensitivity(IspuMotionCompObj[Instance],
                                                                           Sensitivity) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
  * @brief  Get motion sensor Output Data Rate
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @param  Odr pointer to Output Data Rate read value
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetOutputDataRate(uint32_t Instance, uint32_t Function, float_t *Odr)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetOutputDataRate(IspuMotionCompObj[Instance], Odr)
          != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
  * @brief  Get motion sensor Full Scale
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @param  Fullscale pointer to Fullscale read value
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_GetFullScale(uint32_t Instance, uint32_t Function, int32_t *Fullscale)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->GetFullScale(IspuMotionCompObj[Instance], Fullscale)
          != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
  * @brief  Set motion sensor Output Data Rate
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @param  Odr Output Data Rate value to be set
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_SetOutputDataRate(uint32_t Instance, uint32_t Function, float_t Odr)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->SetOutputDataRate(IspuMotionCompObj[Instance], Odr)
          != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
  * @brief  Set motion sensor Full Scale
  * @param  Instance Motion sensor instance
  * @param  Function Motion sensor function. Could be :
  *         - MOTION_GYRO
  *         - MOTION_ACCELERO
  *         - MOTION_MAGNETO
  * @param  Fullscale Fullscale value to be set
  * @retval BSP status
  */
int32_t CUSTOM_ISPU_MOTION_SENSOR_SetFullScale(uint32_t Instance, uint32_t Function, int32_t Fullscale)
{
  int32_t ret;

  if (Instance >= CUSTOM_ISPU_MOTION_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((MotionCtx[Instance].Functions & Function) == Function)
    {
      if (MotionFuncDrv[Instance][FunctionIndex[Function]]->SetFullScale(IspuMotionCompObj[Instance], Fullscale)
          != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    else
    {
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

#if (USE_CUSTOM_MOTION_SENSOR_ISM330IS_0  == 1)
/**
  * @brief  Register Bus IOs for ISM330IS instance
  * @param  Functions Motion sensor functions. Could be :
  *         - MOTION_GYRO and/or MOTION_ACCELERO
  * @retval BSP status
  */
static int32_t ISM330IS_0_Probe(uint32_t Functions)
{
  ISM330IS_IO_t            io_ctx;
  uint8_t                  id;
  static ISM330IS_Object_t ism330is_obj_0;
  ISM330IS_Capabilities_t  cap;
  int32_t                  ret = BSP_ERROR_NONE;

  /* Configure the driver */
  io_ctx.BusType     = ISM330IS_I2C_BUS; /* I2C */
  io_ctx.Address     = ISM330IS_I2C_ADD_L; /* SA0 = GND */
  io_ctx.Init        = CUSTOM_ISM330IS_0_I2C_INIT;
  io_ctx.DeInit      = CUSTOM_ISM330IS_0_I2C_DEINIT;
  io_ctx.ReadReg     = CUSTOM_ISM330IS_0_I2C_READREG;
  io_ctx.WriteReg    = CUSTOM_ISM330IS_0_I2C_WRITEREG;
  io_ctx.GetTick     = BSP_GetTick;

  if (ISM330IS_RegisterBusIO(&ism330is_obj_0, &io_ctx) != ISM330IS_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (ISM330IS_Set_Mem_Bank(&ism330is_obj_0, ISM330IS_MAIN_MEM_BANK) != ISM330IS_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (ISM330IS_ReadID(&ism330is_obj_0, &id) != ISM330IS_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (id != ISM330IS_ID)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    (void)ISM330IS_GetCapabilities(&ism330is_obj_0, &cap);
    MotionCtx[CUSTOM_ISM330IS_0].Functions = ((uint32_t)cap.Gyro) | ((uint32_t)cap.Acc << 1)
                                             | ((uint32_t)cap.Magneto << 2);

    IspuMotionCompObj[CUSTOM_ISM330IS_0] = &ism330is_obj_0;
    MotionDrv[CUSTOM_ISM330IS_0] = (MOTION_SENSOR_CommonDrv_t *)&ISM330IS_COMMON_Driver;

    if ((ret == BSP_ERROR_NONE) && ((Functions & MOTION_GYRO) == MOTION_GYRO) && (cap.Gyro == 1U))
    {
      MotionFuncDrv[CUSTOM_ISM330IS_0][FunctionIndex[MOTION_GYRO]] = (MOTION_SENSOR_FuncDrv_t *)&ISM330IS_GYRO_Driver;

      if (MotionDrv[CUSTOM_ISM330IS_0]->Init(IspuMotionCompObj[CUSTOM_ISM330IS_0]) != ISM330IS_OK)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    if ((ret == BSP_ERROR_NONE) && ((Functions & MOTION_ACCELERO) == MOTION_ACCELERO) && (cap.Acc == 1U))
    {
      MotionFuncDrv[CUSTOM_ISM330IS_0][FunctionIndex[MOTION_ACCELERO]] =
        (MOTION_SENSOR_FuncDrv_t *)&ISM330IS_ACC_Driver;

      if (MotionDrv[CUSTOM_ISM330IS_0]->Init(IspuMotionCompObj[CUSTOM_ISM330IS_0]) != ISM330IS_OK)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    if ((ret == BSP_ERROR_NONE) && ((Functions & MOTION_MAGNETO) == MOTION_MAGNETO))
    {
      /* Return an error if the application try to initialize a function not supported by the component */
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
  }

  return ret;
}
#endif /* USE_CUSTOM_MOTION_SENSOR_ISM330IS_0 */

