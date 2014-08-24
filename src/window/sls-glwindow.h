#ifndef __SLS_GL_WINDOW_H__
#define __SLS_GL_WINDOW_H__
#include "../stdhdr.h"
#include "sls-window.h"

typedef struct _slsGlWindow slsGlWindow;

/**
 * @brief window management structure
 * @details structure managing SDL openGL contextm including main loop callbacks. "inherrits" slsWindow via a pointer to a window object.
 * 
 */
struct _slsGlWindow {
	GString *name; // note: a pointer to slsWindow's name
	void *data;

	slsWindow *super;
	SLbool is_open;
	SDL_GLContext context;

	vec4f clear_color;

	/**
	 * @brief calls main loop
	 * @details [long description]
	 * 
	 * @param n "self"
	 * @param data user-defined data
	 * 
	 * @return void
	 */
	void (*run)				(slsGlWindow *self, void *data);

	/**
	 * @brief polls SDL events
	 * @details [long description]
	 * 
	 * @param n "self"
	 * @param data user-defined data
	 * 
	 * @return void
	 */
	void (*poll_events)		(slsGlWindow *self, void *data);
	void (*load_content)	(slsGlWindow *self, void *data);
	void (*update)			(slsGlWindow *self, double dt, void *data);
	
	void (*resize)			(slsGlWindow *self, int w, int h, void *data);
	void (*render)			(slsGlWindow *self, void *data);
	void *(*dtor)			(slsGlWindow *self);
};

slsGlWindow *slsGlWindow_create(const char *caption, void *data);
void *slsGlWindow_destroy(slsGlWindow *self);

void slsGlWindow_run	(slsGlWindow *self, void *data);
void slsGlWindow_poll_events	(slsGlWindow *self, void *data);
void slsGlWindow_load_content (slsGlWindow *self, void *data);
void slsGlWindow_update (slsGlWindow *self, double dt, void *data);

void slsGlWindow_resize (slsGlWindow *self, int w, int h, void *data);
void slsGlWindow_render (slsGlWindow *self, void *data);

void sls_gl_init(slsGlWindow *self);

#endif