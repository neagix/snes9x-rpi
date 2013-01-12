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

#include "snes9x.h"
#include "movie.h"
#include "logger.h"

static int	resetno = 0;
static int	framecounter = 0;
static FILE	*video = NULL;
static FILE	*audio = NULL;


void S9xResetLogger (void)
{
	if (!Settings.DumpStreams)
		return;

	char	buffer[128];

	S9xCloseLogger();
	framecounter = 0;

	sprintf(buffer, "videostream%d.dat", resetno);
	video = fopen(buffer, "wb");
	if (!video)
	{
		printf("Opening %s failed. Logging cancelled.\n", buffer);
		return;
	}

	sprintf(buffer, "audiostream%d.dat", resetno);
	audio = fopen(buffer, "wb");
	if (!audio)
	{
		printf("Opening %s failed. Logging cancelled.\n", buffer);
		fclose(video);
		return;
	}

	resetno++;
}

void S9xCloseLogger (void)
{
	if (video)
	{
		fclose(video);
		video = NULL;
	}

	if (audio)
	{
		fclose(audio);
		audio = NULL;
	}
}	

void S9xVideoLogger (void *pixels, int width, int height, int depth, int bytes_per_line)
{
	int	fc = S9xMovieGetFrameCounter();
	if (fc > 0)
		framecounter = fc;
	else
		framecounter++;

	if (video)
	{
		char	*data = (char *) pixels;
		size_t	ignore;

		for (int i = 0; i < height; i++)
			ignore = fwrite(data + i * bytes_per_line, depth, width, video);
		fflush(video);
		fflush(audio);

		if (Settings.DumpStreamsMaxFrames > 0 && framecounter >= Settings.DumpStreamsMaxFrames)
		{
			printf("Logging ended.\n");
			S9xCloseLogger();
		}

	}
}

void S9xAudioLogger (void *samples, int length)
{
	if (audio)
	{
		size_t	ignore;
		ignore = fwrite(samples, 1, length, audio);
	}
}
