/**
  ******************************************************************************
  * @file    sensor_commands.c
  * @author  MEMS Software Solutions Team
  * @brief   Handle commands for sensor
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
#include <string.h>
#include "stm32f4xx_nucleo_errno.h"
#include "sensor_commands.h"
#include "com.h"
#include "demo_serial.h"
#include "custom_mems_control.h"
#include "custom_mems_control_ex.h"
#include "custom_ispu_mems_conf_app.h"
#include "custom_ispu_motion_sensors.h"
#include "custom_ispu_motion_sensors_ex.h"
#include "custom_mems_conf_app.h"
#include "custom_motion_sensors.h"
#include "custom_motion_sensors_ex.h"

/** @addtogroup ISPU_APPLICATIONS ISPU APPLICATIONS
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define SENSOR_NAME_MAX_LENGTH  32

#ifndef CUSTOM_ACC_INSTANCE_0
#define CUSTOM_ACC_INSTANCE_0  0xFFFFFFFF
#define CUSTOM_ACC_INSTANCE_NAME_0  ""
#define CUSTOM_ACC_INSTANCE_ODR_0  {0}
#define CUSTOM_ACC_INSTANCE_FS_0  {0}
#endif /* CUSTOM_ACC_INSTANCE_0 */
#ifndef CUSTOM_GYR_INSTANCE_0
#define CUSTOM_GYR_INSTANCE_0  0xFFFFFFFF
#define CUSTOM_GYR_INSTANCE_NAME_0  ""
#define CUSTOM_GYR_INSTANCE_ODR_0  {0}
#define CUSTOM_GYR_INSTANCE_FS_0  {0}
#endif /* CUSTOM_GYR_INSTANCE_0 */
#ifndef CUSTOM_MAG_INSTANCE_0
#define CUSTOM_MAG_INSTANCE_0  0xFFFFFFFF
#define CUSTOM_MAG_INSTANCE_NAME_0  ""
#define CUSTOM_MAG_INSTANCE_ODR_0  {0}
#define CUSTOM_MAG_INSTANCE_FS_0  {0}
#endif /* CUSTOM_MAG_INSTANCE_0 */
#ifndef CUSTOM_HUM_INSTANCE_0
#define CUSTOM_HUM_INSTANCE_0  0xFFFFFFFF
#define CUSTOM_HUM_INSTANCE_NAME_0  ""
#define CUSTOM_HUM_INSTANCE_ODR_0  {0}
#define CUSTOM_HUM_INSTANCE_FS_0  {0}
#endif /* CUSTOM_HUM_INSTANCE_0 */
#ifndef CUSTOM_TEMP_INSTANCE_0
#define CUSTOM_TEMP_INSTANCE_0  0xFFFFFFFF
#define CUSTOM_TEMP_INSTANCE_NAME_0  ""
#define CUSTOM_TEMP_INSTANCE_ODR_0  {0}
#define CUSTOM_TEMP_INSTANCE_FS_0  {0}
#endif /* CUSTOM_TEMP_INSTANCE_0 */
#ifndef CUSTOM_PRESS_INSTANCE_0
#define CUSTOM_PRESS_INSTANCE_0  0xFFFFFFFF
#define CUSTOM_PRESS_INSTANCE_NAME_0  ""
#define CUSTOM_PRESS_INSTANCE_ODR_0  {0}
#define CUSTOM_PRESS_INSTANCE_FS_0  {0}
#endif /* CUSTOM_PRESS_INSTANCE_0 */

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Supported sensor names. Please verify that second index of array is HIGHER than longest string in array!!! */
static uint8_t AccNameList[][SENSOR_NAME_MAX_LENGTH] =
{
  CUSTOM_ACC_INSTANCE_NAME_0,
};
static uint8_t GyrNameList[][SENSOR_NAME_MAX_LENGTH] =
{
  CUSTOM_GYR_INSTANCE_NAME_0,
};
static uint8_t MagNameList[][SENSOR_NAME_MAX_LENGTH] =
{
  CUSTOM_MAG_INSTANCE_NAME_0,
};
static uint8_t HumNameList[][SENSOR_NAME_MAX_LENGTH] =
{
  CUSTOM_HUM_INSTANCE_NAME_0,
};
static uint8_t TmpNameList[][SENSOR_NAME_MAX_LENGTH] =
{
  CUSTOM_TEMP_INSTANCE_NAME_0,
};
static uint8_t PrsNameList[][SENSOR_NAME_MAX_LENGTH] =
{
  CUSTOM_PRESS_INSTANCE_NAME_0,
};

