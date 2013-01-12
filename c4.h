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

#ifndef _C4_H_
#define _C4_H_

extern int16	C4WFXVal;
extern int16	C4WFYVal;
extern int16	C4WFZVal;
extern int16	C4WFX2Val;
extern int16	C4WFY2Val;
extern int16	C4WFDist;
extern int16	C4WFScale;
extern int16	C41FXVal;
extern int16	C41FYVal;
extern int16	C41FAngleRes;
extern int16	C41FDist;
extern int16	C41FDistVal;

void C4TransfWireFrame (void);
void C4TransfWireFrame2 (void);
void C4CalcWireFrame (void);
void C4Op0D (void);
void C4Op15 (void);
void C4Op1F (void);
void S9xInitC4 (void);
void S9xSetC4 (uint8, uint16);
uint8 S9xGetC4 (uint16);
uint8 * S9xGetBasePointerC4 (uint16);
uint8 * S9xGetMemPointerC4 (uint16);

static inline uint8 * C4GetMemPointer (uint32 Address)
{
	return (Memory.ROM + ((Address & 0xff0000) >> 1) + (Address & 0x7fff));
}

#endif
