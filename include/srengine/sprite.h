/**
 * this file includes a sprite structure
 * for rendering via SDL's rendering utilities
 */

#ifndef __SLS_SPRITE_H__
#define __SLS_SPRITE_H__

#include <SDL2/SDL.h>
#include <glib.h>
#include "window/window.h"

struct _slsSprite {
	GString *name;
	
	SDL_Rect subsprite_rect;
	SDL_Rect render_rect;

	SLint cols;
	SLint rows; // #columns in spritesheet
	SLint i;
	SLint j; // actively drawn column

	SLint position[2];

	/**
	 * By default, texture memory is owned externally.
	 * slsSprite will not modify or free data implicitly
	 */
	SDL_Texture *texture;

};

typedef struct _slsSprite slsSprite;


slsSprite *slsSprite_create(
	const char *name,
	SDL_Texture *texture,
	SLint rows, SLint cols,
	SLint i, SLint j
);

/**
 * Destroys sprite object
 * Opionally, you can pass pointers to 
 * get references to sprite's renderer and texture data
 */
void slsSprite_destroy(
	slsSprite *sprite,
	SDL_Texture *texture_ref
);

/**
 * updates sprites texture
 * return value: original sprite texture
 */
SDL_Texture *slsSprite_update_texture(
	slsSprite *sprite,
	SDL_Texture *texture,
	SLbool free_texture
);

void sls_set_subsprite(slsSprite *sprite, SLint i, SLint j);

void slsSprite_draw(SDL_Renderer *renderer, slsSprite *sprite);




#endif