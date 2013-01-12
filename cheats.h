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

#ifndef _CHEATS_H_
#define _CHEATS_H_

#define MAX_CHEATS	150

struct SCheat
{
	uint32	address;
	uint8	byte;
	uint8	saved_byte;
	bool8	enabled;
	bool8	saved;
	char	name[22];
};

struct SCheatData
{
	struct SCheat c[MAX_CHEATS];
	uint32	num_cheats;
	uint8	CWRAM[0x20000];
	uint8	CSRAM[0x10000];
	uint8	CIRAM[0x2000];
	uint8	*RAM;
	uint8	*FillRAM;
	uint8	*SRAM;
	uint32	ALL_BITS[0x32000 >> 5];
	uint8	CWatchRAM[0x32000];
};

struct Watch
{
	bool	on;
	int		size;
	int		format;
	uint32	address;
	char	buf[12];
	char	desc[32];
};

typedef enum
{
	S9X_LESS_THAN,
	S9X_GREATER_THAN,
	S9X_LESS_THAN_OR_EQUAL,
	S9X_GREATER_THAN_OR_EQUAL,
	S9X_EQUAL,
	S9X_NOT_EQUAL
}	S9xCheatComparisonType;

typedef enum
{
	S9X_8_BITS,
	S9X_16_BITS,
	S9X_24_BITS,
	S9X_32_BITS
}	S9xCheatDataSize;

extern SCheatData	Cheat;
extern Watch		watches[16];

void S9xApplyCheat (uint32);
void S9xApplyCheats (void);
void S9xRemoveCheat (uint32);
void S9xRemoveCheats (void);
void S9xDeleteCheat (uint32);
void S9xDeleteCheats (void);
void S9xEnableCheat (uint32);
void S9xDisableCheat (uint32);
void S9xAddCheat (bool8, bool8, uint32, uint8);
void S9xInitCheatData (void);
void S9xInitWatchedAddress (void);
bool8 S9xLoadCheatFile (const char *);
bool8 S9xSaveCheatFile (const char *);

void S9xStartCheatSearch (SCheatData *);
void S9xSearchForChange (SCheatData *, S9xCheatComparisonType, S9xCheatDataSize, bool8, bool8);
void S9xSearchForValue (SCheatData *, S9xCheatComparisonType, S9xCheatDataSize, uint32, bool8, bool8);
void S9xSearchForAddress (SCheatData *, S9xCheatComparisonType, S9xCheatDataSize, uint32, bool8);
void S9xOutputCheatSearchResults (SCheatData *);

const char * S9xGameGenieToRaw (const char *, uint32 &, uint8 &);
const char * S9xProActionReplayToRaw (const char *, uint32 &, uint8 &);
const char * S9xGoldFingerToRaw (const char *, uint32 &, bool8 &, uint8 &, uint8 bytes[3]);

#endif
