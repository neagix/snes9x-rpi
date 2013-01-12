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


#ifndef _mac_dialog_h_
#define _mac_dialog_h_

enum
{
	kS9xMacAlertFolderNotFound = 1,
	kS9xMacAlertFolderNotFoundHint,
	kS9xMacAlertFolderFailToCreate,
	kS9xMacAlertFolderFailToCreateHint,
	kS9xMacAlertkBadRom,
	kS9xMacAlertkBadRomHint,
	kS9xMacAlertCFCantAddEntry,
	kS9xMacAlertCFCantAddEntryHint,
	kS9xMacAlertRequiredSystem,
	kS9xMacAlertRequiredSystemHint
};

extern int	autofireLastTabIndex;

void AboutDialog (void);
void RomInfoDialog (void);
void ConfigureAutofire (void);
void StartCarbonModalDialog (void);
void FinishCarbonModalDialog (void);
void RegisterHelpBook (void);
void MoveWindowPosition (WindowRef, int, Boolean);
void SaveWindowPosition (WindowRef, int);
void AppearanceAlert (AlertType, int, int);
void SetHIViewID (HIViewID *, OSType, SInt32);
OSStatus SetStaticTextCStr (HIViewRef, char *, Boolean);
OSStatus SetStaticTextCFString (HIViewRef, CFStringRef, Boolean);
OSStatus SetStaticTextTrunc (HIViewRef, TruncCode, Boolean);
OSStatus GetEditTextCStr (HIViewRef, char *);
OSStatus SetEditTextCStr (HIViewRef, char *, Boolean);
OSStatus CopyEditTextCFString (HIViewRef, CFStringRef *);
OSStatus SetEditTextCFString (HIViewRef, CFStringRef, Boolean);
OSStatus SetEditTextSelection (HIViewRef, SInt16, SInt16);
pascal OSStatus DefaultEventHandler (EventHandlerCallRef, EventRef, void *);

#endif
