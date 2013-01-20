
#include "port.h"
#include "gfx.h"
#include "sdlvideo.h"

#include <SDL/SDL.h>

extern uint32 xs, ys, cl, cs;
extern bool8_32 Scale;

void *dest_screen_buffer;

SDL_Surface *screen, *gfxscreen = NULL;

void S9xPerformUpdate(int x, int y, int w, int h) {
    SDL_UpdateRect(screen, x, y, w, h);
}

bool S9xInitVideo() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        exit(3);
        return false;
    }

    atexit(SDL_Quit);

    // No more MOUSE-CURSOR
    SDL_ShowCursor(SDL_DISABLE);

#ifdef PANDORA
    /*
    //screen = SDL_SetVideoMode(xs * blit_scalers [ g_scale ].scale_x, ys * blit_scalers [ g_scale ].scale_y, 16,
    //			   SDL_SWSURFACE|SDL_FULLSCREEN);
    //screen = SDL_SetVideoMode( 800 , 480 , 16,
    //			   SDL_SWSURFACE|SDL_FULLSCREEN);
    std::cerr << "setting video mode in S9xInitDisplay, selected mode: " << (std::string) blit_scalers [ g_scale ].desc_en << std::endl;
    //NOTE: the following block should not be required but is left for "safety reasons"
    if (Settings.SupportHiRes && !(blit_scalers [ g_scale ].support_hires)) {
        std::cerr << "S9xInitDisplay: mode \"" << (std::string) blit_scalers [ g_scale ].desc_en << "\" not enabled for hires mode!" << std::endl;
        g_scale = bs_1to2_double;
    }

    setenv("SDL_OMAP_LAYER_SIZE", blit_scalers [ g_scale ].layersize, 1);
    // 	screen = SDL_SetVideoMode( blit_scalers [ g_scale ].res_x , blit_scalers [ g_scale ].res_y, 16,
    // 				   SDL_DOUBLEBUF|SDL_FULLSCREEN);
    screen = SDL_SetVideoMode(blit_scalers [ g_scale ].res_x, blit_scalers [ g_scale ].res_y, 16,
            SDL_SWSURFACE | SDL_FULLSCREEN);

    // for vsync
    // WARNING! this is used as framelimiter, too! The emulator will run by far
    // too fast if you remove this next block!
    // fb1 as well as fb0 seem to work (skeeziz coded it with fb0, but since
    // fb1 works, too, I will leave it at that for the moment).
    {
        extern int g_fb;
        g_fb = open("/dev/fb1", O_RDONLY );
        if (g_fb < 0) {
            fprintf(stderr, "Couldn't open /dev/fb1 for vsync\n");
        }
    }

    // for LCD refresh rate
    switch ((int) Memory.ROMFramesPerSecond) {
        case 60:
            fprintf(stderr, "60hz LCD\n");
            break; // nothing to do
        case 50:
            fprintf(stderr, "50hz LCD\n");
            //            system("/usr/bin/sudo -n /usr/pandora/scripts/op_lcdrate.sh 50");
            break;
        default:
            fprintf(stderr, "Game reports %d hz display; ignoring.\n", (int) Memory.ROMFramesPerSecond);
            break;
    }
     */
#else //DINGOO //CAANOO
    // neagix: check SDL flags effect later
    screen = SDL_SetVideoMode(xs, ys, 16, 0 * SDL_HWSURFACE); //do no take SDL_HWSURFACE on Dingoo (bad overlays) and CAANOO (flickers)

    dest_screen_buffer = screen->pixels;
#endif

    if (screen == NULL) {
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        return false;
    }
}

void S9xEnableHiRes() {
    printf("Enabling high-resolution");
    gfxscreen = SDL_CreateRGBSurface(SDL_SWSURFACE, 512, 480, 16, 0, 0, 0, 0);
    GFX.Screen = (uint8 *) gfxscreen->pixels;
    GFX.Pitch = 512 * 2;
}

void S9xDeInitVideo() {
    // only created for high-res modes
    if (gfxscreen != NULL)
        SDL_FreeSurface(gfxscreen);

    SDL_FreeSurface(screen);
    SDL_ShowCursor(SDL_ENABLE);
}
