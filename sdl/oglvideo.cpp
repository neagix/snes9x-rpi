/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  See CREDITS file to find the copyright owners of this file.

  Snes9x homepage: http://www.snes9x.com/

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

#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#include "snes9x.h"
#include "memmap.h"
#include "ppu.h"
#include "controls.h"
#include "movie.h"
#include "logger.h"
#include "conffile.h"
#include "blit.h"
#include "display.h"

//#include "sdl_snes9x.h"

#include "port.h"
#include "conffile.h"

#include "../escommon/esUtil.h"

typedef struct
{
   // Handle to a program object
   GLuint programObject;

   // Attribute locations
   GLint  positionLoc;
   GLint  texCoordLoc;

   // Sampler location
   GLint samplerLoc;

   // Texture handle
   GLuint textureId;

} UserData;

struct GUIData
{
   ESContext esContext;
   UserData  userData;


	uint8			*snes_buffer;	// this is actually a 16bit values array of RGB565 color values
//	uint8			*blit_screen;
//	uint32			blit_screen_pitch;
	int			video_mode;
//    bool8                   fullscreen;
};
static struct GUIData	GUI;

typedef	void (* Blitter) (uint8 *, int, uint8 *, int, int, int);

#ifdef __linux
// Select seems to be broken in 2.x.x kernels - if a signal interrupts a
// select system call with a zero timeout, the select call is restarted but
// with an infinite timeout! The call will block until data arrives on the
// selected fd(s).
//
// The workaround is to stop the X library calling select in the first
// place! Replace XPending - which polls for data from the X server using
// select - with an ioctl call to poll for data and then only call the blocking
// XNextEvent if data is waiting.
#define SELECT_BROKEN_FOR_SIGNALS
#endif

enum
{
	VIDEOMODE_BLOCKY = 1,
	VIDEOMODE_TV,
	VIDEOMODE_SMOOTH,
	VIDEOMODE_SUPEREAGLE,
	VIDEOMODE_2XSAI,
	VIDEOMODE_SUPER2XSAI,
	VIDEOMODE_EPX,
	VIDEOMODE_HQ2X
};

static void SetupImage (void);
static void TakedownImage (void);
//static void Repaint (void);

void S9xExtraDisplayUsage (void)
{
//	S9xMessage(S9X_INFO, S9X_USAGE, "-fullscreen                     fullscreen mode (without scaling)");
	S9xMessage(S9X_INFO, S9X_USAGE, "");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v1                             Video mode: Blocky (default)");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v2                             Video mode: TV");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v3                             Video mode: Smooth");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v4                             Video mode: SuperEagle");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v5                             Video mode: 2xSaI");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v6                             Video mode: Super2xSaI");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v7                             Video mode: EPX");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v8                             Video mode: hq2x");
	S9xMessage(S9X_INFO, S9X_USAGE, "");
}

void S9xParseDisplayArg (char **argv, int &i, int argc)
{
/*	if (!strncasecmp(argv[i], "-fullscreen", 11))
        {
                GUI.fullscreen = TRUE;
                printf ("Entering fullscreen mode (without scaling).\n");
        }
        else */
	if (!strncasecmp(argv[i], "-v", 2))
	{
		switch (argv[i][2])
		{
			case '1':	GUI.video_mode = VIDEOMODE_BLOCKY;		break;
			case '2':	GUI.video_mode = VIDEOMODE_TV;			break;
			case '3':	GUI.video_mode = VIDEOMODE_SMOOTH;		break;
			case '4':	GUI.video_mode = VIDEOMODE_SUPEREAGLE;	break;
			case '5':	GUI.video_mode = VIDEOMODE_2XSAI;		break;
			case '6':	GUI.video_mode = VIDEOMODE_SUPER2XSAI;	break;
			case '7':	GUI.video_mode = VIDEOMODE_EPX;			break;
			case '8':	GUI.video_mode = VIDEOMODE_HQ2X;		break;
		}
	}
	else
		S9xUsage();
}

