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
/***********************************************************************************
  SNES9X for Mac OS (c) Copyright John Stiles

  Snes9x for Mac OS X

  (c) Copyright 2001 - 2011  zones
  (c) Copyright 2002 - 2005  107
  (c) Copyright 2002         PB1400c
  (c) Copyright 2004         Alexander and Sander
  (c) Copyright 2004 - 2005  Steven Seeger
  (c) Copyright 2005         Ryan Vogt
 ***********************************************************************************/


#include "mac-prefix.h"
#include "mac-stringtools.h"


CFStringRef CopyFixNameStrings (const char *itext, uint8 region)
{
	CFStringRef	str = NULL;

	if (region != 0)	// non-Japanese
	{
		char	btext[256];
		size_t	len = strlen(itext);

		btext[len] = 0;
		for (unsigned int i = 0; i < len ; i++)
			btext[i] = isgraph(itext[i]) ? itext[i] : ' ';

		str = CFStringCreateWithCString(kCFAllocatorDefault, btext, kCFStringEncodingNonLossyASCII);
	}
	else
		str = CFStringCreateWithCString(kCFAllocatorDefault, itext, kCFStringEncodingMacJapanese);	// assuming Shift-JIS

	return (str);
}

#ifdef MAC_TIGER_PANTHER_SUPPORT
OSStatus CreateATSUIStyleFromFontFullNameAndSize (const char *fontName, int fontSize, ATSUStyle *theStyle)
{
	OSStatus	err;
	ATSUStyle	localStyle;
	ATSUFontID	atsuFont;
	Fixed		atsuSize;

	ATSUAttributeTag		theTags[]   = { kATSUFontTag,       kATSUSizeTag  };
	ByteCount				theSizes[]  = { sizeof(ATSUFontID), sizeof(Fixed) };
	ATSUAttributeValuePtr	theValues[] = { NULL,                NULL         };

	atsuFont = 0;
	atsuSize = FixRatio(fontSize, 1);
	localStyle = NULL;

	theValues[0] = &atsuFont;
	theValues[1] = &atsuSize;

	err = ATSUFindFontFromName(fontName, strlen(fontName), kFontFullName, kFontNoPlatform, kFontNoScript, kFontNoLanguage, &atsuFont);
	if (err == noErr)
	{
		err = ATSUCreateStyle(&localStyle);
		if (err == noErr)
		{
			err = ATSUSetAttributes(localStyle, sizeof(theTags) / sizeof(theTags[0]), theTags, theSizes, theValues);
			if (err == noErr)
			{
				*theStyle = localStyle;
				return (noErr);
			}
		}
	}

	if (localStyle != NULL)
		err = ATSUDisposeStyle(localStyle);

	return (err);
}
#endif

const char * GetMultiByteCharacters (CFStringRef inText, int cutAt)
{
	static char	buf[256];

	CFStringRef	str;

	buf[0] = 0;

	if (!inText || (cutAt < 1))
		return (buf);

	if (CFStringGetCString(inText, buf, sizeof(buf), CFStringGetSystemEncoding()))
	{
		buf[cutAt] = 0;

		str = CFStringCreateWithCString(kCFAllocatorDefault, buf, CFStringGetSystemEncoding());
		if (str)
			CFRelease(str);
		else
			buf[cutAt - 1] = 0;
	}

	return (buf);
}
