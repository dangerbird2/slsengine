#include "sls-content.h"
#include "sls-sprite.h"

#include <glib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

slsContentManager *slsContentManager_create()
{
    slsContentManager *self = NULL;
    self = malloc (sizeof(slsContentManager));
    g_return_val_if_fail(self != NULL, NULL);

    self->textures = g_hash_table_new_full(
        g_str_hash, g_str_equal,
        free,
        sls_hash_texture_free
    );

    return self;
}
void slsContentManager_destroy(slsContentManager *self)
{
    if (self->textures != NULL) {
        g_hash_table_unref(self->textures);
    }
    if (self != NULL) {free(self);}
}

void sls_hash_texture_free(gpointer data)
{
    SDL_DestroyTexture((SDL_Texture *) data);
}

SDL_Texture *slsContentManager_load_texture(
    slsContentManager *self,
    SDL_Renderer *renderer,
    char const *texture_key,
    char const *image_path)
{
    SDL_Surface *tmp_surface = NULL;
    SDL_Texture *texture = NULL;

    tmp_surface = IMG_Load(get_content_dir(image_path));
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
    char *texture_key_clone = g_strdup(texture_key);
    g_hash_table_insert(self->textures, texture_key_clone, texture);

    return texture;
}