const char * S9xParseDisplayConfig (ConfigFile &conf, int pass)
{
	if (pass != 1)
		return ("Unix/OpenGL");

	if (conf.Exists("Unix/OpenGL::VideoMode"))
	{
		GUI.video_mode = conf.GetUInt("Unix/OpenGL::VideoMode", VIDEOMODE_BLOCKY);
		if (GUI.video_mode < 1 || GUI.video_mode > 8)
		{
			fprintf(stderr, "Invalid video mode in configuration, reverting to default\n");
			GUI.video_mode = VIDEOMODE_BLOCKY;
		}
		
		//neagix: all other modes disabled until we implement a better buffering method
		if (GUI.video_mode != 1)
		{
			fprintf(stderr, "You selected video mode %d, however only VIDEOMODE_BLOCKY is currently supported and will be used\n", GUI.video_mode);
			GUI.video_mode = VIDEOMODE_BLOCKY;
		}
		
	}
	else
		GUI.video_mode = VIDEOMODE_BLOCKY;

	return ("Unix/OpenGL");
}

static void FatalError (const char *str)
{
	fprintf(stderr, "%s\n", str);
	S9xExit();
}
   // 2x2 Image, 3 bytes per pixel (R, G, B)
   GLubyte testPixels[4 * 3] =
   {  
      255,   0,   0, // Red
        0, 255,   0, // Green
        0,   0, 255, // Blue
      255, 255,   0  // Yellow
   };

//
// Create a simple 2d texture
// we will later upload the pixels color data into it
//
GLuint Create2DTexture()
{
   // Texture object handle
   GLuint textureId;
   
   // Generate a texture object
   glGenTextures ( 1, &textureId );

   // Use tightly packed data
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 2 );

   // Bind the texture object
   glBindTexture ( GL_TEXTURE_2D, textureId );
   
	//TODO: neagix: minor optimization: use normal, not 2x scaled, buffer (when it is possible)
	int w = SNES_WIDTH;
	int h = (SNES_HEIGHT_EXTENDED + 4);
	
	printf("Creating texture with size %dx%d\n", w, h);
   
/*	srand (time(0));

   // we will initialize with random noise, for fun
   for(int i = 0;i < w*h; i++) {
//	   GLushort my_rand = (GLushort)rand();
		GLushort my_rand = 0xAAF0F;
	   
	   ((GLushort *)GUI.snes_buffer)[i] = my_rand;
   } */

   // Load the texture
   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, (GLushort *)GUI.snes_buffer );
   
   // Set the filtering mode
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );   


   return textureId;   
}

void DrawTest(GLuint textureId)
{
   // Bind the texture object
   glBindTexture ( GL_TEXTURE_2D, textureId );

   // Use tightly packed data
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );   

   // Load the texture
   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, testPixels );

   // Set the filtering mode
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );   
}

//TODO: neagix: use eglCreatePbufferSurface (if not using single-buffered display approach)
void TextureUpdate(GLuint textureId, GLushort *srcPixels, int w, int h)
{
   // Bind the texture object
   glBindTexture ( GL_TEXTURE_2D, textureId );
   
   // Load the texture
   glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, srcPixels);
//   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, (GLushort *)GUI.snes_buffer ); 
}

//
// Initialize the shader and program object
//
void OpenGL_ES_Init (GLfloat upScaleFactor)
{
	// initialize OpenGL ES
    esInitContext ( &GUI.esContext );
    GUI.esContext.userData = &GUI.userData;

	//TODO: neagix: use single-buffered EGL display surface
    if (GL_FALSE == esCreateWindow ( &GUI.esContext, SNES_WIDTH + 50, SNES_HEIGHT_EXTENDED + 50, ES_WINDOW_RGB, upScaleFactor ))
    {
	   fprintf(stderr, "Cannot create window!\n");
	   exit(-1);
    }
	
   GLbyte vShaderStr[] =  
      "attribute vec4 a_position;   \n"
      "attribute vec2 a_texCoord;   \n"
      "varying vec2 v_texCoord;     \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = a_position; \n"
      "   v_texCoord = a_texCoord;  \n"
      "}                            \n";
   
   GLbyte fShaderStr[] =  
      "precision mediump float;                            \n"
      "varying vec2 v_texCoord;                            \n"
      "uniform sampler2D s_texture;                        \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
      "}                                                   \n";

   // Load the shaders and get a linked program object
   GUI.userData.programObject = esLoadProgram ( (const char *)vShaderStr, (const char *)fShaderStr );

   // Get the attribute locations
   GUI.userData.positionLoc = glGetAttribLocation ( GUI.userData.programObject, "a_position" );
   GUI.userData.texCoordLoc = glGetAttribLocation ( GUI.userData.programObject, "a_texCoord" );
   
   // Get the sampler location
   GUI.userData.samplerLoc = glGetUniformLocation ( GUI.userData.programObject, "s_texture" );

   // create a blank textgure
   GUI.userData.textureId = Create2DTexture();

	// neagix: when debugging, we set background color to white to contrast with VT background color
   glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
}

