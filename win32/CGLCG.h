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
#define CGGLCG_H

#include <windows.h>
#include <gl/gl.h>
#include "glext.h"
#include "cgFunctions.h"
#include "CCGShader.h"
#include <vector>
#include <deque>

typedef struct _xySize {
	double x;
	double y;
	operator CONST FLOAT* () const;
} xySize;

class CGLCG
{
private:
	typedef struct _STGA {
		_STGA() {data = (unsigned char*)0;
				 width = 0;
				 height = 0;
				 byteCount = 0;}

		~_STGA() { delete[] data; data = 0; }

		void destroy() { delete[] data; data = 0; }

		int width;
		int height;
		unsigned char byteCount;
		unsigned char* data;
	} STGA;
	typedef struct _shaderPass {
		cgScaleParams scaleParams;
		bool linearFilter;
		CGprogram cgVertexProgram, cgFragmentProgram;
		GLuint tex;
		GLuint fbo;
		xySize outputSize;
		xySize textureSize;
		GLfloat	texcoords[8];
		_shaderPass()  {cgVertexProgram=NULL;
					    cgFragmentProgram=NULL;
						fbo=NULL;
						tex=NULL;}
	} shaderPass;
	typedef struct _prevPass {
		GLuint tex;
		xySize videoSize;
		xySize textureSize;
		GLfloat	texCoords[8];
		_prevPass() {tex=0;}
	} prevPass;
	typedef struct _lookupTexture {
		char id[PATH_MAX];
		GLuint tex;
		_lookupTexture() {tex=NULL;}
	} lookupTexture;

	typedef std::vector<shaderPass> glPassVector;
	typedef std::vector<lookupTexture> glLutVector;
	typedef std::deque<prevPass> glPrevDeque;
	typedef std::vector<CGparameter> glAttribParams;
	glPassVector shaderPasses;
	glLutVector lookupTextures;
	glPrevDeque prevPasses;
	glAttribParams cgAttribParams;

	bool fboFunctionsLoaded;
	bool shaderLoaded;
	bool LoadFBOFunctions();
	void checkForCgError(const char *situation);
	void setTexCoords(int pass,xySize inputSize,xySize textureSize,bool topdown=false);
	void setShaderVars(int pass);
	void resetAttribParams();
	bool loadPngImage(const TCHAR *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
	bool loadTGA(const TCHAR *filename, STGA& tgaFile);

	CGcontext cgContext;
	int frameCnt;
	static const GLfloat lut_coords[8];


	PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
	PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
	PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
	PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
	PFNGLACTIVETEXTUREPROC glClientActiveTexture;

public:
	CGLCG(CGcontext cgContext);
	~CGLCG(void);

	bool LoadShader(const TCHAR *shaderFile);
	void Render(GLuint &origTex, xySize textureSize, xySize inputSize, xySize viewportSize, xySize windowSize);
	void ClearPasses();	
};

#endif
