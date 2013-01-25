
#include "port.h"
#include "gfx.h"
#include "svga.h"
#include "snes9x.h"

#include "librpi2d/rpi2d.h"
#include <GLES2/gl2.h>

extern void S9xExit();

extern uint32 xs, ys, cl, cs;
extern bool8_32 Scale;

void *dest_screen_buffer = NULL, *gfxscreen = NULL;
Texture2D *textureBuffer;
Raspberry2D *rpi2D;

void S9xPerformUpdate(int x, int y, int w, int h) {
    textureBuffer->Render(dest_screen_buffer, 0, y, textureBuffer->Width, h);

    rpi2D->Draw(*textureBuffer);

    rpi2D->SwapBuffers();
}

void S9xInitDisplay(int /*argc*/, char ** /*argv*/) {
    //TODO: cover all screen in black, then render only texture in center

    // initialize Raspberry Pi
    rpi2D = new Raspberry2D(xs, ys);

    // vertical ratio
    float ratio = ((float) rpi2D->DisplayHeight - 80) / rpi2D->Height;

    float finalW = rpi2D->Width * ratio;

    // attach surface
    if (!rpi2D->Attach(finalW, rpi2D->DisplayHeight - 80)) {
        delete rpi2D;

        fprintf(stderr, "Could not attach surface\n");
        S9xExit();
    }

    // create the texture
    textureBuffer = new Texture2D(xs, ys, 2, GL_RGB, GL_UNSIGNED_SHORT_5_6_5);

    // create the main display surface
    dest_screen_buffer = malloc(320 * textureBuffer->Height * 2);

    //TODO: check if possible to use directly one surface when no hires mode is needed

    if (Settings.SupportHiRes) {
        printf("Enabling high-resolution\n");
        gfxscreen = malloc(512 * 480 * 2);
        GFX.Screen = (uint8 *) gfxscreen;
        GFX.Pitch = 512 * 2;
    } else {
#ifdef PANDORA
        if (g_scale > bs_1to1) {
            GFX.Screen = (uint8*) malloc((512 * 480 * 2) + 64);
            GFX.Pitch = 320 * 2;
        } else {
            GFX.Screen = (uint8 *) dest_screen_buffer + 64;
            GFX.Pitch = 320 * 2;
        }
#else
        if (Scale) {
            GFX.Screen = (uint8 *) dest_screen_buffer;
            GFX.Pitch = 320 * 2;
        } else {
            GFX.Screen = (uint8 *) dest_screen_buffer + 64; //center screen
            GFX.Pitch = 320 * 2;
        }
#endif
    }

    GFX.SubScreen = (uint8 *) malloc(512 * 480 * 2);
    GFX.ZBuffer = (uint8 *) malloc(512 * 480 * 2);
    GFX.SubZBuffer = (uint8 *) malloc(512 * 480 * 2);
}

void S9xDeinitDisplay() {
#ifdef PANDORA
    // for vsync
    extern int g_fb;
    if (g_fb >= 0) {
        close(g_fb);
    }
    // for LCD refresh
    system("/usr/bin/sudo -n /usr/pandora/scripts/op_lcdrate.sh 60");
#endif

    // -- deinit video start
    delete textureBuffer;
    delete rpi2D;

    // only created for high-res modes
    if (gfxscreen != NULL)
        free(gfxscreen);

    free(dest_screen_buffer);
    // -- deinit video end

    free(GFX.SubScreen);
    free(GFX.ZBuffer);
    free(GFX.SubZBuffer);
}

