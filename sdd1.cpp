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
#include "sdd1.h"
#include "display.h"


void S9xSetSDD1MemoryMap (uint32 bank, uint32 value)
{
	bank = 0xc00 + bank * 0x100;
	value = value * 1024 * 1024;

	for (int c = 0; c < 0x100; c += 16)
	{
		uint8	*block = &Memory.ROM[value + (c << 12)];
		for (int i = c; i < c + 16; i++)
			Memory.Map[i + bank] = block;
	}
}

void S9xResetSDD1 (void)
{
	memset(&Memory.FillRAM[0x4800], 0, 4);
	for (int i = 0; i < 4; i++)
	{
		Memory.FillRAM[0x4804 + i] = i;
		S9xSetSDD1MemoryMap(i, i);
	}
}

void S9xSDD1PostLoadState (void)
{
	for (int i = 0; i < 4; i++)
		S9xSetSDD1MemoryMap(i, Memory.FillRAM[0x4804 + i]);
}
