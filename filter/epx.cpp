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

#include "snes9x.h"
#include "epx.h"


void EPX_16 (uint8 *srcPtr, int srcRowBytes, uint8 *dstPtr, int dstRowBytes, int width, int height)
{
	uint16	colorX, colorA, colorB, colorC, colorD;
	uint16	*sP, *uP, *lP;
	uint32	*dP1, *dP2;
	int		w;

	height -= 2;

	//   D
	// A X C
	//   B

	// top edge

	sP  = (uint16 *) srcPtr;
	lP  = (uint16 *) (srcPtr + srcRowBytes);
	dP1 = (uint32 *) dstPtr;
	dP2 = (uint32 *) (dstPtr + dstRowBytes);

	// left edge

	colorX = *sP;
	colorC = *++sP;
	colorB = *lP++;

	if ((colorX != colorC) && (colorB != colorX))
	{
	#ifdef MSB_FIRST
		*dP1 = (colorX << 16) + colorX;
		*dP2 = (colorX << 16) + ((colorB == colorC) ? colorB : colorX);
	#else
		*dP1 = colorX + (colorX << 16);
		*dP2 = colorX + (((colorB == colorC) ? colorB : colorX) << 16);
	#endif
	}
	else
		*dP1 = *dP2 = (colorX << 16) + colorX;

	dP1++;
	dP2++;

	//

	for (w = width - 2; w; w--)
	{
		colorA = colorX;
		colorX = colorC;
		colorC = *++sP;
		colorB = *lP++;

		if ((colorA != colorC) && (colorB != colorX))
		{
		#ifdef MSB_FIRST
			*dP1 = (colorX << 16) + colorX;
			*dP2 = (((colorA == colorB) ? colorA : colorX) << 16) + ((colorB == colorC) ? colorB : colorX);
		#else
			*dP1 = colorX + (colorX << 16);
			*dP2 = ((colorA == colorB) ? colorA : colorX) + (((colorB == colorC) ? colorB : colorX) << 16);
		#endif
		}
		else
			*dP1 = *dP2 = (colorX << 16) + colorX;

		dP1++;
		dP2++;
	}

	// right edge

	colorA = colorX;
	colorX = colorC;
	colorB = *lP;

	if ((colorA != colorX) && (colorB != colorX))
	{
	#ifdef MSB_FIRST
		*dP1 = (colorX << 16) + colorX;
		*dP2 = (((colorA == colorB) ? colorA : colorX) << 16) + colorX;
	#else
		*dP1 = colorX + (colorX << 16);
		*dP2 = ((colorA == colorB) ? colorA : colorX) + (colorX << 16);
	#endif
	}
	else
		*dP1 = *dP2 = (colorX << 16) + colorX;

	srcPtr += srcRowBytes;
	dstPtr += dstRowBytes << 1;

	//

	for (; height; height--)
	{
		sP  = (uint16 *) srcPtr;
		uP  = (uint16 *) (srcPtr - srcRowBytes);
		lP  = (uint16 *) (srcPtr + srcRowBytes);
		dP1 = (uint32 *) dstPtr;
		dP2 = (uint32 *) (dstPtr + dstRowBytes);

		// left edge

		colorX = *sP;
		colorC = *++sP;
		colorB = *lP++;
		colorD = *uP++;

		if ((colorX != colorC) && (colorB != colorD))
		{
		#ifdef MSB_FIRST
			*dP1 = (colorX << 16) + ((colorC == colorD) ? colorC : colorX);
			*dP2 = (colorX << 16) + ((colorB == colorC) ? colorB : colorX);
		#else
			*dP1 = colorX + (((colorC == colorD) ? colorC : colorX) << 16);
			*dP2 = colorX + (((colorB == colorC) ? colorB : colorX) << 16);
		#endif
		}
		else
			*dP1 = *dP2 = (colorX << 16) + colorX;

		dP1++;
		dP2++;

		//

		for (w = width - 2; w; w--)
		{
			colorA = colorX;
			colorX = colorC;
			colorC = *++sP;
			colorB = *lP++;
			colorD = *uP++;

			if ((colorA != colorC) && (colorB != colorD))
			{
			#ifdef MSB_FIRST
				*dP1 = (((colorD == colorA) ? colorD : colorX) << 16) + ((colorC == colorD) ? colorC : colorX);
				*dP2 = (((colorA == colorB) ? colorA : colorX) << 16) + ((colorB == colorC) ? colorB : colorX);
			#else
				*dP1 = ((colorD == colorA) ? colorD : colorX) + (((colorC == colorD) ? colorC : colorX) << 16);
				*dP2 = ((colorA == colorB) ? colorA : colorX) + (((colorB == colorC) ? colorB : colorX) << 16);
			#endif
			}
			else
				*dP1 = *dP2 = (colorX << 16) + colorX;

			dP1++;
			dP2++;
		}

		// right edge

		colorA = colorX;
		colorX = colorC;
		colorB = *lP;
		colorD = *uP;

		if ((colorA != colorX) && (colorB != colorD))
		{
		#ifdef MSB_FIRST
			*dP1 = (((colorD == colorA) ? colorD : colorX) << 16) + colorX;
			*dP2 = (((colorA == colorB) ? colorA : colorX) << 16) + colorX;
		#else
			*dP1 = ((colorD == colorA) ? colorD : colorX) + (colorX << 16);
			*dP2 = ((colorA == colorB) ? colorA : colorX) + (colorX << 16);
		#endif
		}
		else
			*dP1 = *dP2 = (colorX << 16) + colorX;

		srcPtr += srcRowBytes;
		dstPtr += dstRowBytes << 1;
	}

	// bottom edge

	sP  = (uint16 *) srcPtr;
	uP  = (uint16 *) (srcPtr - srcRowBytes);
	dP1 = (uint32 *) dstPtr;
	dP2 = (uint32 *) (dstPtr + dstRowBytes);

	// left edge

	colorX = *sP;
	colorC = *++sP;
	colorD = *uP++;

	if ((colorX != colorC) && (colorX != colorD))
	{
	#ifdef MSB_FIRST
		*dP1 = (colorX << 16) + ((colorC == colorD) ? colorC : colorX);
		*dP2 = (colorX << 16) + colorX;
	#else
		*dP1 = colorX + (((colorC == colorD) ? colorC : colorX) << 16);
		*dP2 = colorX + (colorX << 16);
	#endif
	}
	else
		*dP1 = *dP2 = (colorX << 16) + colorX;

	dP1++;
	dP2++;

	//

	for (w = width - 2; w; w--)
	{
		colorA = colorX;
		colorX = colorC;
		colorC = *++sP;
		colorD = *uP++;

		if ((colorA != colorC) && (colorX != colorD))
		{
		#ifdef MSB_FIRST
			*dP1 = (((colorD == colorA) ? colorD : colorX) << 16) + ((colorC == colorD) ? colorC : colorX);
			*dP2 = (colorX << 16) + colorX;
		#else
			*dP1 = ((colorD == colorA) ? colorD : colorX) + (((colorC == colorD) ? colorC : colorX) << 16);
			*dP2 = colorX + (colorX << 16);
		#endif
		}
		else
			*dP1 = *dP2 = (colorX << 16) + colorX;

		dP1++;
		dP2++;
	}

	// right edge

	colorA = colorX;
	colorX = colorC;
	colorD = *uP;

	if ((colorA != colorX) && (colorX != colorD))
	{
	#ifdef MSB_FIRST
		*dP1 = (((colorD == colorA) ? colorD : colorX) << 16) + colorX;
		*dP2 = (colorX << 16) + colorX;
	#else
		*dP1 = ((colorD == colorA) ? colorD : colorX) + (colorX << 16);
		*dP2 = colorX + (colorX << 16);
	#endif
	}
	else
		*dP1 = *dP2 = (colorX << 16) + colorX;
}
