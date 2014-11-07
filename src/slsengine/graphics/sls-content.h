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

    GHashTable *content;

    GHashTable *textures;
    GHashTable *sprites;
    GHashTable *shaders;
    GHashTable *meshes;
    slsContentManager* (*init)  (slsContentManager *self);
    void (*dtor)                (slsContentManager *self);
};

slsContentManager *slsContentManager_alloc();

slsContentManager *slsContentManager_init(slsContentManager *self);

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

#endif
