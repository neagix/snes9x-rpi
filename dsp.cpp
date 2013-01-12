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

#include "snes9x.h"
#include "memmap.h"
#ifdef DEBUGGER
#include "missing.h"
#endif

uint8	(*GetDSP) (uint16)        = NULL;
void	(*SetDSP) (uint8, uint16) = NULL;


void S9xResetDSP (void)
{
	memset(&DSP1, 0, sizeof(DSP1));
	DSP1.waiting4command = TRUE;
	DSP1.first_parameter = TRUE;

	memset(&DSP2, 0, sizeof(DSP2));
	DSP2.waiting4command = TRUE;

	memset(&DSP3, 0, sizeof(DSP3));
	DSP3_Reset();

	memset(&DSP4, 0, sizeof(DSP4));
	DSP4.waiting4command = TRUE;
}

uint8 S9xGetDSP (uint16 address)
{
#ifdef DEBUGGER
	if (Settings.TraceDSP)
	{
		sprintf(String, "DSP read: 0x%04X", address);
		S9xMessage(S9X_TRACE, S9X_TRACE_DSP1, String);
	}
#endif

	return ((*GetDSP)(address));
}

void S9xSetDSP (uint8 byte, uint16 address)
{
#ifdef DEBUGGER
	missing.unknowndsp_write = address;
	if (Settings.TraceDSP)
	{
		sprintf(String, "DSP write: 0x%04X=0x%02X", address, byte);
		S9xMessage(S9X_TRACE, S9X_TRACE_DSP1, String);
	}
#endif

	(*SetDSP)(byte, address);
}
