/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2015 Gareth McMullin <gareth@blacksphere.co.nz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "general.h"
#include "morse.h"

#include "ch.h"
#include "hal.h"

static volatile uint32_t time_ms = 0;;

static THD_WORKING_AREA(sys_tick_thd_wa, 128);
static THD_FUNCTION(sys_tick_thd, arg)
{
	(void) arg;

	chRegSetThreadName("Systick emulation GDB");

	uint8_t state = 0;;
	while(1){
		chThdSleepMilliseconds(100);
		state = !state;

		time_ms += 100;

		//SET_ERROR_STATE(morse_update());
	}
}

void platform_timing_init(void)
{
	/* Setup heartbeat timer */
	chThdCreateStatic(sys_tick_thd_wa, sizeof(sys_tick_thd_wa), NORMALPRIO+10, sys_tick_thd, NULL);

}

void platform_delay(uint32_t ms)
{
	chThdSleepMilliseconds(ms);
}

uint32_t platform_time_ms(void)
{
	return time_ms;
}

