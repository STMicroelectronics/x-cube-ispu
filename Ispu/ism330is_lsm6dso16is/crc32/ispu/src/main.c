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

#include "crc32.h"

static volatile uint32_t int_status;

void __attribute__ ((signal)) algo_00_init(void)
{
	crc32_init();
}

void __attribute__ ((signal)) algo_00(void)
{
	int16_t data[6];
	uint32_t crc32;

	data[0] = cast_sint16_t(ISPU_ARAW_X);
	data[1] = cast_sint16_t(ISPU_ARAW_Y);
	data[2] = cast_sint16_t(ISPU_ARAW_Z);
	data[3] = cast_sint16_t(ISPU_GRAW_X);
	data[4] = cast_sint16_t(ISPU_GRAW_Y);
	data[5] = cast_sint16_t(ISPU_GRAW_Z);

	crc32 = crc32_run((uint8_t *)data, 12);

	cast_sint16_t(ISPU_DOUT_00) = data[0];
	cast_sint16_t(ISPU_DOUT_01) = data[1];
	cast_sint16_t(ISPU_DOUT_02) = data[2];
	cast_sint16_t(ISPU_DOUT_03) = data[3];
	cast_sint16_t(ISPU_DOUT_04) = data[4];
	cast_sint16_t(ISPU_DOUT_05) = data[5];
	cast_uint32_t(ISPU_DOUT_06) = crc32;

	int_status = int_status | 0x0001;
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

