#include "sls-content.h"
#include "sls-sprite.h"

#include "sls-mesh.h"
#include "sls-shader.h"
#include "sls-cont-container.h"

#include "../stdhdr.h"

slsContentManager *slsContentManager_create()
{
    slsContentManager *self = NULL;
    self = malloc (sizeof(slsContentManager));
    g_return_val_if_fail(self, NULL);

    int ndictionaries = 5;
    CFMutableDictionaryRef *dicts[5] = {&self->content, &self->textures, &self->sprites, &self->shaders, &self->meshes};
    for (int i=0; i < ndictionaries; i++) {
        *(dicts[i]) = CFDictionaryCreateMutable(
            NULL,
            0,
            &kCFCopyStringDictionaryKeyCallBacks,
            &slsContentContainer_callback
        );
    }

    return self;
}
void slsContentManager_destroy(slsContentManager *self)
{
    if (!self) {return;}

    int ndictionaries = 5;
    CFMutableDictionaryRef dicts[5] = {self->content, self->textures, self->sprites, self->shaders, self->meshes};
    for (int i=0; i < ndictionaries; i++) {
        if (dicts[i]) {
            CFRelease(dicts[i]);
        }
    }

    if (self) {free(self);}
}

void sls_hash_texture_free(gpointer texture)
{
    SDL_DestroyTexture((SDL_Texture *) texture);
}

void sls_hash_shader_free(gpointer shader)
{
    slsShader *self = shader;
    if (self->dtor != NULL)
    self->dtor(self);
}

void sls_hash_mesh_free(gpointer mesh)
{
    slsMesh *meshobj = mesh;
    slsMsg(meshobj, dtor);
}

SDL_Texture *slsContentManager_load_texture(
    slsContentManager *self,
    SDL_Renderer *renderer,
    char const *texture_key,
    char const *image_path)
{
    SDL_Surface *tmp_surface = NULL;
    SDL_Texture *texture = NULL;

    tmp_surface = IMG_Load(image_path);
    if (!tmp_surface) {
        g_critical("IMG_Load(): %s\n", IMG_GetError());
        g_return_val_if_reached(NULL);
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    

    return texture;
}


slsShader *slsContentManager_load_shader(
    slsContentManager *self,
    char const *shader_name,
    char const *vspath,
    char const *fspath)
{
    slsShader *shader = NULL;
    shader = slsShader_create(shader_name, vspath, fspath);
    g_return_val_if_fail(shader != NULL, NULL);


    return shader;
}

slsMesh *slsContentManager_loadExistingMesh(
    slsContentManager *self,
    char const *mesh_name,
    slsMesh *mesh)
{
    

    return mesh;
}