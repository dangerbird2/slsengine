#ifndef __SLS_CONTENT_H__
#define __SLS_CONTENT_H__

#include <glib-2.0/glib.h>
#include <SDL2/SDL.h>
#include "sls-sprite.h"
#include "../graphics/sls-shader.h"
#include "../graphics/sls-mesh.h"



typedef struct _slsContentManager slsContentManager;
typedef void (*slsFreeFn)(void*);

struct _slsContentManager {
    GString *assets_dir;

    GHashTable *content;

    GHashTable *textures;
    GHashTable *sprites;
    GHashTable *shaders;
    GHashTable *meshes;

    char *(*get_asset_path)(slsContentManager *self, char const *path);

    slsContentManager* (*init)  (slsContentManager *self, char const *assets_dir);
    void (*dtor)                (slsContentManager *self);
};

slsContentManager *slsContentManager_new(char const *path);

slsContentManager *slsContentManager_init(slsContentManager *self, char const *assets_shortpath);

void slsContentManager_destroy(slsContentManager *self);

void sls_clear_hash(GHashTable *hash, slsFreeFn free_fn);


void sls_hash_texture_free(void * texture);
void sls_hash_sprite_free(void *sprite);
void sls_hash_shader_free(void * shader);
void sls_hash_mesh_free(void * mesh);



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

slsMesh *slsContentManager_loadExistingMesh(
    slsContentManager *self,
    char const *mesh_name,
    slsMesh *mesh);

GString *sls_get_assets_dir(char const *assets_shortpath);

char const *sls_get_home_dir();
char *slsContentManager_get_full_path(
    slsContentManager *self,
    char const *path);

#endif
