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

#ifndef _blit_h_
#define _blit_h_

#include "2xsai.h"
#include "epx.h"
#include "hq2x.h"
#include "snes_ntsc.h"

bool8 S9xBlitFilterInit (void);
void S9xBlitFilterDeinit (void);
void S9xBlitClearDelta (void);
bool8 S9xBlitNTSCFilterInit (void);
void S9xBlitNTSCFilterDeinit (void);
void S9xBlitNTSCFilterSet (const snes_ntsc_setup_t *);
void S9xBlitPixSimple1x1 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixSimple1x2 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixSimple2x1 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixSimple2x2 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixBlend1x1 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixBlend2x1 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixTV1x2 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixTV2x2 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixMixedTV1x2 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixSmooth2x2 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixSuperEagle16 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPix2xSaI16 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixSuper2xSaI16 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixEPX16 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixHQ2x16 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixHQ3x16 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixHQ4x16 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixNTSC16 (uint8 *, int, uint8 *, int, int, int);
void S9xBlitPixHiResNTSC16 (uint8 *, int, uint8 *, int, int, int);

#endif
