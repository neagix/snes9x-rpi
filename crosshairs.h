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

#ifndef _CROSSHAIRS_H_
#define _CROSSHAIRS_H_

// Read in the specified crosshair file, replacing whatever data might be in that slot.
// Available slots are 1-31.
// The input file must be a PNG or a text file. 
// PNG:  15x15 pixels, palettized, with 3 colors (white, black, and transparent).
// text: 15 lines of 16 characters (counting the \n), consisting of ' ', '#', or '.'.

bool S9xLoadCrosshairFile (int idx, const char *filename);

// Return the specified crosshair. Woo-hoo.
// char * to a 225-byte string, with '#' marking foreground, '.' marking background,
// and anything else transparent.

const char * S9xGetCrosshair (int idx);

// In controls.cpp. Sets the crosshair for the specified device. Defaults are:
//                cross   fgcolor    bgcolor
//   Mouse 1:       1     White      Black
//   Mouse 2:       1     Purple     White
//   Superscope:    2     White      Black
//   Justifier 1:   4     Blue       Black
//   Justifier 2:   4     MagicPink  Black
//
// Available colors are: Trans, Black, 25Grey, 50Grey, 75Grey, White, Red, Orange,
// Yellow, Green, Cyan, Sky, Blue, Violet, MagicPink, and Purple.
// You may also prefix a 't' (e.g. tBlue) for a 50%-transparent version.
// Use idx = -1 or fg/bg = NULL to keep the current setting.

enum crosscontrols
{
	X_MOUSE1,
	X_MOUSE2,
	X_SUPERSCOPE,
	X_JUSTIFIER1,
	X_JUSTIFIER2
};

void S9xSetControllerCrosshair (enum crosscontrols ctl, int8 idx, const char *fg, const char *bg);
void S9xGetControllerCrosshair (enum crosscontrols ctl, int8 *idx, const char **fg, const char **bg);

// In gfx.cpp, much like S9xDisplayChar() except it takes the parameters
// listed and looks up GFX.Screen.
// The 'crosshair' arg is a 15x15 image, with '#' meaning fgcolor,
// '.' meaning bgcolor, and anything else meaning transparent.
// Color values should be (RGB):
//  0 = transparent  4 = 23 23 23    8 = 31 31  0   12 =  0  0 31
//  1 =  0  0  0     5 = 31 31 31    9 =  0 31  0   13 = 23  0 31
//  2 =  8  8  8     6 = 31  0  0   10 =  0 31 31   14 = 31  0 31
//  3 = 16 16 16     7 = 31 16  0   11 =  0 23 31   15 = 31  0 16
//  16-31 are 50% transparent versions of 0-15.

void S9xDrawCrosshair (const char *crosshair, uint8 fgcolor, uint8 bgcolor, int16 x, int16 y);

#endif
