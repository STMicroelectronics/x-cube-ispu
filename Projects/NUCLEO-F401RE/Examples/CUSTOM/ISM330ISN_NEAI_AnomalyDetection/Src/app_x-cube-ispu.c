/**
  ******************************************************************************
  * File Name          : app_x-cube-ispu.c
  * Description        : This file provides code for the configuration
  *                      of the STMicroelectronics.X-CUBE-ISPU.2.1.0 instances.
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

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_x-cube-ispu.h"
#include "main.h"
#include <stdio.h>

#include "custom_mems_control.h"
#include "custom_mems_control_ex.h"
#include "custom_ispu_mems_conf_app.h"
#include "int_pins_interface.h"
#include "ispu_ctrl.h"
#include "ispu_neai.h"
#include "shared_mem.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  LEARNING_STARTING = 0,
  LEARNING_IN_PROGRESS,
  LEARNING_ENDING,
  LEARNING_FINISHED,
} Learning_Status_t;

/* Private define ------------------------------------------------------------*/
#define MAX_BUF_SIZE     256
#define LEARNING_TIME_S  20U /* [s] */

/* Public variables ----------------------------------------------------------*/
char data_out[MAX_BUF_SIZE];
enum ispu_mode ispu_mode;
enum ispu_comm ispu_comm;
enum neai_state neai_state;
int anomaly_detected = 0;
int learn_count;
int fetch_in_progress = 0;
int ad_nr = 0;

/* Private variables ---------------------------------------------------------*/
static volatile uint8_t enable_int;

/* Private function prototypes -----------------------------------------------*/
static void MX_NEAI_AnomalyDetection_Init(void);
static void MX_NEAI_AnomalyDetection_Process(void);

void MX_X_CUBE_ISPU_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN X_CUBE_ISPU_Init_PreTreatment */

  /* USER CODE END X_CUBE_ISPU_Init_PreTreatment */

  /* Initialize the peripherals and the MEMS components */

  MX_NEAI_AnomalyDetection_Init();

  /* USER CODE BEGIN X_CUBE_ISPU_Init_PostTreatment */

  /* USER CODE END X_CUBE_ISPU_Init_PostTreatment */
}

/*
 * LM background task
 */
void MX_X_CUBE_ISPU_Process(void)
{
  /* USER CODE BEGIN X_CUBE_ISPU_Process_PreTreatment */

  /* USER CODE END X_CUBE_ISPU_Process_PreTreatment */

  MX_NEAI_AnomalyDetection_Process();

  /* USER CODE BEGIN X_CUBE_ISPU_Process_PostTreatment */

  /* USER CODE END X_CUBE_ISPU_Process_PostTreatment */
}

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Read data from ISPU
  * @param  reg register address
  * @param  val data
  * @param  len data length
  * @retval None
  */
void ispu_read(uint8_t reg, uint8_t *val, uint16_t len)
{
  uint16_t i;

  for (i = 0; i < len; i++)
  {
    BSP_SENSOR_ACC_Read_Register(reg + i, &val[i]);
  }
}

/**
  * @brief  Write data to ISPU
  * @param  reg register address
  * @param  val data
  * @retval None
  */