//
// Cleanup
//
void OpenGL_ES_ShutDown ()
{
   // Delete texture object
   glDeleteTextures ( 1, &GUI.userData.textureId );

   // Delete program object
   glDeleteProgram ( GUI.userData.programObject );
}


GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

///
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{   
   float x1 = -0.5, y1 = 0.5;
   float x2 = 0.5, y2 = -0.5;
   
   GLfloat vVertices[] = { x1,  y1, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0 
                           x1, y2, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                           x2, y2, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                           x2,  y1, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
                         };
   
   //TODO: neagix: check if these statements are necessary to be reiterated for each frame (most probably not)

   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( GUI.userData.programObject );

   // Load the vertex position
   glVertexAttribPointer ( GUI.userData.positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 5 * sizeof(GLfloat), vVertices );
   // Load the texture coordinate
   glVertexAttribPointer ( GUI.userData.texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );

   glEnableVertexAttribArray ( GUI.userData.positionLoc );
   glEnableVertexAttribArray ( GUI.userData.texCoordLoc );

   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, GUI.userData.textureId );

   // Set the sampler texture unit to 0
   glUniform1i ( GUI.userData.samplerLoc, 0 );

   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

// modified by neagix to use OpenGL ES
void S9xInitDisplay (int argc, char **argv)
{
	/*
	 * domaemon
	 *
	 * we just go along with RGB565 for now, nothing else..
	 */
	 
	// neagix: TODO match this with best OpenGL mode, if possible
	//  GL_UNSIGNED_SHORT_5_6_5
	
	S9xSetRenderPixelFormat(RGB565);
	
	// neagix: could be commented out as well for now
	S9xBlitFilterInit();
	S9xBlit2xSaIFilterInit();
	S9xBlitHQ2xFilterInit();
		
	/*
	 * domaemon
	 *
	 * buffer allocation, quite important
	 */
	SetupImage();
	
	// initialize, fullscreen up-scaled
    OpenGL_ES_Init(1.0f);
}

void S9xDeinitDisplay (void)
{
	TakedownImage();

	OpenGL_ES_ShutDown();

	S9xBlitFilterDeinit();
	S9xBlit2xSaIFilterDeinit();
	S9xBlitHQ2xFilterDeinit();
}

static void TakedownImage (void)
{
	if (GUI.snes_buffer)
	{
		free(GUI.snes_buffer);
		GUI.snes_buffer = NULL;
	}

	S9xGraphicsDeinit();
}

static void SetupImage (void)
{
	TakedownImage();

	// domaemon: The whole unix code basically assumes output=(original * 2);
	// This way the code can handle the SNES filters, which does the 2X.
	
	// neagix: interpreting what is written above, this means we are allocating 2x memory buffer. it's ok
	GFX.Pitch = SNES_WIDTH * 2 * 2; // 2x for 16bit color, 2x to support 2x scaling
	GUI.snes_buffer = (uint8 *) calloc(GFX.Pitch * ((SNES_HEIGHT_EXTENDED + 4) * 2), 1);
	if (!GUI.snes_buffer)
		FatalError("Failed to allocate GUI.snes_buffer.");

	// domaemon: Add 2 lines before drawing.
	// neagix: why such 2 lines offset? never-checked canaries?
	GFX.Screen = (uint16 *) (GUI.snes_buffer + (GFX.Pitch * 2 * 2));
	
	// neagix: we will dump directly the SNES buffer to the rendered texture

	S9xGraphicsInit();
}

