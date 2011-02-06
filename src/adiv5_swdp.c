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

/* This file implements the SW-DP specific functions of the 
 * ARM Debug Interface v5 Architecure Specification, ARM doc IHI0031A.
 */

#include "general.h"
#include "platform.h"
#include "adiv5.h"

#include "swdptap.h"

#include "command.h"

#include <stdlib.h>

#define SWDP_ACK_OK    0x01
#define SWDP_ACK_WAIT  0x02
#define SWDP_ACK_FAULT 0x04

static void adiv5_swdp_write(ADIv5_DP_t *dp, uint8_t addr, uint32_t value);
static uint32_t adiv5_swdp_read(ADIv5_DP_t *dp, uint8_t addr);

static void adiv5_swdp_write_ap(ADIv5_DP_t *dp, uint8_t addr, uint32_t value);
static uint32_t adiv5_swdp_read_ap(ADIv5_DP_t *dp, uint8_t addr);

static uint32_t adiv5_swdp_error(ADIv5_DP_t *dp);

static uint32_t adiv5_swdp_low_access(ADIv5_DP_t *dp, uint8_t APnDP, uint8_t RnW, 
				      uint8_t addr, uint32_t value);


int adiv5_swdp_scan(void)
{
	ADIv5_DP_t *dp;
	uint8_t ack;

	TARGET_LIST_FREE();
	dp = (void*)calloc(1, sizeof(ADIv5_DP_t));

	swdptap_init();
	/* Read the SW-DP IDCODE register to syncronise */
	/* This could be done with adiv_swdp_low_access(), but this doesn't
	 * allow the ack to be checked here. */
	swdptap_seq_out(0b10100101, 8);
	ack = swdptap_seq_in(3);
	if((ack != SWDP_ACK_OK) || swdptap_seq_in_parity(&dp->idcode, 32)) {
		DEBUG("\n");
		morse("NO TARGETS.", 1);
		free(dp);
		return -1;
	}

	dp->dp_write = adiv5_swdp_write;
	dp->dp_read = adiv5_swdp_read;
	dp->ap_write = adiv5_swdp_write_ap;
	dp->ap_read = adiv5_swdp_read_ap;
	dp->error = adiv5_swdp_error;
	dp->low_access = adiv5_swdp_low_access;

	adiv5_dp_init(dp);

	if(!target_list) morse("NO TARGETS.", 1);
	else morse(NULL, 0);

	return target_list?1:0;
}

static void adiv5_swdp_write(ADIv5_DP_t *dp, uint8_t addr, uint32_t value)
{
	adiv5_swdp_low_access(dp, 0, 0, addr, value);
}

static uint32_t adiv5_swdp_read(ADIv5_DP_t *dp, uint8_t addr)
{
	return adiv5_swdp_low_access(dp, 0, 1, addr, 0);
}

static void adiv5_swdp_write_ap(ADIv5_DP_t *dp, uint8_t addr, uint32_t value)
{
	adiv5_swdp_low_access(dp, 1, 0, addr, value);
}

static uint32_t adiv5_swdp_read_ap(ADIv5_DP_t *dp, uint8_t addr)
{
	uint32_t ret;

	adiv5_swdp_low_access(dp, 1, 1, addr, 0);
	ret = adiv5_swdp_low_access(dp, 0, 1, DP_RDBUFF, 0);

	return ret;
}

static uint32_t adiv5_swdp_error(ADIv5_DP_t *dp)
{
	uint32_t err, clr = 0;

	err = adiv5_swdp_read(dp, DP_CTRLSTAT) & 0x32;

	if(err & 0x02) clr |= 0x10; /* STICKORUN */
	if(err & 0x10) clr |= 0x02; /* STICKCMP */
	if(err & 0x20) clr |= 0x04; /* STICKERR */

	adiv5_swdp_write(dp, DP_ABORT, clr);
	dp->fault = 0;

	return err;
}

static uint32_t adiv5_swdp_low_access(ADIv5_DP_t *dp, uint8_t APnDP, uint8_t RnW, 
				      uint8_t addr, uint32_t value)
{
	uint8_t request =  0b10000001;
	uint32_t response;
	uint8_t ack;

	if(APnDP && dp->fault) return 0;

	if(APnDP) request ^= 0b100010;
	if(RnW)   request ^= 0b100100;

	addr &= 0xC;
	request |= (addr << 1) & 0b11000;
	if((addr == 4) || (addr == 8))
		request ^= 0b100000;

	do {
		swdptap_seq_out(request, 8);
		ack = swdptap_seq_in(3);
	} while(ack == SWDP_ACK_WAIT);

	if(ack == SWDP_ACK_FAULT) {
		dp->fault = 1;
		return 0;
	}

	if(ack != SWDP_ACK_OK) {
		/* Fatal error if invalid ACK response */
		PLATFORM_FATAL_ERROR(1);
	}

	if(RnW) {
		if(swdptap_seq_in_parity(&response, 32))  /* Give up on parity error */
			PLATFORM_FATAL_ERROR(1);
	} else {
		swdptap_seq_out_parity(value, 32);
	}

	/* REMOVE THIS */
	swdptap_seq_out(0, 8);

	return response;
}

