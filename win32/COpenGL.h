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


#ifndef COPENGL_H
#define COPENGL_H

#include <windows.h>
#include <gl\gl.h>
#include "cgFunctions.h"
#include "CGLCG.h"

#include "glext.h"
#include "wglext.h"
#include "IS9xDisplayOutput.h"

enum current_ogl_shader_type { OGL_SHADER_NONE, OGL_SHADER_GLSL, OGL_SHADER_CG };

class COpenGL : public IS9xDisplayOutput
{
private:
	HDC					hDC;
	HGLRC				hRC;
	HWND				hWnd;
	GLuint				drawTexture;
	GLuint				drawBuffer;
	GLfloat				vertices[8];
    GLfloat				texcoords[8];
	unsigned char *		noPboBuffer;

	int frameCount;

	bool initDone;
	bool fullscreen;
	unsigned int quadTextureSize;
	unsigned int filterScale;
	unsigned int afterRenderWidth, afterRenderHeight;

	bool shaderFunctionsLoaded;

	bool pboFunctionsLoaded;

	CGcontext cgContext;
	CGprogram cgVertexProgram, cgFragmentProgram;
	current_ogl_shader_type shader_type;
	bool cgAvailable;

	CGLCG *cgShader;

	GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;

	// PBO Functions
	PFNGLGENBUFFERSPROC		glGenBuffers;
	PFNGLBINDBUFFERPROC		glBindBuffer;
	PFNGLBUFFERDATAPROC		glBufferData;
	PFNGLDELETEBUFFERSPROC	glDeleteBuffers;
	PFNGLMAPBUFFERPROC		glMapBuffer;
	PFNGLUNMAPBUFFERPROC	glUnmapBuffer;

	// Shader Functions

	PFNGLCREATEPROGRAMPROC			glCreateProgram;
    PFNGLCREATESHADERPROC			glCreateShader;
    PFNGLCOMPILESHADERPROC			glCompileShader;
    PFNGLDELETESHADERPROC			glDeleteShader;
	PFNGLDELETEPROGRAMPROC			glDeleteProgram;
	PFNGLATTACHSHADERPROC			glAttachShader;
	PFNGLDETACHSHADERPROC			glDetachShader;
	PFNGLLINKPROGRAMPROC			glLinkProgram;
	PFNGLUSEPROGRAMPROC				glUseProgram;
	PFNGLSHADERSOURCEPROC			glShaderSource;
	PFNGLGETUNIFORMLOCATIONPROC		glGetUniformLocation;
	PFNGLUNIFORM2FVPROC				glUniform2fv;

	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

	bool SetShaders(const TCHAR *file);
	void checkForCgError(const char *situation);
	bool SetShadersCG(const TCHAR *file);
	bool SetShadersGLSL(const TCHAR *glslFileName);
	bool LoadShaderFunctions();
	bool LoadPBOFunctions();
	void CreateDrawSurface(void);
	void DestroyDrawSurface(void);
	bool ChangeDrawSurfaceSize(unsigned int scale);
	void SetupVertices();

public:
	COpenGL();
	~COpenGL();
	bool Initialize(HWND hWnd);
	void DeInitialize();
	void Render(SSurface Src);
	bool ChangeRenderSize(unsigned int newWidth, unsigned int newHeight);
	bool ApplyDisplayChanges(void);
	bool SetFullscreen(bool fullscreen);
	void SetSnes9xColorFormat(void);
	void EnumModes(std::vector<dMode> *modeVector);	
};


#endif
