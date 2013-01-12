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

#ifndef _BSX_H_
#define _BSX_H_

struct SBSX
{
	bool8	dirty;			// Changed register values
	bool8	dirty2;			// Changed register values
	bool8	bootup;			// Start in bios mapping
	bool8	flash_enable;	// Flash state
	bool8	write_enable;	// ROM write protection
	bool8	read_enable;	// Allow card vendor reading
	uint32	flash_command;	// Flash command
	uint32	old_write;		// Previous flash write address
	uint32	new_write;		// Current flash write address
	uint8	out_index;
	uint8	output[32];
	uint8	PPU[32];
	uint8	MMC[16];
	uint8	prevMMC[16];
	uint8	test2192[32];
};

extern struct SBSX	BSX;

uint8 S9xGetBSX (uint32);
void S9xSetBSX (uint8, uint32);
uint8 S9xGetBSXPPU (uint16);
void S9xSetBSXPPU (uint8, uint16);
uint8 * S9xGetBasePointerBSX (uint32);
void S9xInitBSX (void);
void S9xResetBSX (void);
void S9xBSXPostLoadState (void);

#endif
