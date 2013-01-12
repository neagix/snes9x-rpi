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

#ifndef _SNAPSHOT_H_
#define _SNAPSHOT_H_

#define SNAPSHOT_MAGIC			"#!s9xsnp"
#define SNAPSHOT_VERSION_IRQ    7
#define SNAPSHOT_VERSION_BAPU   8
#define SNAPSHOT_VERSION		8

#define SUCCESS					1
#define WRONG_FORMAT			(-1)
#define WRONG_VERSION			(-2)
#define FILE_NOT_FOUND			(-3)
#define WRONG_MOVIE_SNAPSHOT	(-4)
#define NOT_A_MOVIE_SNAPSHOT	(-5)
#define SNAPSHOT_INCONSISTENT	(-6)

void S9xResetSaveTimer (bool8);
bool8 S9xFreezeGame (const char *);
uint32 S9xFreezeSize (void);
bool8 S9xFreezeGameMem (uint8 *,uint32);
bool8 S9xUnfreezeGame (const char *);
int S9xUnfreezeGameMem (const uint8 *,uint32);
void S9xFreezeToStream (STREAM);
int	 S9xUnfreezeFromStream (STREAM);

#endif
