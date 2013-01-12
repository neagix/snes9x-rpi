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


#ifndef CGFUNCTIONS_H
#define CGFUNCTIONS_H

#define CG_EXPLICIT
#define CGD3D9_EXPLICIT
#define CGGL_EXPLICIT

#include <cg/cg.h>
#include <cg/cgd3d9.h>
#include <cg/cggl.h>

//cg.dll
typedef CG_API CGcontext (CGENTRY *CGCC)(void);
extern CGCC cgCreateContext;
typedef CG_API void (CGENTRY *CGDC)(CGcontext context);
extern CGDC cgDestroyContext;
typedef CG_API CGparameter (CGENTRY *CGGNP)(CGprogram program, const char *name);
extern CGGNP cgGetNamedParameter;
typedef CG_API CGerror (CGENTRY *CGGE)(void);
extern CGGE cgGetError;
typedef CG_API const char * (CGENTRY *CGGES)(CGerror error);
extern CGGES cgGetErrorString;
typedef CG_API const char * (CGENTRY *CGGLL)(CGcontext context);
extern CGGLL cgGetLastListing;
typedef CG_API CGprogram (CGENTRY *CGCP)(CGcontext context, CGenum program_type, const char *program, CGprofile profile, const char *entry, const char **args);
extern CGCP cgCreateProgram;
typedef CG_API void (CGENTRY *CGDP)(CGprogram program);
extern CGDP cgDestroyProgram;
typedef CG_API unsigned long (CGENTRY *CGGPRI)(CGparameter param);
extern CGGPRI cgGetParameterResourceIndex;
typedef CG_API CGparameter (CGENTRY *CGGFP)(CGprogram program, CGenum name_space);
extern CGGFP cgGetFirstParameter;
typedef CG_API CGparameter (CGENTRY *CGGNEP)(CGparameter current);
extern CGGNEP cgGetNextParameter;
typedef CG_API CGenum (CGENTRY *CGGPD)(CGparameter param);
extern CGGPD cgGetParameterDirection;
typedef CG_API const char * (CGENTRY *CGGPS)(CGparameter param);
extern CGGPS cgGetParameterSemantic;
typedef CG_API const char * (CGENTRY *CGGRS)(CGresource resource);
extern CGGRS cgGetResourceString;
typedef CG_API CGenum (CGENTRY *CGGPV)(CGparameter param);
extern CGGPV cgGetParameterVariability;
typedef CG_API CGtype (CGENTRY *CGGPT)(CGparameter param);
extern CGGPT cgGetParameterType;
typedef CG_API CGparameter (CGENTRY *CGGFSP)(CGparameter param);
extern CGGFSP cgGetFirstStructParameter;
typedef CG_API const char * (CGENTRY *CGGPN)(CGparameter param);
extern CGGPN cgGetParameterName;

//cgD3D9.dll
typedef CGD3D9DLL_API HRESULT (CGD3D9ENTRY *CGD3DSD)(IDirect3DDevice9 *pDevice);
extern CGD3DSD cgD3D9SetDevice;
typedef CGD3D9DLL_API HRESULT (CGD3D9ENTRY *CGD3DBP)(CGprogram prog);
extern CGD3DBP cgD3D9BindProgram;
typedef CGD3D9DLL_API CGprofile (CGD3D9ENTRY *CGD3DGLVP)(void);
extern CGD3DGLVP cgD3D9GetLatestVertexProfile;
typedef CGD3D9DLL_API CGprofile (CGD3D9ENTRY *CGD3DGLPP)(void);
extern CGD3DGLPP cgD3D9GetLatestPixelProfile;
typedef CGD3D9DLL_API const char ** (CGD3D9ENTRY *CGD3DGOO)(CGprofile profile);
extern CGD3DGOO cgD3D9GetOptimalOptions;
typedef CGD3D9DLL_API HRESULT (CGD3D9ENTRY *CGD3DLP)(CGprogram prog, CGbool paramShadowing, DWORD assemFlags);
extern CGD3DLP cgD3D9LoadProgram;
typedef CGD3D9DLL_API HRESULT (CGD3D9ENTRY *CGD3DSUM)(CGparameter param, const D3DMATRIX *matrix);
extern CGD3DSUM cgD3D9SetUniformMatrix;
typedef CGD3D9DLL_API HRESULT (CGD3D9ENTRY *CGD3DSU)(CGparameter param, const void *floats);
extern CGD3DSU cgD3D9SetUniform;
typedef CGD3D9DLL_API HRESULT (CGD3D9ENTRY *CGD3DST)(CGparameter param, IDirect3DBaseTexture9 *tex);
extern CGD3DST cgD3D9SetTexture;
typedef CGD3D9DLL_API CGbool (CGD3D9ENTRY *CGD3DGVD)(CGprogram prog, D3DVERTEXELEMENT9 decl[MAXD3DDECLLENGTH]);
extern CGD3DGVD cgD3D9GetVertexDeclaration;
typedef CGD3D9DLL_API HRESULT (CGD3D9ENTRY *CGD3DSSS)(CGparameter param, D3DSAMPLERSTATETYPE type, DWORD value);
extern CGD3DSSS cgD3D9SetSamplerState;

//cggl.dll
typedef CGGL_API void (CGGLENTRY *CGGLSSMP)(CGparameter param, CGGLenum matrix, CGGLenum transform);
extern CGGLSSMP cgGLSetStateMatrixParameter;
typedef CGGL_API void (CGGLENTRY *CGGLSP1F)(CGparameter param, float x);
extern CGGLSP1F cgGLSetParameter1f;
typedef CGGL_API void (CGGLENTRY *CGGLSP2FV)(CGparameter param, const float *v);
extern CGGLSP2FV cgGLSetParameter2fv;
typedef CGGL_API CGprofile (CGGLENTRY *CGGLGLP)(CGGLenum profile_type);
extern CGGLGLP cgGLGetLatestProfile;
typedef CGGL_API void (CGGLENTRY *CGGLEP)(CGprofile profile);
extern CGGLEP cgGLEnableProfile;
typedef CGGL_API void (CGGLENTRY *CGGLDP)(CGprofile profile);
extern CGGLDP cgGLDisableProfile;
typedef CGGL_API void (CGGLENTRY *CGGLSOO)(CGprofile profile);
extern CGGLSOO cgGLSetOptimalOptions;
typedef CGGL_API void (CGGLENTRY *CGGLLP)(CGprogram program);
extern CGGLLP cgGLLoadProgram;
typedef CGGL_API void (CGGLENTRY *CGGLBP)(CGprogram program);
extern CGGLBP cgGLBindProgram;
typedef CGGL_API void (CGGLENTRY *CGGLSTP)(CGparameter param, GLuint texobj);
extern CGGLSTP cgGLSetTextureParameter;
typedef CGGL_API void (CGGLENTRY *CGGLETP)(CGparameter param);
extern CGGLETP cgGLEnableTextureParameter;
typedef CGGL_API void (CGGLENTRY *CGGLSPP)(CGparameter param, GLint fsize, GLenum type, GLsizei stride, const GLvoid *pointer);
extern CGGLSPP cgGLSetParameterPointer;
typedef CGGL_API void (CGGLENTRY *CGGLECS)(CGparameter param);
extern CGGLECS cgGLEnableClientState;
typedef CGGL_API void (CGGLENTRY *CGGLDCS)(CGparameter param);
extern CGGLDCS cgGLDisableClientState;

//cgfunctions.cpp
bool loadCgFunctions();
void unloadCgLibrary();

#endif		//CGFUNCTIONS_H
