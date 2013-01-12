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



// CDirectDraw.h: interface for the CDirectDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CDIRECTDRAW_H_INCLUDED)
#define CDIRECTDRAW_H_INCLUDED

#include "IS9xDisplayOutput.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDirectDraw: public IS9xDisplayOutput
{
public:	
	HRESULT dErr;
	LPDIRECTDRAW lpDD;
	LPDIRECTDRAWCLIPPER lpDDClipper;
	LPDIRECTDRAWPALETTE lpDDPalette;

	LPDIRECTDRAWSURFACE2 lpDDSPrimary2;
	LPDIRECTDRAWSURFACE2 lpDDSOffScreen2;

	RECT SizeHistory [10];

	int width, height;
	char depth;
	bool doubleBuffered;
	bool clipped;
	bool dDinitialized;

	unsigned char *convertBuffer;
	unsigned int filterScale;

	DDPIXELFORMAT DDPixelFormat;
public:
	bool SetDisplayMode(
		int pWidth, int pHeight, int pScale,
		char pDepth, int pRefreshRate, bool pWindowed,
		bool pDoubleBuffered);
    void GetPixelFormat ();
	void DeInitialize();
	bool Initialize (HWND hWnd);

	void Render(SSurface Src);
	bool ApplyDisplayChanges(void);
	bool ChangeRenderSize(unsigned int newWidth, unsigned int newHeight);
	bool SetFullscreen(bool fullscreen);
	void SetSnes9xColorFormat();

	void EnumModes(std::vector<dMode> *modeVector);

	CDirectDraw();
	virtual ~CDirectDraw();
};

#endif // !defined(CDIRECTDRAW_H_INCLUDED)