void ispu_write(uint8_t reg, uint8_t val)
{
  BSP_SENSOR_ACC_Write_Register(reg, val);
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initialize the application
  * @param  None
  * @retval None
  */
static void MX_NEAI_AnomalyDetection_Init(void)
{
  uint8_t ctrl;
  uint32_t i;
  uint8_t status;

  /* Initialize LED */
  (void)BSP_LED_Init(LED2);

  /* Set EXTI settings for INT pins */
  Set_Int_Pins_Exti();

  /* Initialize Virtual COM Port */
  (void)BSP_COM_Init(COM1);

  snprintf(data_out, MAX_BUF_SIZE, "\r\nISPU NEAI Anomaly Detection Demo\r\n");
  printf("%s", data_out);

  (void)BSP_LED_On(LED2);
  HAL_Delay(500);
  (void)BSP_LED_Off(LED2);

  snprintf(data_out, MAX_BUF_SIZE, "Initialization\r\n");
  printf("%s", data_out);

  /* Initialize the sensor */
  (void)BSP_SENSOR_ACC_Init();

  /* Reset the ISPU */
  ispu_write(0x12, 0x01);
  while (1)
  {
    ispu_read(0x12, &ctrl, 1);
    if (!(ctrl & 1))
    {
      break;
    }
  }

  /* Make sure the user bank is selected */
  ispu_write(0x01, 0x00);

  initialize_ctrl_interface();

  /* Load device configuration */
  for (i = 0; i < sizeof(ispu_conf) / sizeof(ucf_line_ext_t); i++)
  {
    if (ispu_conf[i].op == MEMS_UCF_OP_WRITE)
    {
      ispu_write(ispu_conf[i].address, ispu_conf[i].data);
    }
    else if (ispu_conf[i].op == MEMS_UCF_OP_DELAY)
    {
      HAL_Delay(ispu_conf[i].data);
    }
  }

  /* Wait until the ISPU raises the boot flag */
  ispu_write(0x01, 0x80);
  do
  {
    ispu_read(0x04, &status, 1);
  } while (!(status & (1 << 2)));
  ispu_write(0x01, 0x00);

  HAL_Delay(500);

  enable_int = 1;

  neai_state = get_neai_status();

  if (neai_state == NEAI_BOARD_ERROR)
  {
    snprintf(data_out, MAX_BUF_SIZE, "Not an N version\r\n");
    printf("%s", data_out);
    /* NanoEdgeAI is not loaded on a compatible ISPU board */
    while (1);
  }
  snprintf(data_out, MAX_BUF_SIZE, "It is an N version\r\n");
  printf("%s", data_out);

  INT1Detected = 0;
  INT2Detected = 0;
}

/**
  * @brief  Process of the application
  * @param  None
  * @retval None
  */
static void MX_NEAI_AnomalyDetection_Process(void)
{
  static Learning_Status_t learning_status = LEARNING_STARTING;
  static uint8_t learning_time = 0;
  static int16_t acc_x, acc_y, acc_z;

  switch (learning_status)
  {
    case LEARNING_STARTING:
      snprintf(data_out, MAX_BUF_SIZE, "Learning phase START\r\n");
      printf("%s", data_out);
      do
      {
        ispu_comm = ispu_send_cmd(SET_MODE, MODE_LEARNING);
      } while (ispu_comm != ISPU_COMM_OK);
      learning_status = LEARNING_IN_PROGRESS;
      break;
    case LEARNING_IN_PROGRESS:
      HAL_Delay(100);
      learning_time++;
      if (learning_time == LEARNING_TIME_S * 10U)
      {
        learning_status = LEARNING_ENDING;
      }
      break;
    case LEARNING_ENDING:
      snprintf(data_out, MAX_BUF_SIZE, "Learning phase END\r\n");
      printf("%s", data_out);
      do
      {
        ispu_comm = ispu_send_cmd(SET_MODE, MODE_DETECT);
      } while (ispu_comm != ISPU_COMM_OK);
      learning_status = LEARNING_FINISHED;
    default:
      break;
  }

  if (enable_int != 0U)
  {
    (void)BSP_LED_Toggle(LED2);

    if (INT1Detected != 0U)
    {
      process_answer();
      INT1Detected = 0;
    }

    if (INT2Detected != 0U)
    {
      switch (ispu_mode)
      {
        case MODE_SAMPLING:
          get_accelerometer_samples(&acc_x, &acc_y, &acc_z);
          snprintf(data_out, MAX_BUF_SIZE, "ACC x: %d, y: %d, z: %d\r\n", acc_x, acc_y, acc_z);
          printf("%s", data_out);
          break;
        case MODE_LEARNING:
          learn_count++;
          snprintf(data_out, MAX_BUF_SIZE, "Learning in progress %d !!!\r\n", learn_count);
          printf("%s", data_out);
          break;
        case MODE_DETECT:
          snprintf(data_out, MAX_BUF_SIZE, "Anomaly detected !!!\r\n");
          printf("%s", data_out);
          anomaly_detected = 1;
          break;
        default:
          break;
      }
      INT2Detected = 0;
    }

    /* User can put CPU to sleep and wake up only when there is an anomaly
       detected, then fetch the data */
    if (!fetch_in_progress)
    {
      if (anomaly_detected)
      {
        fetch_in_progress = 1;
        neai_state = get_neai_status();

        if (neai_state == NEAI_NOT_ENOUGH_CALL_TO_LEARNING)
        {
          /* Please make sure that the ISPU spend enough time in learning mode */
        }

        do
        {
          ispu_comm = ispu_send_cmd(FETCH_DATA);
        } while (ispu_comm != ISPU_COMM_OK);
      }
    }
  }
  else
  {
    (void)BSP_LED_Off(LED2);
  }
}

#ifdef __cplusplus
}
#endif
