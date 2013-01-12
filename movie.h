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

#ifndef _MOVIE_H_
#define _MOVIE_H_

#define MOVIE_OPT_FROM_SNAPSHOT		0
#define MOVIE_OPT_FROM_RESET		(1 << 0)
#define MOVIE_OPT_PAL				(1 << 1)
#define MOVIE_OPT_NOSAVEDATA		(1 << 2)
#define MOVIE_SYNC_DATA_EXISTS		0x01
#define MOVIE_SYNC_OBSOLETE			0x02
#define MOVIE_SYNC_VOLUMEENVX		0x08
#define MOVIE_SYNC_FAKEMUTE			0x10
#define MOVIE_SYNC_HASROMINFO		0x40
#define MOVIE_SYNC_NOCPUSHUTDOWN	0x80
#define MOVIE_MAX_METADATA			512

#define CONTROLLER_DATA_SIZE		2
#define MOUSE_DATA_SIZE				5
#define SCOPE_DATA_SIZE				6
#define JUSTIFIER_DATA_SIZE			11

struct MovieInfo
{
	time_t	TimeCreated;
	uint32	Version;
	uint32	LengthFrames;
	uint32	LengthSamples;
	uint32	RerecordCount;
	uint8	Opts;
	uint8	ControllersMask;
	uint8	SyncFlags;
	bool8	ReadOnly;
	uint8	PortType[2];
	wchar_t	Metadata[MOVIE_MAX_METADATA];
	uint32	ROMCRC32;
	char	ROMName[23];
};

// methods used by the user-interface code
int S9xMovieOpen (const char *, bool8);
int S9xMovieCreate (const char *, uint8, uint8, const wchar_t *, int);
int S9xMovieGetInfo (const char *, struct MovieInfo *);
void S9xMovieStop (bool8);
void S9xMovieToggleRecState (void);
void S9xMovieToggleFrameDisplay (void);
const char * S9xChooseMovieFilename (bool8);

// methods used by the emulation
void S9xMovieInit (void);
void S9xMovieShutdown (void);
void S9xMovieUpdate (bool a = true);
void S9xMovieUpdateOnReset (void);
void S9xUpdateFrameCounter (int o = 0);
void S9xMovieFreeze (uint8 **, uint32 *);
int S9xMovieUnfreeze (uint8 *, uint32);

// accessor functions
bool8 S9xMovieActive (void);
bool8 S9xMoviePlaying (void);
bool8 S9xMovieRecording (void);
bool8 S9xMovieReadOnly (void);
uint8 S9xMovieControllers (void);
uint32 S9xMovieGetId (void);
uint32 S9xMovieGetLength (void);
uint32 S9xMovieGetFrameCounter (void);

uint16 MovieGetJoypad (int);
void MovieSetJoypad (int, uint16);
bool MovieGetMouse (int, uint8 d[MOUSE_DATA_SIZE]);
void MovieSetMouse (int, uint8 d[MOUSE_DATA_SIZE], bool);
bool MovieGetScope (int, uint8 d[SCOPE_DATA_SIZE]);
void MovieSetScope (int, uint8 d[SCOPE_DATA_SIZE]);
bool MovieGetJustifier (int, uint8 d[JUSTIFIER_DATA_SIZE]);
void MovieSetJustifier (int, uint8 d[JUSTIFIER_DATA_SIZE]);

#endif
