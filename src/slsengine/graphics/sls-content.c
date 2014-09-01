#include "sls-content.h"
#include "sls-sprite.h"

#include "../gl/sls-gl.h"
#include "../stdhdr.h"

slsContentManager *slsContentManager_create()
{
    slsContentManager *self = NULL;
    self = malloc (sizeof(slsContentManager));
    g_return_val_if_fail(self != NULL, NULL);

    self->textures = g_hash_table_new_full(
        g_str_hash, g_str_equal,
        free,
        sls_hash_texture_free);

    self->shaders = g_hash_table_new_full(
        g_str_hash, g_str_equal,
        free,
        sls_hash_shader_free);

    self->meshes = g_hash_table_new_full(
        g_str_hash, g_str_equal,
        free,
        sls_hash_mesh_free);

    return self;
}
void slsContentManager_destroy(slsContentManager *self)
{
    if (self->textures) {
        g_hash_table_unref(self->textures);
    }

    if (self->shaders) {
        g_hash_table_unref(self->shaders);
    }

    if (self->meshes) {
        g_hash_table_unref(self->meshes);
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
    if (!texture) {
        g_critical("SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        g_return_val_if_reached(NULL);
    }
    // add texture to texture hash table
    char const *texture_key_clone = g_strdup(texture_key);
    g_hash_table_insert(self->textures, (gpointer) texture_key_clone, texture);

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

    char const *shader_key = g_strdup(shader_name);

    g_hash_table_insert(self->shaders, (gpointer) shader_key, shader);

    return shader;
}

slsMesh *slsContentManager_loadExistingMesh(
    slsContentManager *self,
    char const *mesh_name,
    slsMesh *mesh)
{
    char const *mesh_key = g_strdup(mesh_name);
    g_hash_table_insert(self->meshes, (void*) mesh_key, (void*) mesh);

    return mesh;
}