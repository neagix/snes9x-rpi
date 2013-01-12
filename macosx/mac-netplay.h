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


#ifndef _mac_netplay_h_
#define _mac_netplay_h_

#define	WRITE_LONG(p, v) \
{ \
	*((p) + 0) = (uint8) ((v) >> 24); \
	*((p) + 1) = (uint8) ((v) >> 16); \
	*((p) + 2) = (uint8) ((v) >>  8); \
	*((p) + 3) = (uint8) ((v) >>  0); \
}

#define	WRITE_BYTE(p, v) \
{ \
	*(p) = (uint8) (v); \
}

#define READ_LONG(p) \
( \
	(((uint8) *((p) + 0)) << 24) | \
 	(((uint8) *((p) + 1)) << 16) | \
 	(((uint8) *((p) + 2)) <<  8) | \
 	(((uint8) *((p) + 3)) <<  0) \
)

#define READ_BYTE(p) \
( \
	(uint8) *(p) \
)

//#define SELF_TEST

#define	NP_SERVER_MAGIC	'S'
#define	NP_CLIENT_MAGIC	'C'
#define	NP_MAX_PLAYERS	5
#define	NP_MAX_CLIENTS	(NP_MAX_PLAYERS - 1)
#define NP_PORT			6096

#ifdef SELF_TEST
#define SOCK_NAME		"/tmp/s9xsocket"
#endif

enum
{
	kNPClientNameSent = 101,
	kNPClientROMInfoWaiting,
	kNPClientROMOpened,
	kNPClientSRAMWaiting,
	kNPClientSRAMLoaded,
	kNPClientPlayerWaiting,
	kNPClientPlayWaiting,
	kNPClientStartWait
};

enum
{
	kNPServerNameRequest = 201,
	kNPServerNameReceived,
	kNPServerROMInfoWillSend,
	kNPServerSRAMWillSend,
	kNPServerPlayerWillSend,
	kNPServerStart
};

int socket_read (int, unsigned char *, int);
int socket_write (int, unsigned char *, int);
void NPError (const char *, int);
void NPNotification (const char *, int);

#endif
