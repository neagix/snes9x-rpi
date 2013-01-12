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

#ifdef FMOD_SUPPORT
#include "CFMOD.h"
#include "../snes9x.h"
#include "../apu/apu.h"
#include "wsnes9x.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

/*  Construction/Destruction
*/
CFMOD::CFMOD(void)
{
	initDone = false;
	fmod_stream = NULL;
}

CFMOD::~CFMOD(void)
{
	DeInitFMOD();
}

/*  CFMOD::InitStream
initializes FMOD and the output stream that will call our callback function
-----
returns true if successful, false otherwise
*/
bool CFMOD::InitStream()
{
    if (!FSOUND_Init (Settings.SoundPlaybackRate, 16, 0))
    {
        MessageBox (GUI.hWnd, "\
Unable to initialise FMOD sound system. You will not be able to hear\n\
any sound effects or music while playing.\n\n\
It is usually caused by not having DirectX installed or another\n\
application that has already opened DirectSound in exclusive\n\
mode or the Windows WAVE device has been opened.",
                    "Snes9X - Unable to Open FMOD",
                    MB_OK | MB_ICONWARNING);
			DeInitStream();
			return false;
    }

	sampleCount = (Settings.SoundPlaybackRate * GUI.SoundBufferSize/2 ) / 1000;
    if (Settings.Stereo)
		sampleCount *= 2;
	bufferSize = sampleCount * (Settings.SixteenBitSound?2:1);
	fmod_stream = FSOUND_Stream_Create (FMODStreamCallback, bufferSize,
                                        FSOUND_LOOP_OFF |
                                        FSOUND_STREAMABLE |
                                        FSOUND_SIGNED |
                                        FSOUND_LOOP_NORMAL |
                                        (Settings.SixteenBitSound ?
                                           FSOUND_16BITS : FSOUND_8BITS) |
                                        (Settings.Stereo ?
                                           FSOUND_STEREO : FSOUND_MONO),
                                        Settings.SoundPlaybackRate, (void *)this);

	if (!fmod_stream ||
            FSOUND_Stream_Play (FSOUND_FREE, fmod_stream) == -1)
	{
            MessageBox (GUI.hWnd, "\
Unable to create or play an FMOD sound stream. You will not be able\n\
to hear any sound effects or music while playing.",
                        "Snes9X - Unable to Open FMOD",
                        MB_OK | MB_ICONWARNING);
			DeInitStream();
			return false;
	}
	return true;
}

/*  CFMOD::DeInitStream
stops playback and closes the stream
*/
void CFMOD::DeInitStream()
{
	if (fmod_stream)
    {
        FSOUND_StopSound (0);
        FSOUND_Stream_Stop (fmod_stream);
        FSOUND_Stream_Close (fmod_stream);
        FSOUND_Close ();
        fmod_stream = NULL;
    }
}

/*  CFMOD::InitFMOD
sets the sound driver to be used by FMOD
-----
returns true if successful, false otherwise
*/
bool CFMOD::InitFMOD()
{
	if(initDone)
		return true;

    switch (GUI.SoundDriver)
    {
        default:
        case WIN_FMOD_DIRECT_SOUND_DRIVER:
            FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);
            break;
        case WIN_FMOD_WAVE_SOUND_DRIVER:
            FSOUND_SetOutput(FSOUND_OUTPUT_WINMM);
            break;
        case WIN_FMOD_A3D_SOUND_DRIVER:
            FSOUND_SetOutput(FSOUND_OUTPUT_A3D);
            break;
    }

    FSOUND_SetDriver(0);

	initDone = true;
	return true;
}

void CFMOD::DeInitFMOD()
{
	DeInitStream();
}

/*  CFMOD::SetupSound
applies current sound settings by recreating the stream
-----
returns true if successful, false otherwise
*/
bool CFMOD::SetupSound()
{

	DeInitStream();
	if(!InitStream()) {
		return false;
	}

	return true;
}

/*  CFMOD::ProcessSound
Finishes core sample creation, syncronizes the buffer access.
*/
void CFMOD::ProcessSound()
{
	EnterCriticalSection(&GUI.SoundCritSect);

	S9xFinalizeSamples();

	LeaveCriticalSection(&GUI.SoundCritSect);
}

/*  CFMOD::FMODStreamCallback
the callback that mixes into the stream
synchronizes the buffer access with a critical section
IN:
stream		-	the stream object, unused
buff		-	the buffer to mix into
len			-	number of bytes in the buffer
param		-	pointer to the CFMOD object
*/

// The FMOD API changed the return type of the stream callback function
// somewhere between version 3.20 and 3.33. The FMOD API defines a version
// string but you can't test for that at compile time. Instead, I've picked on
// a symbol that wasn't defined in version 3.20 to test for the change in API.
#if !defined (FSOUND_LOADRAW)
void
#else
signed char
#endif
F_CALLBACKAPI CFMOD::FMODStreamCallback (FSOUND_STREAM *stream, void *buff, int len, void *param)
{
	CFMOD *S9xFMOD=(CFMOD *)param;
	int sample_count = Settings.SixteenBitSound?len>>1:len;

	EnterCriticalSection(&GUI.SoundCritSect);

	S9xMixSamples((unsigned char *) buff, sample_count);

	LeaveCriticalSection(&GUI.SoundCritSect);

    SetEvent(GUI.SoundSyncEvent);

		

#if defined (FSOUND_LOADRAW)
    return (1);
#endif
}

#endif
