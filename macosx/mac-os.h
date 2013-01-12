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


#ifndef _mac_os_h_
#define _mac_os_h_

enum
{
	kDrawingReserved1 = 1, // unused
	kDrawingOpenGL,
	kDrawingBlitGL
};

enum
{
	kWindowControllers = 0,
	kWindowPreferences,
	kWindowAbout,
	kWindowAutoFire,
	kWindowRomInfo,
	kWindowCheatFinder,
	kWindowKeyConfig,
	kWindowCheatEntry,
	kWindowScreen,
	kWindowServer,
	kWindowClient,
	kWindowExtra,
	kWindowSoundEffect,
	kWindowCoreImageFilter,
	kWindowMultiCart,

	kWindowCount
};

enum
{
	SNES_MULTIPLAYER5,
	SNES_MULTIPLAYER5_2,
	SNES_JOYPAD,
	SNES_MOUSE_SWAPPED,
	SNES_MOUSE,
	SNES_SUPERSCOPE,
	SNES_JUSTIFIER,
	SNES_JUSTIFIER_2,
	SNES_MAX_CONTROLLER_OPTIONS
};

enum
{
	VIDEOMODE_BLOCKY,
	VIDEOMODE_TV,
	VIDEOMODE_SMOOTH,
	VIDEOMODE_BLEND,
	VIDEOMODE_SUPEREAGLE,
	VIDEOMODE_2XSAI,
	VIDEOMODE_SUPER2XSAI,
	VIDEOMODE_EPX,
	VIDEOMODE_HQ2X,
	VIDEOMODE_HQ3X,
	VIDEOMODE_HQ4X,
	VIDEOMODE_NTSC_C,
	VIDEOMODE_NTSC_S,
	VIDEOMODE_NTSC_R,
	VIDEOMODE_NTSC_M,
	VIDEOMODE_NTSC_TV_C,
	VIDEOMODE_NTSC_TV_S,
	VIDEOMODE_NTSC_TV_R,
	VIDEOMODE_NTSC_TV_M
};

typedef struct
{
	long long	nextTime[12];
	uint16		buttonMask;
	uint16		toggleMask;
	uint16		tcMask;
	uint16		invertMask;
	SInt32		frequency;
}	AutoFireState;

typedef struct
{
	bool8		benchmark;
	bool8		glForceNoTextureRectangle;
	bool8		glUseClientStrageApple;
	bool8		glUseTexturePriority;
	int			glStorageHint;
}	ExtraOption;

#define kMacWindowHeight	(SNES_HEIGHT_EXTENDED << 1)
#define	MAC_MAX_PLAYERS		8

extern volatile bool8	running, s9xthreadrunning;
extern volatile bool8	eventQueued, windowExtend;
extern volatile int		windowResizeCount;
extern uint32			controlPad[MAC_MAX_PLAYERS];
extern uint8			romDetect, interleaveDetect, videoDetect, headerDetect;
extern WindowRef		gWindow;
extern HIRect			gWindowRect;
extern int				glScreenW, glScreenH;
extern CGRect			glScreenBounds;
extern Point			windowPos[kWindowCount];
extern CGSize			windowSize[kWindowCount];
extern CGImageRef		macIconImage[118];
extern int				macPadIconIndex, macLegendIconIndex, macMusicBoxIconIndex, macFunctionIconIndex;
extern int				macFrameSkip;
extern int32			skipFrames;
extern int64			lastFrame;
extern unsigned long	spcFileCount, pngFileCount;
extern SInt32			systemVersion;
extern bool8			finished, cartOpen,
						autofire, hidExist, directDisplay;
extern bool8			fullscreen, autoRes,
						glstretch, gl32bit, vsync, drawoverscan, lastoverscan, screencurvature,
						multiprocessor, ciFilterEnable;
extern long				drawingMethod;
extern int				videoMode;
extern SInt32			macSoundVolume;
extern uint32			macSoundBuffer_ms, macSoundInterval_ms;
extern bool8			macSoundLagEnable;
extern uint16			aueffect;
extern uint8			saveInROMFolder;
extern CFStringRef		saveFolderPath;
extern int				macCurvatureWarp, macAspectRatio;
extern int				macFastForwardRate, macFrameAdvanceRate;
extern int				inactiveMode;
extern bool8			macQTRecord;
extern uint16			macRecordFlag, macPlayFlag, macQTMovFlag;
extern bool8			startopendlog, showtimeinfrz, enabletoggle, savewindowpos, onscreeninfo;
extern int				musicboxmode;
extern bool8			applycheat;
extern int				padSetting, deviceSetting, deviceSettingMaster;
extern int				macControllerOption;
extern CGPoint			unlimitedCursor;
extern char				npServerIP[256], npName[256];
extern AutoFireState	autofireRec[MAC_MAX_PLAYERS];
extern ExtraOption		extraOptions;
extern CFStringRef		multiCartPath[2];

#ifdef MAC_PANTHER_SUPPORT
extern IconRef			macIconRef[118];
#endif

void InitGameWindow (void);
void DeinitGameWindow (void);
void UpdateGameWindow (void);
void AddRecentItem (FSRef *);
void BuildRecentMenu (void);
void AdjustMenus (void);
void UpdateMenuCommandStatus (Boolean);
void ApplyNSRTHeaderControllers (void);
void QuitWithFatalError (OSStatus, const char *);
void ChangeInputDevice (void);
void GetGameScreenPointer (int16 *, int16 *, bool);
void PostQueueToSubEventLoop (void);
int PromptFreezeDefrost (Boolean);

#endif
