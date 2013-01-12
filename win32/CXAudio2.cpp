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

#include "CXAudio2.h"
#include "../snes9x.h"
#include "../apu/apu.h"
#include "wsnes9x.h"
#include <process.h>
#include <Dxerr.h>

/* CXAudio2
	Implements audio output through XAudio2.
	Basic idea: one master voice and one source voice are created;
	the source voice consumes buffers queued by PushBuffer, plays them through
	the master voice and calls OnBufferEnd after each buffer.
	ProcessSound copies new samples into the buffer and queues them for playback.
*/

/*  Construction/Destruction
*/
CXAudio2::CXAudio2(void)
{
	pXAudio2 = NULL;
	pSourceVoice = NULL;
	pMasterVoice = NULL;

	sum_bufferSize = singleBufferBytes \
		= singleBufferSamples = blockCount = 0;
	soundBuffer = NULL;
	initDone = false;
}

CXAudio2::~CXAudio2(void)
{
	DeInitXAudio2();
}

/*  CXAudio2::InitXAudio2
initializes the XAudio2 object
-----
returns true if successful, false otherwise
*/
bool CXAudio2::InitXAudio2(void)
{
	if(initDone)
		return true;

	HRESULT hr;
	if ( FAILED(hr = XAudio2Create( &pXAudio2, 0 , XAUDIO2_DEFAULT_PROCESSOR ) ) ) {
		DXTRACE_ERR_MSGBOX(TEXT("Unable to create XAudio2 object."),hr);
		MessageBox (GUI.hWnd, TEXT("\
Unable to initialize XAudio2. You will not be able to hear any\n\
sound effects or music while playing.\n\n\
This is usually caused by not having a recent DirectX release installed."),
			TEXT("Snes9X - Unable to Initialize XAudio2"),
            MB_OK | MB_ICONWARNING);
		return false;
	}
	initDone = true;
	return true;
}

/*  CXAudio2::InitVoices
initializes the voice objects with the current audio settings
-----
returns true if successful, false otherwise
*/
bool CXAudio2::InitVoices(void)
{
	HRESULT hr;
	if ( FAILED(hr = pXAudio2->CreateMasteringVoice( &pMasterVoice, (Settings.Stereo?2:1),
		Settings.SoundPlaybackRate, 0, 0 , NULL ) ) ) {
			DXTRACE_ERR_MSGBOX(TEXT("Unable to create mastering voice."),hr);
			return false;
	}

	WAVEFORMATEX wfx;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = Settings.Stereo ? 2 : 1;
    wfx.nSamplesPerSec = Settings.SoundPlaybackRate;
    wfx.nBlockAlign = (Settings.SixteenBitSound ? 2 : 1) * (Settings.Stereo ? 2 : 1);
    wfx.wBitsPerSample = Settings.SixteenBitSound ? 16 : 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
    wfx.cbSize = 0;

	if( FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx,
		XAUDIO2_VOICE_NOSRC , XAUDIO2_DEFAULT_FREQ_RATIO, this, NULL, NULL ) ) ) {
			DXTRACE_ERR_MSGBOX(TEXT("Unable to create source voice."),hr);
			return false;
	}

	return true;
}

/*  CXAudio2::DeInitXAudio2
deinitializes all objects
*/
void CXAudio2::DeInitXAudio2(void)
{
	initDone = false;
	DeInitVoices();	
	if(pXAudio2) {
		pXAudio2->Release();
		pXAudio2 = NULL;
	}
}

/*  CXAudio2::DeInitVoices
deinitializes the voice objects and buffers
*/
void CXAudio2::DeInitVoices(void)
{
	if(pSourceVoice) {
		StopPlayback();
		pSourceVoice->DestroyVoice();
		pSourceVoice = NULL;
	}
	if(pMasterVoice) {
		pMasterVoice->DestroyVoice();
		pMasterVoice = NULL;
	}
	if(soundBuffer) {
		delete [] soundBuffer;
		soundBuffer = NULL;
	}
}

/*  CXAudio2::OnBufferEnd
callback function called by the source voice
IN:
pBufferContext		-	unused
*/
void CXAudio2::OnBufferEnd(void *pBufferContext)
{
	InterlockedDecrement(&bufferCount);
    SetEvent(GUI.SoundSyncEvent);
}

/*  CXAudio2::PushBuffer
pushes one buffer onto the source voice playback queue
IN:
AudioBytes		-	size of the buffer
pAudioData		-	pointer to the buffer
pContext		-	context passed to the callback, currently unused
*/
void CXAudio2::PushBuffer(UINT32 AudioBytes,BYTE *pAudioData,void *pContext)
{
	XAUDIO2_BUFFER xa2buffer={0};
	xa2buffer.AudioBytes=AudioBytes;
	xa2buffer.pAudioData=pAudioData;
	xa2buffer.pContext=pContext;
	InterlockedIncrement(&bufferCount);
	pSourceVoice->SubmitSourceBuffer(&xa2buffer);
}

/*  CXAudio2::SetupSound
applies current sound settings by recreating the voice objects and buffers
-----
returns true if successful, false otherwise
*/
bool CXAudio2::SetupSound()
{
	if(!initDone)
		return false;

	DeInitVoices();

	blockCount = 8;
	UINT32 blockTime = GUI.SoundBufferSize / blockCount;

	singleBufferSamples = (Settings.SoundPlaybackRate * blockTime * (Settings.Stereo ? 2 : 1)) / 1000;
	singleBufferBytes = singleBufferSamples * (Settings.SixteenBitSound ? 2 : 1);
	sum_bufferSize = singleBufferBytes * blockCount;

    if (InitVoices())
    {
		soundBuffer = new uint8[sum_bufferSize];
		writeOffset = 0;
    }
	else {
		DeInitVoices();
		return false;
	}

	bufferCount = 0;

	BeginPlayback();

    return true;
}

void CXAudio2::BeginPlayback()
{
	pSourceVoice->Start(0);
}

void CXAudio2::StopPlayback()
{
	pSourceVoice->Stop(0);
}

/*  CXAudio2::ProcessSound
The mixing function called by the sound core when new samples are available.
SoundBuffer is divided into blockCount blocks. If there are enought available samples and a free block,
the block is filled and queued to the source voice. bufferCount is increased by pushbuffer and decreased by
the OnBufferComplete callback.
*/
void CXAudio2::ProcessSound()
{
	S9xFinalizeSamples();

	if(!initDone)
		return;

	BYTE * curBuffer;

	UINT32 availableSamples;
	UINT32 availableBytes;

	availableSamples = S9xGetSampleCount();
	availableBytes = availableSamples * (Settings.SixteenBitSound ? 2 : 1);

	while(availableSamples > singleBufferSamples && bufferCount < blockCount) {
		curBuffer = soundBuffer + writeOffset;
		S9xMixSamples(curBuffer,singleBufferSamples);
		PushBuffer(singleBufferBytes,curBuffer,NULL);
		writeOffset+=singleBufferBytes;
		writeOffset%=sum_bufferSize;
	}
}
