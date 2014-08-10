#ifndef __SLS_CONTENT_H__
#define __SLS_CONTENT_H__

#include <glib-2.0/glib.h>
#include <SDL2/SDL.h>
#include "sls-sprite.h"
#include "../gl/sls-shader.h"

typedef struct _slsContentManager slsContentManager;

struct _slsContentManager {
    GHashTable *textures;
    GHashTable *shaders;
};

slsContentManager *slsContentManager_create();
void slsContentManager_destroy(slsContentManager *self);

void sls_hash_texture_free(gpointer texture);
void sls_hash_shader_free(gpointer shader);


SDL_Texture *slsContentManager_load_texture(
    slsContentManager *self,
    SDL_Renderer *renderer,
    char const *texture_key,
    char const *image_path);


slsShader *slsContentManager_load_shader(
	slsContentManager *self,
	char const *shader_name,
	char const *vspath,
	char const *fspath);

// dummy function returns argument unchanged
// todo: append path to proper game content path
//char *get_content_dir(char const *path);

#endif
