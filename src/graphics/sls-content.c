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
    self->sprites = g_hash_table_new_full(
        g_str_hash, g_str_equal,
        free,
        sls_hash_sprite_free
    );

    return self;
}
void slsContentManager_destroy(slsContentManager *self)
{
    if (self->textures != NULL) {
        g_hash_table_unref(self->textures);
    }
    if (self->sprites != NULL) {
        g_hash_table_unref(self->sprites);
    }
    if (self != NULL) {free(self);}
}

void sls_hash_texture_free(gpointer data)
{
    SDL_DestroyTexture((SDL_Texture *) data);
}

void sls_hash_sprite_free(gpointer data)
{
    slsSprite_destroy((slsSprite *) data);
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

slsSprite *slsContentManager_load_sprite(
    slsContentManager *self,
    char const *sprite_key,
    char const *tgt_texture_key,
    SDL_Rect const * dest_rect,
    SDL_Rect const * src_rect)
{
    char *sprite_key_clone = g_strdup(sprite_key);
    g_return_val_if_fail(self != NULL, NULL);
    SDL_Texture *tex = g_hash_table_lookup(self->textures, tgt_texture_key);
    g_return_val_if_fail(tex != NULL, NULL);

    slsSprite *sprite = NULL;
    sprite = slsSprite_create(tex, dest_rect, src_rect);
    g_return_val_if_fail(sprite != NULL, NULL);

    g_hash_table_insert(self->sprites, sprite_key_clone, sprite);
    return sprite;
}

char *get_content_dir(char const *path)
{
    return (char *)path;
}
