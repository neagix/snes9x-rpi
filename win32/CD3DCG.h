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
#define CGD3DCG_H

#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "CCGShader.h"
#include <vector>
#include <deque>

class CD3DCG
{
private:
	typedef struct _parameterEntry {
		unsigned long rIndex;
		const char* semantic;
		bool isKnownParam;
		UINT streamNumber;
	} parameterEntry;
	typedef struct _shaderPass {
		cgScaleParams scaleParams;
		bool linearFilter;
		CGprogram cgVertexProgram, cgFragmentProgram;
		LPDIRECT3DTEXTURE9    tex;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		LPDIRECT3DVERTEXDECLARATION9 vertexDeclaration;
		std::vector<parameterEntry> parameterMap;

		D3DXVECTOR2 outputSize;
		D3DXVECTOR2 textureSize;

		_shaderPass()  {cgVertexProgram=NULL;
					    cgFragmentProgram=NULL;
						tex=NULL;
						vertexBuffer=NULL;
						vertexDeclaration=NULL;}
	} shaderPass;
	typedef struct _prevPass {
		LPDIRECT3DTEXTURE9    tex;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		D3DXVECTOR2 imageSize;
		D3DXVECTOR2 textureSize;
		_prevPass() {tex=NULL;
		             vertexBuffer=NULL;}
		_prevPass(const shaderPass &pass) {tex = pass.tex;
		                                   vertexBuffer = pass.vertexBuffer;
										   imageSize = pass.outputSize;
										   textureSize = pass.textureSize;}
	} prevPass;
	typedef struct _lookupTexture {
		char id[PATH_MAX];
		LPDIRECT3DTEXTURE9 tex;
		bool linearFilter;
		_lookupTexture() {tex=NULL;}
	} lookupTexture;

	std::vector<shaderPass> shaderPasses;
	std::vector<lookupTexture> lookupTextures;
	std::deque<prevPass> prevPasses;

	bool shaderLoaded;
	void checkForCgError(const char *situation);
	void setVertexStream(IDirect3DVertexBuffer9 *vertexBuffer,D3DXVECTOR2 inputSize,D3DXVECTOR2 textureSize,D3DXVECTOR2 outputSize);
	void setViewport(DWORD x, DWORD y, DWORD width, DWORD height);
	void setShaderVars(int pass);
	void ensureTextureSize(LPDIRECT3DTEXTURE9 &tex, D3DXVECTOR2 &texSize, D3DXVECTOR2 wantedSize,bool renderTarget);
	void fillParameterMap(std::vector<parameterEntry> &map, CGparameter param);
	void setupVertexDeclaration(shaderPass &pass);
	void calculateMatrix();

	LPDIRECT3DDEVICE9     pDevice;
	CGcontext cgContext;
	float frameCnt;
	D3DXMATRIX mvp;

public:
	CD3DCG(CGcontext cgContext,LPDIRECT3DDEVICE9 pDevice);
	~CD3DCG(void);

	bool LoadShader(const TCHAR *shaderFile);
	void Render(LPDIRECT3DTEXTURE9 &origTex, D3DXVECTOR2 textureSize, D3DXVECTOR2 inputSize, D3DXVECTOR2 viewportSize, D3DXVECTOR2 windowSize);
	void ClearPasses();	
	void OnLostDevice();
	void OnResetDevice();
};

#endif
