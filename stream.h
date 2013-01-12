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

#ifndef _STREAM_H_
#define _STREAM_H_

#include <string>

class Stream
{
	public:
		Stream (void);
		virtual ~Stream (void);
		virtual int get_char (void) = 0;
		virtual char * gets (char *, size_t) = 0;
		virtual char * getline (void);	// free() when done
		virtual std::string getline (bool &);
		virtual size_t read (void *, size_t) = 0;
        virtual size_t write (void *, size_t) = 0;
        virtual size_t pos (void) = 0;
        virtual size_t size (void) = 0;
        virtual int revert (size_t from, size_t offset) = 0;
        virtual void closeStream() = 0;
};

class fStream : public Stream
{
	public:
		fStream (FSTREAM);
		virtual ~fStream (void);
		virtual int get_char (void);
		virtual char * gets (char *, size_t);
		virtual size_t read (void *, size_t);
        virtual size_t write (void *, size_t);
        virtual size_t pos (void);
        virtual size_t size (void);
        virtual int revert (size_t from, size_t offset);
        virtual void closeStream();

	private:
		FSTREAM	fp;
};

#ifdef UNZIP_SUPPORT

#include "unzip.h"

#define unz_BUFFSIZ	1024

class unzStream : public Stream
{
	public:
		unzStream (unzFile &);
		virtual ~unzStream (void);
		virtual int get_char (void);
		virtual char * gets (char *, size_t);
		virtual size_t read (void *, size_t);
        virtual size_t write (void *, size_t);
        virtual size_t pos (void);
        virtual size_t size (void);
        virtual int revert (size_t from, size_t offset);
        virtual void closeStream();

	private:
		unzFile	file;
		char	buffer[unz_BUFFSIZ];
		char	*head;
		size_t	numbytes;
};

#endif

class memStream : public Stream
{
	public:
        memStream (uint8 *,size_t);
        memStream (const uint8 *,size_t);
		virtual ~memStream (void);
		virtual int get_char (void);
		virtual char * gets (char *, size_t);
		virtual size_t read (void *, size_t);
        virtual size_t write (void *, size_t);
        virtual size_t pos (void);
        virtual size_t size (void);
        virtual int revert (size_t from, size_t offset);
        virtual void closeStream();

	private:
		uint8   *mem;
        size_t  msize;
        size_t  remaining;
		uint8	*head;
        bool    readonly;
};

/* dummy stream that always reads 0 and writes nowhere
   but counts bytes written
*/
class nulStream : public Stream
{
	public:
        nulStream (void);
		virtual ~nulStream (void);
        virtual int get_char (void);
        virtual char * gets (char *, size_t);
		virtual size_t read (void *, size_t);
        virtual size_t write (void *, size_t);
        virtual size_t pos (void);
        virtual size_t size (void);
        virtual int revert (size_t from, size_t offset);
        virtual void closeStream();

    private:
        size_t  bytes_written;
};

Stream *openStreamFromFSTREAM(const char* filename, const char* mode);
Stream *reopenStreamFromFd(int fd, const char* mode);


#endif
