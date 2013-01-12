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
#define CCGSHADER_H

#include "port.h"
#include "cgFunctions.h"
#include <vector>

enum cgScaleType { CG_SCALE_NONE, CG_SCALE_SOURCE, CG_SCALE_VIEWPORT, CG_SCALE_ABSOLUTE };
typedef struct _cgScaleParams {
	cgScaleType scaleTypeX;
	cgScaleType scaleTypeY;
	float scaleX;
	float scaleY;
	unsigned absX;
	unsigned absY;
} cgScaleParams;

class CCGShader
{
private:	
	cgScaleType scaleStringToEnum(const char* scale);
public:
	typedef struct _shaderPass {
		cgScaleParams scaleParams;
		bool linearFilter;
		bool filterSet;
		char cgShaderFile[PATH_MAX];
	} shaderPass;
	typedef struct _lookupTexture {
		char id[PATH_MAX];
		char texturePath[PATH_MAX];
		bool linearfilter;
	} lookupTexture;

	CCGShader(void);
	~CCGShader(void);
	bool LoadShader(const char *path);

	typedef std::vector<shaderPass> passVector;
	typedef std::vector<lookupTexture> lutVector;
	passVector shaderPasses;
	lutVector lookupTextures;
};

#endif
