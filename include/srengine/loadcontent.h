/**
 * This file includes media loading functions, as well as a content
 * management structure
 */

#ifndef __SLS_LOAD_CONTENT_H__
#define __SLS_LOAD_CONTENT_H__

#include <SDL2/SDL.h>
#include <glib.h>

SDL_Texture *sls_load_texture(
	SDL_Renderer *renderer,
	const char* local_path
);

struct _slsMediaCache {
	GHashTable *sdl_textures;
	GHashTable *sdl_surfaces;
	GHashTable *etc;
};

typedef struct _slsMediaCache slsMediaCache;

slsMediaCache *slsMediaCache_create();
void slsMediaCache_destroy(slsMediaCache *cache);

#endif