/* MISRAC2012 violations in following groups of definitions */
/* MISRAC2012-Rule-9.2 violation for purpose */
/* MISRAC2012-Rule-9.3 violation for purpose */
/* MISRAC2012-Rule-8.9_a violation to keep the data structures together */

/* Sensor fullscale lists (have to correspond with supported sensor names above)
 * Please verify that second index of array is equal to or higher than count of longest sub-array items */
static uint32_t AccFsList[][16] =   /* g */
{
  CUSTOM_ACC_INSTANCE_FS_0, /* ISPU */
};
static uint32_t GyrFsList[][16] =   /* dps */
{
  CUSTOM_GYR_INSTANCE_FS_0, /* ISPU */
};
static uint32_t MagFsList[][16] =   /* Ga */
{
  CUSTOM_MAG_INSTANCE_FS_0, /* MEMS */
};
static uint32_t HumFsList[][16] =   /* % */
{
  CUSTOM_HUM_INSTANCE_FS_0, /* MEMS */
};
static uint32_t TmpFsList[][16] =   /* C */
{
  CUSTOM_TEMP_INSTANCE_FS_0, /* MEMS */
};
static uint32_t PrsFsList[][16] =   /* Pa */
{
  CUSTOM_PRESS_INSTANCE_FS_0, /* MEMS */
};

/* Sensor output data rate lists (have to correspond with supported sensor names above)
 * Please verify that second index of array is equal to or higher than count of longest sub-array items */
static float AccOdrList[][16] =   /* Hz */
{
  CUSTOM_ACC_INSTANCE_ODR_0, /* ISPU */
};
static float GyrOdrList[][16] =   /* Hz */
{
  CUSTOM_GYR_INSTANCE_ODR_0, /* ISPU */
};
static float MagOdrList[][16] =   /* Hz */
{
  CUSTOM_MAG_INSTANCE_ODR_0, /* MEMS */
};
static float HumOdrList[][16] =   /* Hz */
{
  CUSTOM_HUM_INSTANCE_ODR_0, /* MEMS */
};
static float TmpOdrList[][16] =   /* Hz */
{
  CUSTOM_TEMP_INSTANCE_ODR_0, /* MEMS */
};
static float PrsOdrList[][16] =   /* Hz */
{
  CUSTOM_PRESS_INSTANCE_ODR_0, /* MEMS */
};

/* Supported sensor names of same kind in one string (comma separated) */
static uint8_t AccNamesString[sizeof(AccNameList) + (sizeof(AccNameList) / SENSOR_NAME_MAX_LENGTH)];
static uint8_t GyrNamesString[sizeof(GyrNameList) + (sizeof(GyrNameList) / SENSOR_NAME_MAX_LENGTH)];
static uint8_t MagNamesString[sizeof(MagNameList) + (sizeof(MagNameList) / SENSOR_NAME_MAX_LENGTH)];
static uint8_t TmpNamesString[sizeof(TmpNameList) + (sizeof(TmpNameList) / SENSOR_NAME_MAX_LENGTH)];
static uint8_t HumNamesString[sizeof(HumNameList) + (sizeof(HumNameList) / SENSOR_NAME_MAX_LENGTH)];
static uint8_t PrsNamesString[sizeof(PrsNameList) + (sizeof(PrsNameList) / SENSOR_NAME_MAX_LENGTH)];

/* Currently selected sensor indexes */
static uint8_t AccIndex = 0;
static uint8_t GyrIndex = 0;
static uint8_t MagIndex = 0;
static uint8_t HumIndex = 0;
static uint8_t TmpIndex = 0;
static uint8_t PrsIndex = 0;

