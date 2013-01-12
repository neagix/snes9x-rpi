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

#ifndef CFMOD_H
#define CFMOD_H
#include "fmod.h"
#include "IS9xSoundOutput.h"

class CFMOD: public IS9xSoundOutput
{
	bool initDone;					// has init been called successfully?

	FSOUND_STREAM *fmod_stream;		// the stream object

	int sampleCount;
	int bufferSize;

	bool InitFMOD();
	void DeInitFMOD();

	bool InitStream();
	void DeInitStream();

	void ProcessSound();

	// The FMOD API changed the return type of the stream callback function
	// somewhere between version 3.20 and 3.33. The FMOD API defines a version
	// string but you can't test for that at compile time. Instead, I've picked on
	// a symbol that wasn't defined in version 3.20 to test for the change in API.
	#if !defined (FSOUND_LOADRAW)
	void
	#else
	signed char
	#endif
	static F_CALLBACKAPI FMODStreamCallback (FSOUND_STREAM *stream, void *buff, int len, void *param);

public:
	CFMOD(void);
	~CFMOD(void);

	// Inherited from IS9xSoundOutput
	bool InitSoundOutput(void) { return InitFMOD(); }
	void DeInitSoundOutput(void) { DeInitFMOD(); }
	bool SetupSound(void);
};

#endif