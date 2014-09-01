#include "types.h"
#include "setup.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glib.h>


static SLbool is_active = false;

SLbool init_Sls()
{
    SLuint sdl_flags = SDL_INIT_EVERYTHING;
    if (SDL_Init(sdl_flags) < 0) {
        g_critical("SDL_Init(): %s\n", SDL_GetError());
        g_return_val_if_reached(false);
    }

    int flags=IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;
    int initted=IMG_Init(flags);
    if((initted & flags)!= flags) {
        printf("IMG_Init: Failed to init required support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }
    is_active = true;
    return true;
}

void quit_Sls()
{
    IMG_Quit();
    SDL_Quit();
}
SLbool Sls_is_active()
{
    SLbool response = is_active;
    return response;
}
