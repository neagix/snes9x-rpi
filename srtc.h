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

#ifndef _SRTC_H_
#define _SRTC_H_

struct SRTCData
{
	uint8	reg[20];
};

// for snapshot only
struct SSRTCSnapshot
{
	int32	rtc_mode;	// enum RTC_Mode
	int32	rtc_index;	// signed
};

extern struct SRTCData		RTCData;
extern struct SSRTCSnapshot	srtcsnap;

void S9xInitSRTC (void);
void S9xResetSRTC (void);
void S9xSRTCPreSaveState (void);
void S9xSRTCPostLoadState (int);
void S9xSetSRTC (uint8, uint16);
uint8 S9xGetSRTC (uint16);

#endif
