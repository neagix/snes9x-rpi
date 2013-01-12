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

#ifndef _FXEMU_H_
#define _FXEMU_H_

#define FX_BREAKPOINT				(-1)
#define FX_ERROR_ILLEGAL_ADDRESS	(-2)

// The FxInfo_s structure, the link between the FxEmulator and the Snes Emulator
struct FxInfo_s
{
	uint32	vFlags;
	uint8	*pvRegisters;	// 768 bytes located in the memory at address 0x3000
	uint32	nRamBanks;		// Number of 64kb-banks in GSU-RAM/BackupRAM (banks 0x70-0x73)
	uint8	*pvRam;			// Pointer to GSU-RAM
	uint32	nRomBanks;		// Number of 32kb-banks in Cart-ROM
	uint8	*pvRom;			// Pointer to Cart-ROM
	uint32	speedPerLine;
	bool8	oneLineDone;
};

extern struct FxInfo_s	SuperFX;

void S9xInitSuperFX (void);
void S9xResetSuperFX (void);
void S9xSuperFXExec (void);
void S9xSetSuperFX (uint8, uint16);
uint8 S9xGetSuperFX (uint16);
void fx_flushCache (void);
void fx_computeScreenPointers (void);
uint32 fx_run (uint32);

#endif
