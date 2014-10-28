#include "stdhdr.h"
#include "setup.h"

static SLbool is_active = false;

SLbool init_Sls()
{
    SLuint sdl_flags = SDL_INIT_EVERYTHING;
    if (SDL_Init(sdl_flags) < 0) {
        log_err("SDL_Init(): %s\n", SDL_GetError());
        exit(-1);
    }

    int flags=IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;
    int initted=IMG_Init(flags);
    if((initted & flags)!= flags) {
        printf("IMG_Init: Failed to init required support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error

        exit(-1);
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
