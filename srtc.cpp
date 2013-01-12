/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.
  http://www.snes9x.com/

  See CREDITS for copyright and authorship information.
  
  Specific ports contains the works of other authors. See headers in
  individual files.

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
 ***********************************************************************************/
/*****
 * S-RTC emulation code
 * Copyright (c) byuu
 *****/


#include <limits>

#include "snes9x.h"
#include "memmap.h"
#include "srtc.h"
#include "display.h"

#define memory_cartrtc_read(a)		RTCData.reg[(a)]
#define memory_cartrtc_write(a, b)	{ RTCData.reg[(a)] = (b); }
#define cpu_regs_mdr				OpenBus

static inline unsigned max (unsigned a, unsigned b)
{
	return ((a > b) ? a : b);
}

static inline unsigned min (unsigned a, unsigned b)
{
	return ((a < b) ? a : b);
}

#include "srtcemu.h"
#include "srtcemu.cpp"

static SRTC	srtcemu;


void S9xInitSRTC (void)
{
	srtcemu.power();
	memset(RTCData.reg, 0, 20);
}

void S9xResetSRTC (void)
{
	srtcemu.reset();
}

void S9xSetSRTC (uint8 data, uint16 address)
{
	srtcemu.mmio_write(address, data);
}

uint8 S9xGetSRTC (uint16 address)
{
	return (srtcemu.mmio_read(address));
}

void S9xSRTCPreSaveState (void)
{
	srtcsnap.rtc_mode  = (int32) srtcemu.rtc_mode;
	srtcsnap.rtc_index = (int32) srtcemu.rtc_index;
}

void S9xSRTCPostLoadState (int)
{
	srtcemu.rtc_mode  = (SRTC::RTC_Mode) srtcsnap.rtc_mode;
	srtcemu.rtc_index = (signed)         srtcsnap.rtc_index;

	srtcemu.update_time();
}
