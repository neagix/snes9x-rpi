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

#ifndef CXHAUDIO2_H
#define CXAUDIO2_H
#include "XAudio2.h"
#include "../snes9x.h"
#include <windows.h>
#include "IS9xSoundOutput.h"

class CXAudio2 : public IXAudio2VoiceCallback, public IS9xSoundOutput
{
private:
	IXAudio2SourceVoice *pSourceVoice;
	IXAudio2 *pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;

	bool initDone;							// has init been called successfully?

	volatile LONG bufferCount;				// currently submitted XAudio2 buffers

	UINT32 sum_bufferSize;					// the size of soundBuffer
	UINT32 singleBufferSamples;				// samples in one block
	UINT32 singleBufferBytes;				// bytes in one block
	UINT32 blockCount;						// soundBuffer is divided into blockCount blocks
											// currently set to 4

	UINT32 writeOffset;						// offset into the buffer for the next block
	uint8 *soundBuffer;						// the buffer itself

	bool InitVoices(void);
	void DeInitVoices(void);

	void PushBuffer(UINT32 AudioBytes,BYTE *pAudioData,void *pContext);	
	void BeginPlayback(void);
	void StopPlayback(void);
	void ProcessSound(void);
	bool InitXAudio2(void);
	void DeInitXAudio2(void);

public:
	CXAudio2(void);
	~CXAudio2(void);
		
	// inherited from IXAudio2VoiceCallback - we only use OnBufferEnd
	STDMETHODIMP_(void) OnBufferEnd(void *pBufferContext);
	STDMETHODIMP_(void) OnBufferStart(void *pBufferContext){}
	STDMETHODIMP_(void) OnLoopEnd(void *pBufferContext){}
	STDMETHODIMP_(void) OnStreamEnd() {}
	STDMETHODIMP_(void) OnVoiceError(void *pBufferContext, HRESULT Error) {}
	STDMETHODIMP_(void) OnVoiceProcessingPassEnd() {}
	STDMETHODIMP_(void) OnVoiceProcessingPassStart(UINT32 BytesRequired) {}


	// Inherited from IS9xSoundOutput
	bool InitSoundOutput(void) { return InitXAudio2(); }
	void DeInitSoundOutput(void) { DeInitXAudio2(); }
	bool SetupSound(void);
};

#endif