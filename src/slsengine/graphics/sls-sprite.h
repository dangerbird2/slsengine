#ifndef __SLS_SPRITE_H__
#define __SLS_SPRITE_H__

#include "../types.h"
#include "../linalg/vectypes.h"

#include <SDL2/SDL.h>

typedef struct _slsSprite slsSprite;

struct _slsSprite {
    SDL_Texture *texture;
    SDL_Rect dest_rect;
    SDL_Rect src_rect;
};

slsSprite *slsSprite_create(
    SDL_Texture *tex,
    int x, int y,
    SDL_Rect const *texture_rect
);
void slsSprite_destroy(slsSprite *self);

void slsSprite_draw(SDL_Renderer *renderer, slsSprite *sprite);
void slsSprite_draw_transformed(SDL_Renderer *renderer, slsSprite *sprite);

#endif
