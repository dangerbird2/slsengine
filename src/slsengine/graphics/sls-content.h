#ifndef __SLS_CONTENT_H__
#define __SLS_CONTENT_H__

#include <glib-2.0/glib.h>
#include <SDL2/SDL.h>
#include "sls-sprite.h"
#include "../graphics/sls-shader.h"
#include "../graphics/sls-mesh.h"
#include "sls-cont-container.h"

typedef struct _slsContentManager slsContentManager;

struct _slsContentManager {
    
    CFMutableDictionaryRef content;

    CFMutableDictionaryRef textures;
    CFMutableDictionaryRef sprites;
    CFMutableDictionaryRef shaders;
    CFMutableDictionaryRef meshes;
};

slsContentManager *slsContentManager_create();
void slsContentManager_destroy(slsContentManager *self);



void sls_hash_texture_free(gpointer texture);
void sls_hash_shader_free(gpointer shader);
void sls_hash_mesh_free(gpointer mesh);



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