/* Private function prototypes -----------------------------------------------*/
static int32_t SC_Get_Sensor_Name(TMsg_t *Msg);
static int32_t SC_Read_Register(TMsg_t *Msg);
static int32_t SC_Write_Register(TMsg_t *Msg);
static int32_t SC_Get_Full_Scale_List(TMsg_t *Msg);
static int32_t SC_Set_Full_Scale(TMsg_t *Msg);
static int32_t SC_Get_Full_Scale(TMsg_t *Msg);
static int32_t SC_Get_ODR_List(TMsg_t *Msg);
static int32_t SC_Set_ODR(TMsg_t *Msg);
static int32_t SC_Get_ODR(TMsg_t *Msg);
static int32_t SC_Get_Sensor_List(TMsg_t *Msg);
static int32_t SC_Set_Sensor_Index(TMsg_t *Msg);
static int32_t SC_Write_Multi_Register(TMsg_t *Msg);

static void Send_Sensor_Name(TMsg_t *Msg, uint8_t *SensorName);
static void Send_Sensor_FS_List(TMsg_t *Msg, uint32_t *FsList);
static void Send_Sensor_ODR_List(TMsg_t *Msg, float_t *OdrList);

static void ArrayToFloat(uint8_t *Source, float *data);

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Handle Sensors command
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
int32_t Handle_Sensor_Command(TMsg_t *Msg)
{
  int32_t ret;

  /* Commands */
  switch (Msg->Data[3])
  {
    case SC_GET_SENSOR_NAME:
      ret = SC_Get_Sensor_Name(Msg);
      break;

    case SC_READ_REGISTER:
      ret = SC_Read_Register(Msg);
      break;

    case SC_WRITE_REGISTER:
      ret = SC_Write_Register(Msg);
      break;

    case SC_GET_FULL_SCALE_LIST:
      ret = SC_Get_Full_Scale_List(Msg);
      break;

    case SC_SET_FULL_SCALE:
      ret = SC_Set_Full_Scale(Msg);
      break;

    case SC_GET_FULL_SCALE:
      ret = SC_Get_Full_Scale(Msg);
      break;

    case SC_GET_ODR_LIST:
      ret = SC_Get_ODR_List(Msg);
      break;

    case SC_SET_ODR:
      ret = SC_Set_ODR(Msg);
      break;

    case SC_GET_ODR:
      ret = SC_Get_ODR(Msg);
      break;

    case SC_GET_SENSOR_LIST:
      ret = SC_Get_Sensor_List(Msg);
      break;

    case SC_SET_SENSOR_INDEX:
      ret = SC_Set_Sensor_Index(Msg);
      break;

    case SC_WRITE_MULTI_REGISTER:
      ret = SC_Write_Multi_Register(Msg);
      break;

    default:
      ret = 0;
      break;
  }

  return ret;
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Get sensor name
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Get_Sensor_Name(TMsg_t *Msg)
{
  int32_t ret = 1;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      Send_Sensor_Name(Msg, AccNameList[AccIndex]);
      break;

    case SC_GYROSCOPE:
      Send_Sensor_Name(Msg, GyrNameList[GyrIndex]);
      break;

    case SC_MAGNETOMETER:
      Send_Sensor_Name(Msg, MagNameList[MagIndex]);
      break;

    case SC_TEMPERATURE:
      Send_Sensor_Name(Msg, TmpNameList[TmpIndex]);
      break;

    case SC_HUMIDITY:
      Send_Sensor_Name(Msg, HumNameList[HumIndex]);
      break;

    case SC_PRESSURE:
      Send_Sensor_Name(Msg, PrsNameList[PrsIndex]);
      break;

    default:
      ret = 0;
      break;
  }

  return ret;
}

