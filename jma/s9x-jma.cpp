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
//  JMA compressed file support
//  (c) Copyright 2004-2006 NSRT Team (http://nsrt.edgeemu.com)


#include "snes9x.h"
#include "memmap.h"

#include <vector>
using namespace std;

#include "s9x-jma.h"
#include "jma.h"

size_t load_jma_file(const char *filename, unsigned char *buffer)
{
  try
  {
    JMA::jma_open JMAFile(filename);
    vector<JMA::jma_public_file_info> file_info = JMAFile.get_files_info();

    string our_file_name;
    size_t our_file_size = 0;

    for (vector<JMA::jma_public_file_info>::iterator i = file_info.begin(); i != file_info.end(); i++)
    {
      //Check for valid ROM based on size
      if ((i->size <= CMemory::MAX_ROM_SIZE+512) && (i->size > our_file_size))
      {
        our_file_name = i->name;
        our_file_size = i->size;
      }
    }

    if (!our_file_size)
    {
      return(0);
    }

    JMAFile.extract_file(our_file_name, buffer);

    return(our_file_size);
  }
  catch (JMA::jma_errors jma_error)
  {
    return(0);
  }
}
