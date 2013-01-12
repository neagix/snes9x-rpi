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

#ifndef _SETA_H_
#define _SETA_H_

#define ST_010	0x01
#define ST_011	0x02
#define ST_018	0x03

struct SST010
{
	uint8	input_params[16];
	uint8	output_params[16];
	uint8	op_reg;
	uint8	execute;
	bool8	control_enable;
};

struct SST011
{
	bool8	waiting4command;
	uint8	status;
	uint8	command;
	uint32	in_count;
	uint32	in_index;
	uint32	out_count;
	uint32	out_index;
	uint8	parameters[512];
	uint8	output[512];
};

struct SST018
{
	bool8	waiting4command;
	uint8	status;
	uint8	part_command;
	uint8	pass;
	uint32	command;
	uint32	in_count;
	uint32	in_index;
	uint32	out_count;
	uint32	out_index;
	uint8	parameters[512];
	uint8	output[512];
};

extern struct SST010	ST010;
extern struct SST011	ST011;
extern struct SST018	ST018;

uint8 S9xGetST010 (uint32);
void S9xSetST010 (uint32, uint8);
uint8 S9xGetST011 (uint32);
void S9xSetST011 (uint32, uint8);
uint8 S9xGetST018 (uint32);
void S9xSetST018 (uint8, uint32);
uint8 S9xGetSetaDSP (uint32);
void S9xSetSetaDSP (uint8, uint32);

extern uint8 (*GetSETA) (uint32);
extern void (*SetSETA) (uint32, uint8);

#endif
