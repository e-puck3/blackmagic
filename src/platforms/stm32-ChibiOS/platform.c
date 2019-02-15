/**
 * @file	platform.c
 * @brief  	Used to make the link between the blackmagic files and the e-puck2_programmer files.
 * 
 * @written by  	Eliot Ferragni
 * @creation date	18.06.2018
 */

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "gdb_packet.h"

//////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

void platform_srst_set_val(bool assert)
{
	if (assert) {
		gpio_clear(SRST_PORT, SRST_PIN);
		chThdSleepMilliseconds(1);
	} else {
		gpio_set(SRST_PORT, SRST_PIN);
	}
}

bool platform_srst_get_val(void)
{
	return gpio_get(SRST_PORT, SRST_PIN) == 0;
}

const char *platform_target_voltage(void)
{
	return "ABSENT!";
}
