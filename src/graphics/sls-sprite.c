#include "sls-sprite.h"
#include <glib.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

slsSprite *slsSprite_create(
    SDL_Texture *tex,
    SDL_Rect const *dest_rect,
    SDL_Rect const *src_rect)
{
    slsSprite *sprite = NULL;

    sprite = malloc(sizeof(slsSprite));
    g_return_val_if_fail(sprite != NULL, NULL);
    g_return_val_if_fail(tex != NULL, NULL);

    if (dest_rect != NULL) {
        memcpy(&sprite->dest_rect, dest_rect, sizeof(SDL_Rect));
    } else {
        // dest rect is size of texture
        SDL_QueryTexture (tex, NULL, NULL,
            &sprite->dest_rect.w, &sprite->dest_rect.h);
    }

    if (src_rect != NULL) {
        memcpy(&sprite->src_rect, src_rect, sizeof(SDL_Rect));
    } else {
        // src rect is size of texture
        SDL_QueryTexture (tex, NULL, NULL,
            &sprite->src_rect.w, &sprite->src_rect.h);
    }

    return sprite;
}
void slsSprite_destroy(slsSprite *self)
{
    if (self) {free(self);}
}
