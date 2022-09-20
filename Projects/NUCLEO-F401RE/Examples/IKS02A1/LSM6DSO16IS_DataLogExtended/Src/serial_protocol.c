/**
  ******************************************************************************
  * @file    serial_protocol.c
  * @author  MEMS Software Solutions Team
  * @brief   This file implements some utilities for the serial protocol
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

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "serial_protocol.h"

/** @addtogroup MOTION_APPLICATIONS MOTION APPLICATIONS
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Byte stuffing process for one byte
  * @param  Dest destination
  * @param  Source source
  * @retval Total number of bytes processed
  */
int32_t ByteStuffCopyByte(uint8_t *Dest, uint8_t Source)
{
  int32_t ret = 2;

  switch (Source)
  {
    case TMSG_EOF:
      Dest[0] = TMSG_BS;
      Dest[1] = TMSG_BS_EOF;
      break;

    case TMSG_BS:
      Dest[0] = TMSG_BS;
      Dest[1] = TMSG_BS;
      break;

    default:
      Dest[0] = Source;
      ret = 1;
      break;
  }

  return ret;
}

/**
  * @brief  Byte stuffing process for a Msg
  * @param  Dest destination
  * @param  Source source
  * @retval Total number of bytes processed
  */
int32_t ByteStuffCopy(uint8_t *Dest, TMsg_t *Source)
{
  uint32_t i;
  int32_t count = 0;

  for (i = 0; i < Source->Len; i++)
  {
    count += ByteStuffCopyByte(&Dest[count], Source->Data[i]);
  }

  Dest[count] = TMSG_EOF;
  count++;
  return count;
}

/**
  * @brief  Reverse Byte stuffing process for one byte
  * @param  Source source
  * @param  Dest destination
  * @retval Number of input bytes processed (1 or 2) or 0 for invalid sequence
  */
int32_t ReverseByteStuffCopyByte(uint8_t *Source, uint8_t *Dest)
{
  int32_t ret;

  if (Source[0] == (uint8_t)TMSG_BS)
  {
    if (Source[1] == (uint8_t)TMSG_BS)
    {
      *Dest = TMSG_BS;
      ret = 2;
    }
    else if (Source[1] == (uint8_t)TMSG_BS_EOF)
    {
      *Dest = TMSG_EOF;
      ret = 2;
    }
    else
    {
      ret = 0; /* Invalid sequence */
    }
  }
  else
  {
    *Dest = Source[0];
    ret = 1;
  }

  return ret;
}

/**
  * @brief  Reverse Byte stuffing process for two input data
  * @param  Source0 input data
  * @param  Source1 input data
  * @param  Dest the destination data
  * @retval Number of input bytes processed (1 or 2) or 0 for invalid sequence
  */
int32_t ReverseByteStuffCopyByte2(uint8_t Source0, uint8_t Source1, uint8_t *Dest)
{
  int32_t ret;

  if (Source0 == (uint8_t)TMSG_BS)
  {
    if (Source1 == (uint8_t)TMSG_BS)
    {
      *Dest = TMSG_BS;
      ret = 2;
    }
    else if (Source1 == (uint8_t)TMSG_BS_EOF)
    {
      *Dest = TMSG_EOF;
      ret = 2;
    }
    else
    {
      ret = 0; /* Invalid sequence */
    }
  }
  else
  {
    *Dest = Source0;
    ret = 1;
  }

  return ret;
}

/**
  * @brief  Reverse Byte stuffing process for a Msg
  * @param  Dest destination
  * @param  Source source
  * @retval 1 if the operation succeeds, 0 if an error occurs
  */
