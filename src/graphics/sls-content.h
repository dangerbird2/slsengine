#ifndef __SLS_CONTENT_H__
#define __SLS_CONTENT_H__

#include <glib.h>
#include <SDL2/SDL.h>
#include "sls-sprite.h"

typedef struct _slsContentManager slsContentManager;

struct _slsContentManager {
    GHashTable *textures;
    GHashTable *sprites;
};

slsContentManager *slsContentManager_create();
void slsContentManager_destroy(slsContentManager *self);

void sls_hash_texture_free(gpointer data);
void sls_hash_sprite_free(gpointer data);

SDL_Texture *slsContentManager_load_texture(
    slsContentManager *self,
    SDL_Renderer *renderer,
    char const *texture_key,
    char const *image_path);

slsSprite *slsContentManager_load_sprite(
    slsContentManager *self,
    char const *sprite_key,
    char const *tgt_texture_key,
    SDL_Rect const * dest_rect,
    SDL_Rect const * src_rect
);

// dummy function returns argument unchanged
// todo: append path to proper game content path
char *get_content_dir(char const *path);

#endif
