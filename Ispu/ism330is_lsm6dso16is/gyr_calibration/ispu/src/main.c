/**
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

#include "peripherals.h"
#include "reg_map.h"

#include <stddef.h>
#include "motion_gc.h"

#define ACC_SENS 0.000244f
#define GYR_SENS 0.070f
#define MGC_MAX_GYRO 20.0f

static volatile uint32_t int_status;

void __attribute__ ((signal)) algo_00_init(void)
{
	float dtime, freq;
	uint32_t dt = ((uint32_t)cast_uint16_t(ISPU_DTIME_1) << 16) | cast_uint16_t(ISPU_DTIME_0);
	dtime = *((float *)&dt) * 2.0f;
	freq = 1.0f / dtime;

	MGC_mcu_type_t mcu = MGC_MCU_ISPU;
	MotionGC_Initialize(mcu, &freq);

	MGC_knobs_t knobs;
	MotionGC_GetKnobs(&knobs);
	knobs.MaxGyro = MGC_MAX_GYRO;
	MotionGC_SetKnobs(&knobs);
}

void __attribute__ ((signal)) algo_00(void)
{
	MGC_input_t data_in;
	MGC_output_t data_out;
	uint8_t bias_update;

	data_in.Acc[0] = cast_sint16_t(ISPU_ARAW_X) * ACC_SENS;
	data_in.Acc[1] = cast_sint16_t(ISPU_ARAW_Y) * ACC_SENS;
	data_in.Acc[2] = cast_sint16_t(ISPU_ARAW_Z) * ACC_SENS;
	data_in.Gyro[0] = cast_sint16_t(ISPU_GRAW_X) * GYR_SENS;
	data_in.Gyro[1] = cast_sint16_t(ISPU_GRAW_Y) * GYR_SENS;
	data_in.Gyro[2] = cast_sint16_t(ISPU_GRAW_Z) * GYR_SENS;

	MotionGC_Update(&data_in, &data_out, &bias_update);

	cast_float(ISPU_DOUT_00) = data_in.Gyro[0] - data_out.GyroBiasX;
	cast_float(ISPU_DOUT_02) = data_in.Gyro[1] - data_out.GyroBiasY;
	cast_float(ISPU_DOUT_04) = data_in.Gyro[2] - data_out.GyroBiasZ;
	cast_float(ISPU_DOUT_06) = data_out.GyroBiasX;
	cast_float(ISPU_DOUT_08) = data_out.GyroBiasY;
	cast_float(ISPU_DOUT_10) = data_out.GyroBiasZ;

	int_status = int_status | 0x1;
}

int main(void)
{
	// set boot done flag
	uint8_t status = cast_uint8_t(ISPU_STATUS);
	status = status | 0x04;
	cast_uint8_t(ISPU_STATUS) = status;

	// enable algorithms interrupt request generation
	cast_uint8_t(ISPU_GLB_CALL_EN) = 0x01;

	while (1) {
		stop_and_wait_start_pulse;

		// reset status registers and interrupts
		int_status = 0;
		cast_uint32_t(ISPU_INT_STATUS) = 0;
		cast_uint8_t(ISPU_INT_PIN) = 0;

		// get all the algorithms to run in this time slot
		cast_uint32_t(ISPU_CALL_EN) = cast_uint32_t(ISPU_ALGO) << 1;

		// wait for all algorithms execution
		while (cast_uint32_t(ISPU_CALL_EN))
			;

		// set status registers and generate interrupts
		cast_uint32_t(ISPU_INT_STATUS) = int_status;
		cast_uint8_t(ISPU_INT_PIN) = (((int_status & cast_uint32_t(ISPU_INT1_CTRL)) > 0) << 0) |
			(((int_status & cast_uint32_t(ISPU_INT2_CTRL)) > 0) << 1);
	}
}

