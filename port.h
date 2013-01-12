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

#ifndef _PORT_H_
#define _PORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#ifndef __LIBRETRO__
#include <memory.h>
#endif
#include <time.h>
#include <string.h>
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#include <sys/types.h>

#ifdef __WIN32__
#define NOMINMAX
#include <windows.h>
#endif

#define GFX_MULTI_FORMAT

#ifdef __WIN32__
//#define RIGHTSHIFT_IS_SAR
#define RIGHTSHIFT_int8_IS_SAR
#define RIGHTSHIFT_int16_IS_SAR
#define RIGHTSHIFT_int32_IS_SAR
#ifndef __WIN32_LIBSNES__
#define SNES_JOY_READ_CALLBACKS
#endif //__WIN32_LIBSNES__
#endif

#ifdef __MACOSX__
#undef GFX_MULTI_FORMAT
#define PIXEL_FORMAT RGB555
#endif

#ifndef snes9x_types_defined
#define snes9x_types_defined
typedef unsigned char		bool8;
#ifdef HAVE_STDINT_H
#include <stdint.h>
typedef intptr_t			pint;
typedef int8_t				int8;
typedef uint8_t				uint8;
typedef int16_t				int16;
typedef uint16_t			uint16;
typedef int32_t				int32;
typedef uint32_t			uint32;
typedef int64_t				int64;
typedef uint64_t			uint64;
#else	// HAVE_STDINT_H
#ifdef __WIN32__
typedef intptr_t			pint;
typedef signed char			int8;
typedef unsigned char		uint8;
typedef signed short		int16;
typedef unsigned short		uint16;
typedef signed int     		int32;
typedef unsigned int		uint32;
typedef signed __int64		int64;
typedef unsigned __int64	uint64;
typedef int8                int8_t;
typedef uint8       		uint8_t;
typedef int16       		int16_t;
typedef uint16      		uint16_t;
typedef int32		    	int32_t;
typedef uint32      		uint32_t;
typedef int64               int64_t;
typedef uint64              uint64_t;
typedef int					socklen_t;
#else	// __WIN32__
typedef signed char			int8;
typedef unsigned char		uint8;
typedef signed short		int16;
typedef unsigned short		uint16;
typedef signed int			int32;
typedef unsigned int		uint32;
#ifdef __GNUC__
// long long is not part of ISO C++ 
__extension__
#endif
typedef long long			int64;
typedef unsigned long long	uint64;
#ifdef PTR_NOT_INT
typedef long				pint;
#else   // __PTR_NOT_INT
typedef int					pint;
#endif  // __PTR_NOT_INT
#endif	//  __WIN32__
#endif	// HAVE_STDINT_H
#endif	// snes9x_types_defined

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

#define START_EXTERN_C	extern "C" {
#define END_EXTERN_C	}

#ifndef __WIN32__
#ifndef PATH_MAX
#define PATH_MAX	1024
#endif
#define _MAX_DRIVE	1
#define _MAX_DIR	PATH_MAX
#define _MAX_FNAME	PATH_MAX
#define _MAX_EXT	PATH_MAX
#define _MAX_PATH	PATH_MAX
#else
#ifndef PATH_MAX
#define PATH_MAX	_MAX_PATH
#endif
#endif

#ifndef __WIN32__
void _splitpath (const char *, char *, char *, char *, char *);
void _makepath (char *, const char *, const char *, const char *, const char *);
#define S9xDisplayString	DisplayStringFromBottom
#else   // __WIN32__
#define snprintf _snprintf
#define strcasecmp	stricmp
#define strncasecmp	strnicmp
#ifndef __WIN32_LIBSNES__
void WinDisplayStringFromBottom(const char *string, int linesFromBottom, int pixelsFromLeft, bool allowWrap);
#define S9xDisplayString	WinDisplayStringFromBottom
void SetInfoDlgColor(unsigned char, unsigned char, unsigned char);
#define SET_UI_COLOR(r,g,b) SetInfoDlgColor(r,g,b)
#else   // __WIN32_LIBSNES__
#define S9xDisplayString	DisplayStringFromBottom
#endif  // __WIN32_LIBSNES__
#endif  // __WIN32__

#ifdef __DJGPP
#define SLASH_STR	"\\"
#define SLASH_CHAR	'\\'
#else
#define SLASH_STR	"/"
#define SLASH_CHAR	'/'
#endif

#ifndef SIG_PF
#define SIG_PF	void (*) (int)
#endif

#ifdef __linux
#define TITLE "Snes9x: Linux"
#define SYS_CONFIG_FILE "/etc/snes9x/snes9x.conf"
#endif

#ifndef TITLE
#define TITLE "Snes9x"
#endif

#if defined(__arm__) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__x86_64__) || defined(__alpha__) || defined(__MIPSEL__) || defined(_M_IX86) || defined(_M_X64) || defined(_XBOX1)
// little endian
#define LSB_FIRST
#define FAST_LSB_WORD_ACCESS
#else
// big endian
#define MSB_FIRST
#endif

#ifdef FAST_LSB_WORD_ACCESS
#define READ_WORD(s)		(*(uint16 *) (s))
#define READ_3WORD(s)		(*(uint32 *) (s) & 0x00ffffff)
#define READ_DWORD(s)		(*(uint32 *) (s))
#define WRITE_WORD(s, d)	*(uint16 *) (s) = (d)
#define WRITE_3WORD(s, d)	*(uint16 *) (s) = (uint16) (d), *((uint8 *) (s) + 2) = (uint8) ((d) >> 16)
#define WRITE_DWORD(s, d)	*(uint32 *) (s) = (d)
#else
#define READ_WORD(s)		(*(uint8 *) (s) | (*((uint8 *) (s) + 1) << 8))
#define READ_3WORD(s)		(*(uint8 *) (s) | (*((uint8 *) (s) + 1) << 8) | (*((uint8 *) (s) + 2) << 16))
#define READ_DWORD(s)		(*(uint8 *) (s) | (*((uint8 *) (s) + 1) << 8) | (*((uint8 *) (s) + 2) << 16) | (*((uint8 *) (s) + 3) << 24))
#define WRITE_WORD(s, d)	*(uint8 *) (s) = (uint8) (d), *((uint8 *) (s) + 1) = (uint8) ((d) >> 8)
#define WRITE_3WORD(s, d)	*(uint8 *) (s) = (uint8) (d), *((uint8 *) (s) + 1) = (uint8) ((d) >> 8), *((uint8 *) (s) + 2) = (uint8) ((d) >> 16)
#define WRITE_DWORD(s, d)	*(uint8 *) (s) = (uint8) (d), *((uint8 *) (s) + 1) = (uint8) ((d) >> 8), *((uint8 *) (s) + 2) = (uint8) ((d) >> 16), *((uint8 *) (s) + 3) = (uint8) ((d) >> 24)
#endif

#define SWAP_WORD(s)		(s) = (((s) & 0xff) <<  8) | (((s) & 0xff00) >> 8)
#define SWAP_DWORD(s)		(s) = (((s) & 0xff) << 24) | (((s) & 0xff00) << 8) | (((s) & 0xff0000) >> 8) | (((s) & 0xff000000) >> 24)

#include "pixform.h"

#endif