/**
  * @brief  Read sensor register
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Read_Register(TMsg_t *Msg)
{
  uint8_t reg_value = 0;
  int32_t ret = 1;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      BSP_SENSOR_ACC_Read_Register(Msg->Data[5], &reg_value);
      break;

    case SC_GYROSCOPE:
      BSP_SENSOR_GYR_Read_Register(Msg->Data[5], &reg_value);
      break;

    case SC_MAGNETOMETER:
      BSP_SENSOR_MAG_Read_Register(Msg->Data[5], &reg_value);
      break;

    case SC_TEMPERATURE:
      BSP_SENSOR_TEMP_Read_Register(Msg->Data[5], &reg_value);
      break;

    case SC_HUMIDITY:
      BSP_SENSOR_HUM_Read_Register(Msg->Data[5], &reg_value);
      break;

    case SC_PRESSURE:
      BSP_SENSOR_PRESS_Read_Register(Msg->Data[5], &reg_value);
      break;

    default:
      ret = 0;
      break;
  }

  if (ret != 0)
  {
    BUILD_REPLY_HEADER(Msg);
    Msg->Data[6] = reg_value;
    Msg->Len = 7;
    UART_SendMsg(Msg);
  }

  return ret;
}

/**
  * @brief  Write to sensor register
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Write_Register(TMsg_t *Msg)
{
  int32_t ret = 1;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      BSP_SENSOR_ACC_Write_Register(Msg->Data[5], Msg->Data[6]);
      break;

    case SC_GYROSCOPE:
      BSP_SENSOR_GYR_Write_Register(Msg->Data[5], Msg->Data[6]);
      break;

    case SC_MAGNETOMETER:
      BSP_SENSOR_MAG_Write_Register(Msg->Data[5], Msg->Data[6]);
      break;

    case SC_TEMPERATURE:
      BSP_SENSOR_TEMP_Write_Register(Msg->Data[5], Msg->Data[6]);
      break;

    case SC_HUMIDITY:
      BSP_SENSOR_HUM_Write_Register(Msg->Data[5], Msg->Data[6]);
      break;

    case SC_PRESSURE:
      BSP_SENSOR_PRESS_Write_Register(Msg->Data[5], Msg->Data[6]);
      break;

    default:
      ret = 0;
      break;
  }

  if (ret != 0)
  {
    BUILD_REPLY_HEADER(Msg);
    Msg->Len = 7;
    UART_SendMsg(Msg);
  }

  return ret;
}

/**
  * @brief  Get sensor full scale list
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Get_Full_Scale_List(TMsg_t *Msg)
{
  int32_t ret = 1;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      Send_Sensor_FS_List(Msg, AccFsList[AccIndex]);
      break;

    case SC_GYROSCOPE:
      Send_Sensor_FS_List(Msg, GyrFsList[GyrIndex]);
      break;

    case SC_MAGNETOMETER:
      Send_Sensor_FS_List(Msg, MagFsList[MagIndex]);
      break;

    case SC_TEMPERATURE:
      Send_Sensor_FS_List(Msg, TmpFsList[TmpIndex]);
      break;

    case SC_HUMIDITY:
      Send_Sensor_FS_List(Msg, HumFsList[HumIndex]);
      break;

    case SC_PRESSURE:
      Send_Sensor_FS_List(Msg, PrsFsList[PrsIndex]);
      break;

    default:
      ret = 0;
      break;
  }

  return ret;
}

/**
  * @brief  Set sensor full scale
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Set_Full_Scale(TMsg_t *Msg)
{
  uint32_t full_scale = Deserialize(&Msg->Data[5], 4);
  int32_t ret = 1;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      BSP_SENSOR_ACC_SetFullScale((int32_t)full_scale);
      break;

    case SC_GYROSCOPE:
      BSP_SENSOR_GYR_SetFullScale((int32_t)full_scale);
      break;

    case SC_MAGNETOMETER:
      BSP_SENSOR_MAG_SetFullScale((int32_t)full_scale);
      break;

    case SC_TEMPERATURE:
    case SC_HUMIDITY:
    case SC_PRESSURE:
      break;

    default:
      ret = 0;
      break;
  }

  if (ret != 0)
  {
    BUILD_REPLY_HEADER(Msg);
    Msg->Len = 9;
    UART_SendMsg(Msg);
  }

  return ret;
}

/**
  * @brief  Get sensor full scale
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Get_Full_Scale(TMsg_t *Msg)
{
  int32_t full_scale = 0;
  int32_t ret = 1;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      BSP_SENSOR_ACC_GetFullScale(&full_scale);
      break;

    case SC_GYROSCOPE:
      BSP_SENSOR_GYR_GetFullScale(&full_scale);
      break;

    case SC_MAGNETOMETER:
      BSP_SENSOR_MAG_GetFullScale(&full_scale);
      break;

    case SC_TEMPERATURE:
    case SC_HUMIDITY:
    case SC_PRESSURE:
      break;

    default:
      ret = 0;
      break;
  }

  if (ret != 0)
  {
    BUILD_REPLY_HEADER(Msg);
    Serialize(&Msg->Data[5], (uint32_t)full_scale, 4);
    Msg->Len = 9;
    UART_SendMsg(Msg);
  }

  return ret;
}

/**
  * @brief  Get sensor output data rate list
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Get_ODR_List(TMsg_t *Msg)
{
  int32_t ret = 1;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      Send_Sensor_ODR_List(Msg, AccOdrList[AccIndex]);
      break;

    case SC_GYROSCOPE:
      Send_Sensor_ODR_List(Msg, GyrOdrList[GyrIndex]);
      break;

    case SC_MAGNETOMETER:
      Send_Sensor_ODR_List(Msg, MagOdrList[MagIndex]);
      break;

    case SC_TEMPERATURE:
      Send_Sensor_ODR_List(Msg, TmpOdrList[TmpIndex]);
      break;

    case SC_HUMIDITY:
      Send_Sensor_ODR_List(Msg, HumOdrList[HumIndex]);
      break;

    case SC_PRESSURE:
      Send_Sensor_ODR_List(Msg, PrsOdrList[PrsIndex]);
      break;

    default:
      ret = 0;
      break;
  }

  return ret;
}

/**
  * @brief  Set sensor output data rate
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Set_ODR(TMsg_t *Msg)
{
  float_t odr = 0.0f;
  int32_t ret = 1;

  ArrayToFloat(&Msg->Data[5], &odr);

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      BSP_SENSOR_ACC_SetOutputDataRate(odr);
      break;

    case SC_GYROSCOPE:
      BSP_SENSOR_GYR_SetOutputDataRate(odr);
      break;

    case SC_MAGNETOMETER:
      BSP_SENSOR_MAG_SetOutputDataRate(odr);
      break;

    case SC_TEMPERATURE:
      BSP_SENSOR_TEMP_SetOutputDataRate(odr);
      break;

    case SC_HUMIDITY:
      BSP_SENSOR_HUM_SetOutputDataRate(odr);
      break;

    case SC_PRESSURE:
      BSP_SENSOR_PRESS_SetOutputDataRate(odr);
      break;

    default:
      ret = 0;
      break;
  }

  if (ret != 0)
  {
    BUILD_REPLY_HEADER(Msg);
    Msg->Len = 9;
    UART_SendMsg(Msg);
  }

  return ret;
}

/**
  * @brief  Get sensor output data rate
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Get_ODR(TMsg_t *Msg)
{
  float_t odr = 0.0f;
  int32_t ret = 1;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      BSP_SENSOR_ACC_GetOutputDataRate(&odr);
      break;

    case SC_GYROSCOPE:
      BSP_SENSOR_GYR_GetOutputDataRate(&odr);
      break;

    case SC_MAGNETOMETER:
      BSP_SENSOR_MAG_GetOutputDataRate(&odr);
      break;

    case SC_TEMPERATURE:
      BSP_SENSOR_TEMP_GetOutputDataRate(&odr);
      break;

    case SC_HUMIDITY:
      BSP_SENSOR_HUM_GetOutputDataRate(&odr);
      break;

    case SC_PRESSURE:
      BSP_SENSOR_PRESS_GetOutputDataRate(&odr);
      break;

    default:
      ret = 0;
      break;
  }

  if (ret != 0)
  {
    BUILD_REPLY_HEADER(Msg);
    FloatToArray(&Msg->Data[5], odr);
    Msg->Len = 9;
    UART_SendMsg(Msg);
  }

  return ret;
}

/**
  * @brief  Get sensor list
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Get_Sensor_List(TMsg_t *Msg)
{
  int32_t ret = 1;
  uint32_t i;

  /* MISRAC2012-Dir-4.6_a violations in order to use strcat function */

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      for (i = 0; i < sizeof(AccNamesString); i++)
      {
        AccNamesString[i] = (uint8_t)'\0';
      }
      (void)strcat((char *)AccNamesString, (char *)AccNameList[AccIndex]);
      Send_Sensor_Name(Msg, AccNamesString);
      break;

    case SC_GYROSCOPE:
      for (i = 0; i < sizeof(GyrNamesString); i++)
      {
        GyrNamesString[i] = (uint8_t)'\0';
      }
      (void)strcat((char *)GyrNamesString, (char *)GyrNameList[GyrIndex]);
      Send_Sensor_Name(Msg, GyrNamesString);
      break;

    case SC_MAGNETOMETER:
      for (i = 0; i < sizeof(MagNamesString); i++)
      {
        MagNamesString[i] = (uint8_t)'\0';
      }
      (void)strcat((char *)MagNamesString, (char *)MagNameList[MagIndex]);
      Send_Sensor_Name(Msg, MagNamesString);
      break;

    case SC_TEMPERATURE:
      for (i = 0; i < sizeof(TmpNamesString); i++)
      {
        TmpNamesString[i] = (uint8_t)'\0';
      }
      (void)strcat((char *)TmpNamesString, (char *)TmpNameList[TmpIndex]);
      Send_Sensor_Name(Msg, TmpNamesString);
      break;

    case SC_HUMIDITY:
      for (i = 0; i < sizeof(HumNamesString); i++)
      {
        HumNamesString[i] = (uint8_t)'\0';
      }
      (void)strcat((char *)HumNamesString, (char *)HumNameList[HumIndex]);
      Send_Sensor_Name(Msg, HumNamesString);
      break;

    case SC_PRESSURE:
      for (i = 0; i < sizeof(PrsNamesString); i++)
      {
        PrsNamesString[i] = (uint8_t)'\0';
      }
      (void)strcat((char *)PrsNamesString, (char *)PrsNameList[PrsIndex]);
      Send_Sensor_Name(Msg, PrsNamesString);
      break;

    default:
      ret = 0;
      break;
  }

  return ret;
}

