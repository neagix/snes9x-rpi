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

#ifdef DEBUGGER

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <string>

struct SBreakPoint
{
	bool8	Enabled;
	uint8	Bank;
	uint16	Address;
};

#define ENSURE_TRACE_OPEN(fp, file, mode) \
	if (!fp) \
	{ \
		std::string fn = S9xGetDirectory(LOG_DIR); \
		fn += SLASH_STR file; \
		fp = fopen(fn.c_str(), mode); \
	}

extern struct SBreakPoint	S9xBreakpoint[6];

void S9xDoDebug (void);
void S9xTrace (void);
void S9xSA1Trace (void);
void S9xTraceMessage (const char *);
void S9xTraceFormattedMessage (const char *, ...);
void S9xPrintHVPosition (char *);

#endif

#endif
