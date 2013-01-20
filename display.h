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

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

enum s9x_getdirtype
{
	DEFAULT_DIR = 0,
	HOME_DIR,
	ROMFILENAME_DIR,
	ROM_DIR,
	SRAM_DIR,
	SNAPSHOT_DIR,
	SCREENSHOT_DIR,
	SPC_DIR,
	CHEAT_DIR,
	IPS_DIR,
	BIOS_DIR,
	LOG_DIR,
	LAST_DIR
};

void S9xUsage (void);
char * S9xParseArgs (char **, int);
void S9xLoadConfigFiles (char **, int);
void S9xSetInfoString (const char *);

// Routines the port has to implement even if it doesn't use them

void S9xPutImage (int, int);
bool S9xInitDisplay (int, char **);
void S9xDeinitDisplay (void);
void S9xTextMode (void);
void S9xGraphicsMode (void);
void S9xSetPalette (void);
void S9xToggleSoundChannel (int);
bool8 S9xOpenSnapshotFile (const char *, bool8, STREAM *);
void S9xCloseSnapshotFile (STREAM);
const char * S9xStringInput (const char *);
const char * S9xGetDirectory (enum s9x_getdirtype);
const char * S9xGetFilename (const char *, enum s9x_getdirtype);
const char * S9xGetFilenameInc (const char *, enum s9x_getdirtype);
const char * S9xChooseFilename (bool8);
const char * S9xBasename (const char *);

// Routines the port has to implement if it uses command-line

void S9xExtraUsage (void);
void S9xParseArg (char **, int &, int);

// Routines the port may implement as needed

void S9xExtraDisplayUsage (void);
void S9xParseDisplayArg (char **, int &, int);
void S9xSetTitle (const char *);
void S9xInitInputDevices (void);
void S9xProcessEvents (bool8);
const char * S9xSelectFilename (const char *, const char *, const char *, const char *);

#endif
