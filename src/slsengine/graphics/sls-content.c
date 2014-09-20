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

    check_mem(apr_pool_create_core(&self->pool) == APR_SUCCESS);
    apr_hash_t **hash_tables[] = {
        &(self->textures),
        &(self->sprites),
        &(self->shaders),
        &(self->meshes),
        NULL};
    for (int i=0; hash_tables[i] != NULL; i++) {
        *(hash_tables[i]) = apr_hash_make(self->pool);
        check_mem(*(hash_tables[i]));
    }

    return self;

error:
    log_err("slsContentManager_init failure");
    slsMsg(self, dtor);
    return NULL;
}

void sls_clear_hash(apr_pool_t *pool, apr_hash_t *hash, slsFreeFn free_fn)
{

    if ((!hash ) || (!free_fn)) {return;}
    for (apr_hash_index_t *hi = apr_hash_first(pool, hash);
         hi;
         hi = apr_hash_next(hi)) {
        void *val = NULL;
        apr_hash_this(hi, NULL, NULL, &val);
        if (val) {
            free_fn(val);
        }
    }

    
}

void slsContentManager_destroy(slsContentManager *self)
{
    if (!self) {return;}
    sls_clear_hash(self->pool, self->textures, sls_hash_texture_free);
    sls_clear_hash(self->pool, self->shaders, sls_hash_shader_free);
    sls_clear_hash(self->pool, self->meshes, sls_hash_mesh_free);

    // destroy memory pool
    if (self->pool) {
        apr_pool_destroy(self->pool);
    }

    if (self) {free(self);}
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