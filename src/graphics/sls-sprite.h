#ifndef __SLS_SPRITE_H__
#define __SLS_SPRITE_H__

#include "../types.h"

#include <SDL2/SDL.h>

typedef struct _slsSprite slsSprite;

struct _slsSprite {
    SDL_Texture *texture;
    SDL_Rect dest_rect;
    SDL_Rect src_rect;
};

slsSprite *slsSprite_create(
    SDL_Texture *tex,
    SDL_Rect const *dest_rect,
    SDL_Rect const *texture_rect
);
void slsSprite_destroy(slsSprite *self);

#endif
