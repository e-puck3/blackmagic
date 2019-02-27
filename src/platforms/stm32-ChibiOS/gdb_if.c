/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2011  Black Sphere Technologies Ltd.
 * Written by Gareth McMullin <gareth@blacksphere.co.nz>
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

/* This file implements a transparent channel over which the GDB Remote
 * Serial Debugging protocol is implemented.  This implementation for STM32
 * uses the USB CDC-ACM device bulk endpoints to implement the channel.
 */
#include "general.h"
#include "gdb_if.h"
#include "usbcfg.h"

static uint32_t count_out;
static uint32_t count_in;
static uint32_t out_ptr;
static uint8_t buffer_out[USB_DATA_SIZE];
static uint8_t buffer_in[USB_DATA_SIZE];
#ifdef STM32F4
//static volatile uint32_t count_new;
//static uint8_t double_buffer_out[USB_DATA_SIZE];
#endif

void gdb_if_putchar(unsigned char c, int flush)
{
	buffer_in[count_in++] = c;
	if(flush || (count_in == USB_DATA_SIZE)) {
		/* Refuse to send if USB isn't configured, and
		 * don't bother if nobody's listening */
		if(( isUSBConfigured() && getControlLineState(GDB_INTERFACE, CONTROL_LINE_DTR)) ) {
			chnWrite((BaseChannel *) &USB_GDB, buffer_in, count_in);
		}
#ifdef USE_SECOND_GDB_INTERFACE
		//send to the second GDB interface if it is active and connected
		if( platform_is_second_gdb_interface_active() && platform_is_second_gdb_interface_connected() ) {
			chnWrite((BaseChannel *) &GDB_2ND_INTERFACE, buffer_in, count_in);
		}
#endif /* USE_SECOND_GDB_INTERFACE */
		count_in = 0;
		return;
	}
}

static void gdb_if_update_buf(uint32_t timeout)
{
#ifdef USE_SECOND_GDB_INTERFACE
	while ( !isUSBConfigured() && !platform_is_second_gdb_interface_connected() ){
#else
	while ( !isUSBConfigured() ){
#endif /* USE_SECOND_GDB_INTERFACE */
		chThdSleepMilliseconds(10);
	}

	count_out = chnReadTimeout((BaseChannel *) &USB_GDB, buffer_out, USB_DATA_SIZE, timeout);

#ifdef USE_SECOND_GDB_INTERFACE
	if(count_out == 0 && platform_is_second_gdb_interface_active() ){
		count_out = chnReadTimeout((BaseChannel *) &GDB_2ND_INTERFACE, buffer_out, USB_DATA_SIZE, timeout);
	}
#endif /* USE_SECOND_GDB_INTERFACE */
	out_ptr = 0;
}

unsigned char gdb_if_getchar(void)
{

	while (!(out_ptr < count_out)) {
		/* Detach if port closed */
#ifdef USE_SECOND_GDB_INTERFACE
		if ( !getControlLineState(GDB_INTERFACE, CONTROL_LINE_DTR) && !platform_is_second_gdb_interface_connected() )
#else
		if ( !getControlLineState(GDB_INTERFACE, CONTROL_LINE_DTR) )
#endif /* USE_SECOND_GDB_INTERFACE */
			return 0x04;

		gdb_if_update_buf(TIME_MS2I(1));
	}

	return buffer_out[out_ptr++];
}

unsigned char gdb_if_getchar_to(int timeout)
{	
	platform_timeout t;
	platform_timeout_set(&t, timeout);

	if (!(out_ptr < count_out)) do {
		/* Detach if port closed */
#ifdef USE_SECOND_GDB_INTERFACE
		if ( !getControlLineState(GDB_INTERFACE, CONTROL_LINE_DTR) && !platform_is_second_gdb_interface_connected() )
#else
		if ( !getControlLineState(GDB_INTERFACE, CONTROL_LINE_DTR) )
#endif /* USE_SECOND_GDB_INTERFACE */
			return 0x04;

		gdb_if_update_buf(TIME_MS2I(1));
	} while (!platform_timeout_is_expired(&t) && !(out_ptr < count_out));

	if(out_ptr < count_out)
		return gdb_if_getchar();

	return -1;
}

