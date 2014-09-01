/**
 * a wrapper structure for CSFML's sfRenderWindow,
 * allowing user to set callback methods for rendering
 *
 */

#ifndef __SLS_SFML_RENDER_WINDOW_H__
#define __SLS_SFML_RENDER_WINDOW_H__

#include "../stdhdr.h"



typedef struct _slsWindow slsWindow;

struct _slsWindow {
	GString *name;
	void *data;

	SDL_Window *window;
	SDL_Renderer *renderer;
};

slsWindow *slsWindow_create(const char *caption, void *data);
void *slsWindow_destroy(slsWindow *self);


#endif
