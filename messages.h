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

#ifndef _MESSAGES_H_
#define _MESSAGES_H_

// Types of message sent to S9xMessage()
enum
{
	S9X_TRACE,
	S9X_DEBUG,
	S9X_WARNING,
	S9X_INFO,
	S9X_ERROR,
	S9X_FATAL_ERROR
};

// Individual message numbers
enum
{
	S9X_ROM_INFO,
	S9X_HEADERS_INFO,
	S9X_CONFIG_INFO,
	S9X_ROM_CONFUSING_FORMAT_INFO,
	S9X_ROM_INTERLEAVED_INFO,
	S9X_SOUND_DEVICE_OPEN_FAILED,
	S9X_APU_STOPPED,
	S9X_USAGE,
	S9X_GAME_GENIE_CODE_ERROR,
	S9X_ACTION_REPLY_CODE_ERROR,
	S9X_GOLD_FINGER_CODE_ERROR,
	S9X_DEBUG_OUTPUT,
	S9X_DMA_TRACE,
	S9X_HDMA_TRACE,
	S9X_WRONG_FORMAT,
	S9X_WRONG_VERSION,
	S9X_ROM_NOT_FOUND,
	S9X_FREEZE_FILE_NOT_FOUND,
	S9X_PPU_TRACE,
	S9X_TRACE_DSP1,
	S9X_FREEZE_ROM_NAME,
	S9X_HEADER_WARNING,
	S9X_NETPLAY_NOT_SERVER,
	S9X_FREEZE_FILE_INFO,
	S9X_TURBO_MODE,
	S9X_SOUND_NOT_BUILT,
	S9X_MOVIE_INFO,
	S9X_WRONG_MOVIE_SNAPSHOT,
	S9X_NOT_A_MOVIE_SNAPSHOT,
	S9X_SNAPSHOT_INCONSISTENT,
	S9X_AVI_INFO
};

#endif
