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



/*
  Win32 AVI Output module
  (c) 2004 blip
*/

#ifndef __AVIOUTPUT_H_
#define __AVIOUTPUT_H_

#ifdef __cplusplus
extern "C" {
#endif

// create a new avi output object
void AVICreate(struct AVIFile** avi_out);

// set up avi output options
void AVISetFramerate(const int fps, const int frameskip, struct AVIFile* avi_out);
void AVISetVideoFormat(const BITMAPINFOHEADER* bitmap_format, struct AVIFile* avi_out);
void AVISetSoundFormat(const WAVEFORMATEX* wave_format, struct AVIFile* avi_out);

// after setting up output options, start writing with this
// returns 1 if successful, 0 otherwise
// check the return value!
int AVIBegin(const TCHAR* filename, struct AVIFile* avi_out);

// get the format in use from an already existing avi output object
// returns 1 if successful, 0 otherwise
int AVIGetVideoFormat(const struct AVIFile* avi_out, const BITMAPINFOHEADER** ppFormat);
int AVIGetSoundFormat(const struct AVIFile* avi_out, const WAVEFORMATEX** ppFormat);

// write video frames and sound samples to an avi output object
// that's been successfully Begun()
void AVIAddVideoFrame(void* bitmap_data, struct AVIFile* avi_out);
void AVIAddSoundSamples(void* sound_data, const int num_samples, struct AVIFile* avi_out);

// when done writing, close and delete the object with this
void AVIClose(struct AVIFile** avi_out);

#ifdef __cplusplus
}
#endif

#endif /* __AVIOUTPUT_H_ */