int32_t ReverseByteStuffCopy(TMsg_t *Dest, uint8_t *Source)
{
  uint32_t count = 0;
  int32_t state = 0;
  int32_t ret = 1;
  uint8_t *source_local;

  source_local = Source;

  while ((*source_local) != (uint8_t)TMSG_EOF)
  {
    if (state == 0)
    {
      if ((*source_local) == (uint8_t)TMSG_BS)
      {
        state = 1;
      }
      else
      {
        Dest->Data[count] = *source_local;
        count++;
      }
    }
    else
    {
      if ((*source_local) == (uint8_t)TMSG_BS)
      {
        Dest->Data[count] = TMSG_BS;
        count++;
      }
      else
      {
        if ((*source_local) == (uint8_t)TMSG_BS_EOF)
        {
          Dest->Data[count] = TMSG_EOF;
          count++;
        }
        else
        {
          ret = 0; /* Invalid sequence */
          break;
        }
      }

      state = 0;
    }

    source_local++;
  }

  if (state != 0)
  {
    ret = 0;
  }

  if (ret != 0)
  {
    Dest->Len = count;
  }

  return ret;
}

/**
  * @brief  Compute and add checksum
  * @param  Msg pointer to the message
  * @retval None
  */
void CHK_ComputeAndAdd(TMsg_t *Msg)
{
  uint8_t chk = 0;
  uint32_t i;

  for (i = 0; i < Msg->Len; i++)
  {
    chk -= Msg->Data[i];
  }

  Msg->Data[i] = chk;
  Msg->Len++;
}

/**
  * @brief  Compute and remove checksum
  * @param  Msg pointer to the message
  * @retval A number different from 0 if the operation succeeds, 0 if an error occurs
  */
int32_t CHK_CheckAndRemove(TMsg_t *Msg)
{
  uint8_t chk = 0;
  uint32_t i;
  int32_t ret;

  for (i = 0; i < Msg->Len; i++)
  {
    chk += Msg->Data[i];
  }

  Msg->Len--;

  if (chk == 0U)
  {
    ret = 1;
  }
  else
  {
    ret = 0;
  }

  return ret;
}

/**
  * @brief  Build an array from the uint32_t (LSB first)
  * @param  Dest destination
  * @param  Source source
  * @param  Len number of bytes
  * @retval None
  */
void Serialize(uint8_t *Dest, uint32_t Source, uint32_t Len)
{
  uint32_t i;
  uint32_t source_local = Source;

  for (i = 0; i < Len; i++)
  {
    Dest[i] = (uint8_t)source_local & 0xFFU;
    source_local >>= 8;
  }
}

/**
  * @brief  Unbuild a Number from an array (LSB first)
  * @param  Source source
  * @param  Len number of bytes
  * @retval Rebuild unsigned int variable
  */
uint32_t Deserialize(uint8_t *Source, uint32_t Len)
{
  uint32_t app;
  uint32_t len_local = Len;

  len_local--;
  app = Source[len_local];
  while (len_local > 0U)
  {
    app <<= 8;
    len_local--;
    app += Source[len_local];
  }

  return app;
}

/**
  * @brief  Build an array from the uint32_t (LSB first)
  * @param  Dest destination
  * @param  Source source
  * @param  Len number of bytes
  * @retval None
  */
void Serialize_s32(uint8_t *Dest, int32_t Source, uint32_t Len)
{
  uint32_t i;
  uint32_t source_uint32;

  source_uint32 = (uint32_t)Source;

  for (i = 0; i < Len; i++)
  {
    Dest[i] = (uint8_t)(source_uint32 & 0xFFU);
    source_uint32 >>= 8;
  }
}

/**
  * @brief  Unbuild a Number from an array (LSB first)
  * @param  Source source
  * @param  Len number of bytes
  * @retval Rebuild signed int variable
  */
int32_t Deserialize_s32(uint8_t *Source, uint32_t Len)
{
  uint32_t app;
  uint32_t len_local = Len;

  len_local--;
  app = (uint32_t)Source[len_local];
  while (len_local > 0U)
  {
    app <<= 8;
    len_local--;
    app += (uint32_t)Source[len_local];
  }

  return (int32_t)app;
}

/**
  * @brief  Build an array from the float
  * @param  Dest destination
  * @param  Data source
  * @retval None
  */
void FloatToArray(uint8_t *Dest, float_t Data)
{
  (void)memcpy((void *)Dest, (void *)&Data, 4);
}

/**
  * @}
  */
