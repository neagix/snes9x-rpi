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
#include "memmap.h"


uint8 S9xGetOBC1 (uint16 Address)
{
	switch (Address)
	{
		case 0x7ff0:
			return (Memory.OBC1RAM[OBC1.basePtr + (OBC1.address << 2)]);

		case 0x7ff1:
			return (Memory.OBC1RAM[OBC1.basePtr + (OBC1.address << 2) + 1]);

		case 0x7ff2:
			return (Memory.OBC1RAM[OBC1.basePtr + (OBC1.address << 2) + 2]);

		case 0x7ff3:
			return (Memory.OBC1RAM[OBC1.basePtr + (OBC1.address << 2) + 3]);

		case 0x7ff4:
			return (Memory.OBC1RAM[OBC1.basePtr + (OBC1.address >> 2) + 0x200]);
	}

	return (Memory.OBC1RAM[Address - 0x6000]);
}

void S9xSetOBC1 (uint8 Byte, uint16 Address)
{
	switch (Address)
	{
		case 0x7ff0:
			Memory.OBC1RAM[OBC1.basePtr + (OBC1.address << 2)] = Byte;
			break;

		case 0x7ff1:
			Memory.OBC1RAM[OBC1.basePtr + (OBC1.address << 2) + 1] = Byte;
			break;

		case 0x7ff2:
			Memory.OBC1RAM[OBC1.basePtr + (OBC1.address << 2) + 2] = Byte;
			break;

		case 0x7ff3:
			Memory.OBC1RAM[OBC1.basePtr + (OBC1.address << 2) + 3] = Byte;
			break;

		case 0x7ff4:
		{
			uint8 Temp;
			Temp = Memory.OBC1RAM[OBC1.basePtr + (OBC1.address >> 2) + 0x200];
			Temp = (Temp & ~(3 << OBC1.shift)) | ((Byte & 3) << OBC1.shift);
			Memory.OBC1RAM[OBC1.basePtr + (OBC1.address >> 2) + 0x200] = Temp;
			break;
		}

		case 0x7ff5:
			if (Byte & 1)
				OBC1.basePtr = 0x1800;
			else
				OBC1.basePtr = 0x1c00;
			break;

		case 0x7ff6:
			OBC1.address = Byte & 0x7f;
			OBC1.shift = (Byte & 3) << 1;
			break;
	}

	Memory.OBC1RAM[Address - 0x6000] = Byte;
}

void S9xResetOBC1 (void)
{
	for (int i = 0; i <= 0x1fff; i++)
		Memory.OBC1RAM[i] = 0xff;

	if (Memory.OBC1RAM[0x1ff5] & 1)
		OBC1.basePtr = 0x1800;
	else
		OBC1.basePtr = 0x1c00;

	OBC1.address = Memory.OBC1RAM[0x1ff6] & 0x7f;
	OBC1.shift = (Memory.OBC1RAM[0x1ff6] & 3) << 1;
}

uint8 * S9xGetBasePointerOBC1 (uint16 Address)
{
	if (Address >= 0x7ff0 && Address <= 0x7ff6)
		return (NULL);
	return (Memory.OBC1RAM - 0x6000);
}

uint8 * S9xGetMemPointerOBC1 (uint16 Address)
{
	if (Address >= 0x7ff0 && Address <= 0x7ff6)
		return (NULL);
	return (Memory.OBC1RAM + Address - 0x6000);
}
