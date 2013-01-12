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

#ifndef _SAR_H_
#define _SAR_H_

#ifdef RIGHTSHIFT_IS_SAR
#define SAR(b, n)	((b) >> (n))
#else

static inline int8 SAR (const int8 b, const int n)
{
#ifndef RIGHTSHIFT_int8_IS_SAR
	if (b < 0)
		return ((b >> n) | (-1 << (8  - n)));
#endif
	return (b >> n);
}

static inline int16 SAR (const int16 b, const int n)
{
#ifndef RIGHTSHIFT_int16_IS_SAR
	if (b < 0)
		return ((b >> n) | (-1 << (16 - n)));
#endif
	return (b >> n);
}

static inline int32 SAR (const int32 b, const int n)
{
#ifndef RIGHTSHIFT_int32_IS_SAR
	if (b < 0)
		return ((b >> n) | (-1 << (32 - n)));
#endif
	return (b >> n);
}

static inline int64 SAR (const int64 b, const int n)
{
#ifndef RIGHTSHIFT_int64_IS_SAR
	if (b < 0)
		return ((b >> n) | (-1 << (64 - n)));
#endif
	return (b >> n);
}

#endif

#endif