/**
  * @brief  Set sensor index
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Set_Sensor_Index(TMsg_t *Msg)
{
  int32_t ret;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      if (AccIndex != Msg->Data[5])
      {
        ret = 0;
      }
      else
      {
        ret = (int32_t)BSP_SENSOR_ACC_Init();
      }
      break;

    case SC_GYROSCOPE:
      if (GyrIndex != Msg->Data[5])
      {
        ret = 0;
      }
      else
      {
        ret = (int32_t)BSP_SENSOR_GYR_Init();
      }
      break;

    case SC_MAGNETOMETER:
      if (MagIndex != Msg->Data[5])
      {
        ret = 0;
      }
      else
      {
        ret = (int32_t)BSP_SENSOR_MAG_Init();
      }
      break;

    case SC_TEMPERATURE:
      if (TmpIndex != Msg->Data[5])
      {
        ret = 0;
      }
      else
      {
        ret = (int32_t)BSP_SENSOR_TEMP_Init();
      }
      break;

    case SC_HUMIDITY:
      if (HumIndex != Msg->Data[5])
      {
        ret = 0;
      }
      else
      {
        ret = (int32_t)BSP_SENSOR_HUM_Init();
      }
      break;

    case SC_PRESSURE:
      if (PrsIndex != Msg->Data[5])
      {
        ret = 0;
      }
      else
      {
        ret = (int32_t)BSP_SENSOR_PRESS_Init();
      }
      break;

    default:
      ret = 0;
      break;
  }

  BUILD_REPLY_HEADER(Msg);
  Msg->Data[5U] = (uint8_t)ret;
  Msg->Len = 6U;
  UART_SendMsg(Msg);

  return ret;
}

/**
  * @brief  Write to sensor registers
  * @param  Msg the pointer to the message to be handled
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static int32_t SC_Write_Multi_Register(TMsg_t *Msg)
{
  int32_t ret = 1;
  uint8_t i;

  /* Sensor Type */
  switch (Msg->Data[4])
  {
    case SC_ACCELEROMETER:
      for (i = 0; i < Msg->Data[5]; i++)
      {
        BSP_SENSOR_ACC_Write_Register(Msg->Data[6U + (2U * i)], Msg->Data[7U + (2U * i)]);
      }
      break;

    case SC_GYROSCOPE:
      for (i = 0; i < Msg->Data[5]; i++)
      {
        BSP_SENSOR_GYR_Write_Register(Msg->Data[6U + (2U * i)], Msg->Data[7U + (2U * i)]);
      }
      break;

    case SC_MAGNETOMETER:
      for (i = 0; i < Msg->Data[5]; i++)
      {
        BSP_SENSOR_MAG_Write_Register(Msg->Data[6U + (2U * i)], Msg->Data[7U + (2U * i)]);
      }
      break;

    case SC_TEMPERATURE:
      for (i = 0; i < Msg->Data[5]; i++)
      {
        BSP_SENSOR_TEMP_Write_Register(Msg->Data[6U + (2U * i)], Msg->Data[7U + (2U * i)]);
      }
      break;

    case SC_HUMIDITY:
      for (i = 0; i < Msg->Data[5]; i++)
      {
        BSP_SENSOR_HUM_Write_Register(Msg->Data[6U + (2U * i)], Msg->Data[7U + (2U * i)]);
      }
      break;

    case SC_PRESSURE:
      for (i = 0; i < Msg->Data[5]; i++)
      {
        BSP_SENSOR_PRESS_Write_Register(Msg->Data[6U + (2U * i)], Msg->Data[7U + (2U * i)]);
      }
      break;

    default:
      ret = 0;
      break;
  }

  if (ret != 0)
  {
    BUILD_REPLY_HEADER(Msg);
    Msg->Len = 6;
    UART_SendMsg(Msg);
  }

  return ret;
}

