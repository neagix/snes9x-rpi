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
/***********************************************************************************
  SNES9X for Mac OS (c) Copyright John Stiles

  Snes9x for Mac OS X

  (c) Copyright 2001 - 2011  zones
  (c) Copyright 2002 - 2005  107
  (c) Copyright 2002         PB1400c
  (c) Copyright 2004         Alexander and Sander
  (c) Copyright 2004 - 2005  Steven Seeger
  (c) Copyright 2005         Ryan Vogt
 ***********************************************************************************/


#ifndef _mac_snes9x_h_
#define _mac_snes9x_h_

enum
{
	kAutoROMType       = 0,
	kLoROMForce        = 2,
	kHiROMForce        = 3
};

enum
{
	kAutoInterleave    = 0,
	kNoInterleaveForce = 2,
	kInterleaveForce   = 3,
	kInterleave2Force  = 4,
	kInterleaveGD24    = 5
};

enum
{
	kAutoVideo         = 0,
	kPALForce          = 2,
	kNTSCForce         = 3
};

enum
{
	kAutoHeader        = 0,
	kNoHeaderForce     = 2,
	kHeaderForce       = 3
};

void SNES9X_Go (void);
void SNES9X_LoadSRAM (void);
void SNES9X_SaveSRAM (void);
void SNES9X_Reset (void);
void SNES9X_SoftReset (void);
void SNES9X_Quit (void);
void SNES9X_InitSound (void);
bool8 SNES9X_OpenCart (FSRef *);
bool8 SNES9X_OpenMultiCart (void);
bool8 SNES9X_Freeze (void);
bool8 SNES9X_FreezeTo (void);
bool8 SNES9X_Defrost (void);
bool8 SNES9X_DefrostFrom (void);
bool8 SNES9X_RecordMovie (void);
bool8 SNES9X_PlayMovie (void);
bool8 SNES9X_QTMovieRecord (void);

#endif
