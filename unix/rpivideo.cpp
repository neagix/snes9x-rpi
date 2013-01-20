
#include "port.h"
#include "gfx.h"
#include "rpivideo.h"

#include "librpi2d/rpi2d.h"
#include <GLES2/gl2.h>

extern uint32 xs, ys, cl, cs;
//extern bool8_32 Scale;

void *dest_screen_buffer = NULL, *gfxscreen = NULL;
Texture2D *textureBuffer;
Raspberry2D *rpi2D;

void S9xPerformUpdate(int x, int y, int w, int h) {
    textureBuffer->Render(dest_screen_buffer, 0, y, textureBuffer->Width, h);
    
    rpi2D->Draw(*textureBuffer);
    
    rpi2D->SwapBuffers();
}

bool S9xInitVideo() {
    // initialize Raspberry Pi
    rpi2D = new Raspberry2D(xs, ys);
    
    // vertical ratio
    float ratio = ((float)rpi2D->DisplayHeight-80) / rpi2D->Height;
    
    float finalW = rpi2D->Width * ratio;

    // attach surface
    if (!rpi2D->Attach(finalW, rpi2D->DisplayHeight-80)) {
        delete rpi2D;

        fprintf(stderr, "Could not attach surface\n");
        return false;
    }

    // create the texture
    textureBuffer = new Texture2D(rpi2D->Width, rpi2D->Height, 2, GL_RGB, GL_UNSIGNED_SHORT_5_6_5);
    
    // create the main display surface
    dest_screen_buffer = malloc(xs * ys * 2);

    return true;
}

void S9xEnableHiRes() {
    printf("Enabling high-resolution\n");
    gfxscreen = malloc(512*480*2);
    GFX.Screen = (uint8 *) gfxscreen;
    GFX.Pitch = 512 * 2;
}

void S9xDeInitVideo() {
    
    delete textureBuffer;
    delete rpi2D;
    
    // only created for high-res modes
    if (gfxscreen != NULL)
        free(gfxscreen);

    free(dest_screen_buffer);
}
