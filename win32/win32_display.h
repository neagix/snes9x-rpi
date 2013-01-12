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
#ifndef WIN32_DISPLAY_H
#define WIN32_DISPLAY_H

#include "wsnes9x.h"
#include "port.h"
#include "render.h"
#include <vector>

#define IsHiRes(x) ((x.Height > SNES_HEIGHT_EXTENDED || x.Width == 512))
#define CurrentScale (IsHiRes(Src) ? GUI.ScaleHiRes : GUI.Scale)

void WinRefreshDisplay(void);
void S9xSetWinPixelFormat ();
void SwitchToGDI();
void SaveMainWinPos();
void RestoreMainWinPos();
void ToggleFullScreen ();
void RestoreGUIDisplay ();
void RestoreSNESDisplay ();
void WinChangeWindowSize(unsigned int newWidth, unsigned int newHeight);
bool WinDisplayReset(void);
void WinDisplayApplyChanges();
RECT CalculateDisplayRect(unsigned int sourceWidth,unsigned int sourceHeight,
						  unsigned int displayWidth,unsigned int displayHeight);
void WinEnumDisplayModes(std::vector<dMode> *modeVector);
void ConvertDepth (SSurface *src, SSurface *dst, RECT *srect);
void WinDisplayStringFromBottom (const char *string, int linesFromBottom, int pixelsFromLeft, bool allowWrap);
void WinSetCustomDisplaySurface(void *screen, int ppl, int width, int height, int scale);
template<typename screenPtrType>
void WinDisplayStringInBuffer (const char *string, int linesFromBottom, int pixelsFromLeft, bool allowWrap);
char *ReadShaderFileContents(const TCHAR *filename);

#endif
