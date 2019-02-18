/**
 * @file	platform.h
 * @brief  	Used to make the link between the blackmagic files and the ChibiOS project.
 * 
 * @written by  	Eliot Ferragni
 * @creation date	15.02.2019
 */

#ifndef __PLATFORM_H
#define __PLATFORM_H

#include <ch.h>
#include <hal.h>

#include "gdb.h"

/**
 * Blackmagic wrappers
 */


#include "gpio.h"
#include "timing.h"
#include "timing_stm32.h"

#define USB_NAME "Blackmagic probe"

#define NOT_USED	0
#define JTAG_PORT 	
#define TDI_PORT	NOT_USED
#define TMS_PORT	NOT_USED
#define TCK_PORT	NOT_USED
#define TDO_PORT	NOT_USED
#define TDI_PIN		NOT_USED
#define TMS_PIN		NOT_USED
#define TCK_PIN		NOT_USED
#define TDO_PIN		NOT_USED

#define SWDIO_PORT 	NOT_USED
#define SWCLK_PORT 	NOT_USED
#define SWDIO_PIN	NOT_USED
#define SWCLK_PIN	NOT_USED

#define TRST_PORT	NOT_USED
#define TRST_PIN	NOT_USED
#define SRST_PORT	NOT_USED
#define SRST_PIN	NOT_USED

#define LED_PORT_ERROR		NOT_USED //RED_LED
#define LED_PORT_UART		NOT_USED //BLUE_LED
#define LED_PORT			NOT_USED //GREEN_LED


#define LED_ERROR		NOT_USED	
#define LED_UART		NOT_USED	
#define LED_IDLE_RUN	NOT_USED	
#define LED_BOOTLOADER	NOT_USED

#define TMS_SET_MODE() {palSetPadMode(TMS_PORT, SWDIO_PIN, PAL_MODE_OUTPUT_PUSHPULL);}

#define SWDIO_MODE_FLOAT() {palSetPadMode(SWDIO_PORT, SWDIO_PIN, PAL_MODE_INPUT);}

#define SWDIO_MODE_DRIVE() {palSetPadMode(SWDIO_PORT, SWDIO_PIN, PAL_MODE_OUTPUT_PUSHPULL);}

#define DEBUG(...)

#define SET_RUN_STATE(state)	{gdbSetFlag(state ? RUNNING_FLAG : IDLE_FLAG);};
#define SET_PROGRAMMING_STATE()	{gdbSetFlag(PROGRAMMING_FLAG);};
#define SET_IDLE_STATE(state)	{};
#define SET_ERROR_STATE(state)	{gdbSetFlag(ERROR_FLAG);};

static inline int platform_hwversion(void)
{
	return 0;
}

/* Use newlib provided integer only stdio functions */
#define sscanf siscanf
#define sprintf siprintf
#define vasprintf vasiprintf
#define snprintf sniprintf

#endif /* __PLATFORM_H */