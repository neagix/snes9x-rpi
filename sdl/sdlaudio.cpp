/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  See CREDITS file to find the copyright owners of this file.

  SDL Input/Audio/Video code (many lines of code come from snes9x & drnoksnes)
  (c) Copyright 2011         Makoto Sugano (makoto.sugano@gmail.com)

  Snes9x homepage: http://www.snes9x.com/

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

#define HAVE_SDL 1

#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#include "port.h"
#include "wapu/soundux.h"

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#include <sys/stat.h>
#include <sys/types.h>

#include "snes9x.h"
#include "memmap.h"
#include "wapu/apu.h"
#include "gfx.h"
#include "snapshot.h"
#include "controls.h"
#include "cheats.h"
#include "movie.h"
#include "logger.h"
#include "display.h"
#include "conffile.h"
#include <cmath>

#ifdef DEBUGGER
#include "debug.h"
#endif

#include <SDL/SDL.h>
//#include "sdl_snes9x.h"

SDL_AudioSpec *audiospec;
//uint32 sound_buffer_size;

void S9xToggleSoundChannel(int c) {
    static uint8 sound_switch = 255;

    if (c == 8)
        sound_switch = 255;
    else
        sound_switch ^= 1 << c;

    S9xSetSoundControl(sound_switch);
}

static void
sdl_audio_callback(void *userdata, Uint8 *stream, int len) {
    SDL_LockAudio();
//    printf("[SDL] Filling out %d samples\n", len);
    S9xMixSamples(stream, len >> (Settings.SixteenBitSound ? 1 : 0));
    SDL_UnlockAudio();
}

void create_tone( void *userdata, Uint8 *stream, int len ) {
  static double angle = 0.0 ;
  int i = 0 ;
  fprintf( stderr, "Filling %d\n", len ) ;
  for(i=0;i<len;i++) {
    *stream++ = 128*cos(angle) ; // I think that this should be 128 * cos(angle) as cos is (-1,1)
    angle += 3.14159/100 ;       // and a Uint8 is only 8 bits (256 values)
    if( angle > 2.0*3.14159 ) {
      angle -= 2.0*3.14159 ;
    }
  }
}


void S9xLandSamples() {
/*    SDL_LockAudio();
    S9xFinalizeSamples();
    SDL_UnlockAudio(); */
}

bool8 S9xOpenSoundDevice(void) {
    SDL_InitSubSystem(SDL_INIT_AUDIO);

    audiospec = (SDL_AudioSpec *) malloc(sizeof (SDL_AudioSpec));

    audiospec->freq = Settings.SoundPlaybackRate;
    audiospec->channels = Settings.Stereo ? 2 : 1;
    audiospec->format = Settings.SixteenBitSound ? AUDIO_S16SYS : AUDIO_U8;
    audiospec->samples = (so.buffer_size * audiospec->freq / 1000) >> 1;
    audiospec->callback = sdl_audio_callback;
//        audiospec->callback = create_tone;
    
    // neagix: TODO: use buffer size, somewhere

    printf("SDL sound driver initializing...\n");
    printf("    --> (Frequency: %dhz, Latency: %dms)...",
            audiospec->freq,
            (audiospec->samples * 1000 / audiospec->freq) << 1);

    if (SDL_OpenAudio(audiospec, NULL) < 0) {
        printf("Failed\n");

        free(audiospec);
        audiospec = NULL;

        return FALSE;
    }

    printf("OK\n");

    SDL_PauseAudio(0);

    //	S9xSetSamplesAvailableCallback (samples_available, NULL);

    return (TRUE);
}

bool8 S9xInitSound(bool8 stereo) {
    //    so.sound_fd = -1;
    so.sound_switch = 255;

    so.playback_rate = 0;
    // neagix: set, although never used!
//    so.buffer_size = buffer_size;
    so.stereo = stereo;
    so.sixteen_bit = Settings.SixteenBitSound;
    so.encoded = FALSE;

    S9xResetSound(TRUE);

    //    if (!(mode & 7))
    //	return (1);

    S9xSetSoundMute(TRUE);
    if (!S9xOpenSoundDevice()) {
        S9xMessage(S9X_ERROR, S9X_SOUND_DEVICE_OPEN_FAILED,
                "Sound device open failed");
        return (0);
    }

    return (1);
}