/*void S9xPutImage (int width, int height)
{
	
	// only simple direct rendering is currently supported, thus blitting part is commented out
	
	static int	prevWidth = 0, prevHeight = 0;
	int			copyWidth, copyHeight;
	Blitter		blitFn = NULL;

	if (GUI.video_mode == VIDEOMODE_BLOCKY || GUI.video_mode == VIDEOMODE_TV || GUI.video_mode == VIDEOMODE_SMOOTH)
		if ((width <= SNES_WIDTH) && ((prevWidth != width) || (prevHeight != height)))
			S9xBlitClearDelta();

	if (width <= SNES_WIDTH)
	{
		if (height > SNES_HEIGHT_EXTENDED)
		{
			copyWidth  = width * 2;
			copyHeight = height;
			blitFn = S9xBlitPixSimple2x1;
		}
		else
		{
			copyWidth  = width  * 2;
			copyHeight = height * 2;

			switch (GUI.video_mode)
			{
				case VIDEOMODE_BLOCKY:		blitFn = S9xBlitPixSimple2x2;		break;
				case VIDEOMODE_TV:			blitFn = S9xBlitPixTV2x2;			break;
				case VIDEOMODE_SMOOTH:		blitFn = S9xBlitPixSmooth2x2;		break;
				case VIDEOMODE_SUPEREAGLE:	blitFn = S9xBlitPixSuperEagle16;	break;
				case VIDEOMODE_2XSAI:		blitFn = S9xBlitPix2xSaI16;			break;
				case VIDEOMODE_SUPER2XSAI:	blitFn = S9xBlitPixSuper2xSaI16;	break;
				case VIDEOMODE_EPX:			blitFn = S9xBlitPixEPX16;			break;
				case VIDEOMODE_HQ2X:		blitFn = S9xBlitPixHQ2x16;			break;
			}
		}
	}
	else
	if (height <= SNES_HEIGHT_EXTENDED)
	{
		copyWidth  = width;
		copyHeight = height * 2;

		switch (GUI.video_mode)
		{
			default:					blitFn = S9xBlitPixSimple1x2;	break;
			case VIDEOMODE_TV:			blitFn = S9xBlitPixTV1x2;		break;
		}
	}
	else
	{
		copyWidth  = width;
		copyHeight = height;
		blitFn = S9xBlitPixSimple1x1;
	}

	// domaemon: this is place where the rendering buffer size should be changed?
	blitFn((uint8 *) GFX.Screen, GFX.Pitch, GUI.blit_screen, GUI.blit_screen_pitch, width, height);

	// domaemon: does the height change on the fly?
	if (height < prevHeight)
	{
		int	p = GUI.blit_screen_pitch >> 2;
		for (int y = SNES_HEIGHT * 2; y < SNES_HEIGHT_EXTENDED * 2; y++)
		{
			uint32	*d = (uint32 *) (GUI.blit_screen + y * GUI.blit_screen_pitch);
			for (int x = 0; x < p; x++)
				*d++ = 0;
		}
	} 

	Repaint(TRUE);

	prevWidth  = width;
	prevHeight = height;
} */

//static int framesRendered = 0;

// neagix: we force a double-buffer swap only on frame boundary (that is always, in this case)
void S9xPutImage(int w, int h)
{
//	framesRendered++;
//	if (framesRendered == 200)
//		exit(0);
	
//	printf("painting frame #%d (area is %dx%d)\n", framesRendered, w, h);
	
	// neagix: we will update only the necessary area
	TextureUpdate(GUI.userData.textureId, (GLushort *)GUI.snes_buffer, w, h);
	
	Draw(&GUI.esContext);
	
	eglSwapBuffers(GUI.esContext.eglDisplay, GUI.esContext.eglSurface);	
}

void S9xMessage (int type, int number, const char *message)
{
	const int	max = 36 * 3;
	static char	buffer[max + 1];

	fprintf(stdout, "%s\n", message);
	strncpy(buffer, message, max + 1);
	buffer[max] = 0;
	S9xSetInfoString(buffer);
}

const char * S9xStringInput (const char *message)
{
	static char	buffer[256];

	printf("%s: ", message);
	fflush(stdout);

	if (fgets(buffer, sizeof(buffer) - 2, stdin))
		return (buffer);

	return (NULL);
}

void S9xSetTitle (const char *string)
{
//	SDL_WM_SetCaption(string, string);
}

void S9xSetPalette (void)
{
	return;
}