/**
  * @brief  Send sensor name
  * @param  Msg the pointer to the message to be handled
  * @param  SensorName the sensor name
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static void Send_Sensor_Name(TMsg_t *Msg, uint8_t *SensorName)
{
  uint32_t i = 0;
  BUILD_REPLY_HEADER(Msg);

  /* MISRAC2012-Dir-4.6_a violation in order to use strlen function */
  while (i < strlen((char const *)SensorName))
  {
    Msg->Data[5U + i] = SensorName[i];
    i++;
  }

  Msg->Len = 5U + i;
  UART_SendMsg(Msg);
}

/**
  * @brief  Send sensor full scale list
  * @param  Msg the pointer to the message to be handled
  * @param  FsList the sensor full scale list
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static void Send_Sensor_FS_List(TMsg_t *Msg, uint32_t *FsList)
{
  uint32_t i;
  BUILD_REPLY_HEADER(Msg);

  Serialize(&Msg->Data[5], FsList[0], 4);

  for (i = 0; i < FsList[0]; i++)
  {
    Serialize(&Msg->Data[9U + (i * 4U)], FsList[i + 1U], 4U);
  }

  Msg->Len = 9U + (i * 4U);
  UART_SendMsg(Msg);
}

/**
  * @brief  Send sensor output data rate list
  * @param  Msg the pointer to the message to be handled
  * @param  OdrList the sensor output data rate list
  * @retval 1 if the message is correctly handled, 0 otherwise
  */
static void Send_Sensor_ODR_List(TMsg_t *Msg, float_t *OdrList)
{
  uint32_t i;
  BUILD_REPLY_HEADER(Msg);

  Serialize(&Msg->Data[5], (uint32_t)OdrList[0], 4);

  for (i = 0; i < (uint32_t)OdrList[0]; i++)
  {
    FloatToArray(&Msg->Data[9U + (i * 4U)], OdrList[i + 1U]);
  }

  Msg->Len = 9U + (i * 4U);
  UART_SendMsg(Msg);
}

/**
  * @brief  Copy float data from array
  * @param  Source the pointer to the source data
  * @param  data the pointer to the destination
  * @retval None
  */
static void ArrayToFloat(uint8_t *Source, float_t *data)
{
  (void)memcpy((void *)data, (void *)Source, sizeof(float_t));
}

/**
  * @}
  */
