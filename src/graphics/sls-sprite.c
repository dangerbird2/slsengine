#include "sls-sprite.h"
#include <glib.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

slsSprite *slsSprite_create(
    SDL_Texture *tex,
    int x, int y,
    SDL_Rect const *texture_rect)
{
    slsSprite *sprite = NULL;

    sprite = malloc(sizeof(slsSprite));
    g_return_val_if_fail(sprite != NULL, NULL);
    g_return_val_if_fail(tex != NULL, NULL);

    sprite->src_rect = (SDL_Rect) {0, 0, 1, 1};
    if (texture_rect != NULL) {
        memcpy(&sprite->src_rect, texture_rect, sizeof(SDL_Rect));
    } else {
        // src rect is size of texture
        SDL_QueryTexture (tex, NULL, NULL,
            &sprite->src_rect.w, &sprite->src_rect.h);
    }

    sprite->dest_rect = (SDL_Rect){x, y, sprite->src_rect.w, sprite->src_rect.h};

    return sprite;
}
void slsSprite_destroy(slsSprite *self)
{
    if (self) {free(self);}
}
