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


#ifndef IS9XSOUNDOUTPUT_H
#define IS9XSOUNDOUTPUT_H
#include "../port.h"

/* IS9xSoundOutput
	Interface for the sound output.
*/

class IS9xSoundOutput {
public:
	// InitSoundOutput should initialize the sound output but not start playback
	virtual bool InitSoundOutput(void)=0;

	// DeInitSoundOutput should stop playback and uninitialize the output
	virtual void DeInitSoundOutput(void)=0;

	// SetupSound should apply the current sound settings for outputbuffers/devices and
	// (re)start playback
	virtual bool SetupSound()=0;

	// ProcessSound should call S9xFinalizeSamples and queue new available samples into the
	// Host sound system. If the sound system is callback based, ProcessSound should do a syncronized
	// S9xFinalizeSamples and return.
	virtual void ProcessSound()=0;
};

#endif