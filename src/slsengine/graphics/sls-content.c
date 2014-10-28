#include "sls-content.h"
#include "sls-sprite.h"

#include "sls-mesh.h"
#include "sls-shader.h"


#include "../stdhdr.h"

static const slsContentManager slsContentManager_proto = {
        .textures = NULL,
        .sprites = NULL,
        .shaders = NULL,
        .meshes = NULL,
        .init = slsContentManager_init,
        .dtor = slsContentManager_destroy
};

slsContentManager *slsContentManager_alloc()
{
    slsContentManager *self = NULL;
    self = malloc (sizeof(slsContentManager));

    memcpy(self, &slsContentManager_proto, sizeof(slsContentManager));

    return self;
}

slsContentManager *slsContentManager_init(slsContentManager *self)
{
    if (!self) {return NULL;}

    memcpy(self, &slsContentManager_proto, sizeof(slsContentManager));

    

    return self;

error:
    log_err("slsContentManager_init failure");
    slsMsg(self, dtor);
    return NULL;
}

void sls_clear_hash(GHashTable *hash, slsFreeFn free_fn)
{

    

    
}

void slsContentManager_destroy(slsContentManager *self)
{
    if (!self) {return;}
    sls_clear_hash(self->textures, sls_hash_texture_free);
    sls_clear_hash(self->shaders, sls_hash_shader_free);
    sls_clear_hash(self->meshes, sls_hash_mesh_free);

    
    free(self);
}

void sls_hash_texture_free(void * texture)
{
    SDL_DestroyTexture((SDL_Texture *) texture);
}

void sls_hash_shader_free(void * shader)
{
    slsShader *self = shader;
    if (self->dtor != NULL)
    self->dtor(self);
}

void sls_hash_mesh_free(void * mesh)
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