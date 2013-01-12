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


// CDirectSound.h: interface for the CDirectSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(DIRECTSOUND_H_INCLUDED)
#define DIRECTSOUND_H_INCLUDED

#include <windows.h>
#include "IS9xSoundOutput.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDirectSound : public IS9xSoundOutput
{
private:
	LPDIRECTSOUND lpDS;
	LPDIRECTSOUNDBUFFER lpDSB;				// the buffer used for mixing
	LPDIRECTSOUNDBUFFER lpDSBPrimary;

	int blockCount;							// number of blocks in the buffer
	int blockSize;							// bytes in one block
	int blockSamples;						// samples in one block
	int bufferSize;							// bytes in the whole buffer
	int blockTime;							// ms in one block

	DWORD last_block;						// the last block that was mixed

	bool initDone;							// has init been called successfully?
	DWORD hTimer;							// mixing timer
	
	bool InitDirectSound ();
	void DeInitDirectSound();

	bool InitSoundBuffer();
	void DeInitSoundBuffer();

	static VOID CALLBACK SoundTimerCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	
	void ProcessSound();
	void MixSound();

public:
	CDirectSound();
	~CDirectSound();

	// Inherited from IS9xSoundOutput
	bool InitSoundOutput(void) { return InitDirectSound(); }
	void DeInitSoundOutput(void) { DeInitDirectSound(); }
	bool SetupSound(void);
	
};

extern CDirectSound DirectSound;

#endif // !defined(DIRECTSOUND_H_INCLUDED)
