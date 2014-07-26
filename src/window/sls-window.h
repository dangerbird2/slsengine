/**
 * a wrapper structure for CSFML's sfRenderWindow,
 * allowing user to set callback methods for rendering
 *
 */

#ifndef __SLS_SFML_RENDER_WINDOW_H__
#define __SLS_SFML_RENDER_WINDOW_H__

#include <SDL2/SDL.h>
#include <glib.h>
#include "../types.h"


typedef struct _slsWindow slsWindow;

struct _slsWindow {
	GString *name;
	void *data;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Color clear_color;

	SLbool is_open;

	void (*run)				(slsWindow *self, void *data);
	void (*poll_events)		(slsWindow *self, void *data);
	void (*load_content)	(slsWindow *self, void *data);
	void (*update)			(slsWindow *self, double dt, void *data);
	void (*fixed_update)	(slsWindow *self, double dt, void *data);
	void (*resize)			(slsWindow *self, int w, int h, void *data);
	void (*render)			(slsWindow *self, void *data);
};

slsWindow *slsWindow_create(const char *caption, void *data);
void *slsWindow_destroy(slsWindow *self);

// sets all callback functions to NULL
void slsWindow_clear_callbacks(slsWindow *self);

#endif
