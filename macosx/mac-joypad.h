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


#ifndef _mac_joypad_h_
#define _mac_joypad_h_

enum
{
	kISp1PUp = 0,
	kISp1PDn,
	kISp1PLf,
	kISp1PRt,

	kISp2PUp,
	kISp2PDn,
	kISp2PLf,
	kISp2PRt,

	kISp3PUp,
	kISp3PDn,
	kISp3PLf,
	kISp3PRt,

	kISp4PUp,
	kISp4PDn,
	kISp4PLf,
	kISp4PRt,

	kISp5PUp,
	kISp5PDn,
	kISp5PLf,
	kISp5PRt,

	kISp6PUp,
	kISp6PDn,
	kISp6PLf,
	kISp6PRt,

	kISp7PUp,
	kISp7PDn,
	kISp7PLf,
	kISp7PRt,

	kISp8PUp,
	kISp8PDn,
	kISp8PLf,
	kISp8PRt,

	kISp1PB,
	kISp1PA,
	kISp1PX,
	kISp1PY,
	kISp1PL,
	kISp1PR,
	kISp1PSelect,
	kISp1PStart,

	kISp2PB,
	kISp2PA,
	kISp2PX,
	kISp2PY,
	kISp2PL,
	kISp2PR,
	kISp2PSelect,
	kISp2PStart,

	kISp3PB,
	kISp3PA,
	kISp3PX,
	kISp3PY,
	kISp3PL,
	kISp3PR,
	kISp3PSelect,
	kISp3PStart,

	kISp4PB,
	kISp4PA,
	kISp4PX,
	kISp4PY,
	kISp4PL,
	kISp4PR,
	kISp4PSelect,
	kISp4PStart,

	kISp5PB,
	kISp5PA,
	kISp5PX,
	kISp5PY,
	kISp5PL,
	kISp5PR,
	kISp5PSelect,
	kISp5PStart,

	kISp6PB,
	kISp6PA,
	kISp6PX,
	kISp6PY,
	kISp6PL,
	kISp6PR,
	kISp6PSelect,
	kISp6PStart,

	kISp7PB,
	kISp7PA,
	kISp7PX,
	kISp7PY,
	kISp7PL,
	kISp7PR,
	kISp7PSelect,
	kISp7PStart,

	kISp8PB,
	kISp8PA,
	kISp8PX,
	kISp8PY,
	kISp8PL,
	kISp8PR,
	kISp8PSelect,
	kISp8PStart,

	kISpFastForward,
	kISpFreeze,
	kISpDefrost,
	kISpScreenshot,
	kISpEsc,
	kISpSPC,
	kISpMouseL,
	kISpMouseR,
	kISpScopeT,
	kISpScopeP,
	kISpScopeC,
	kISpOffScreen,
	kISpFunction,
	kISpAlt,
	kISpFFUp,
	kISpFFDown,
	kISpTC,

	kNeedCount
};

void SetUpHID (void);
void ReleaseHID (void);
void ConfigureHID (void);
void ClearPadSetting (void);
void SaveControllerSettings (void);
void LoadControllerSettings (void);
long ISpKeyIsPressed (int);
void JoypadScanDirection (int, uint32 *);

#endif
