#ifndef __SLS_GL_WINDOW_H__
#define __SLS_GL_WINDOW_H__
#include "../stdhdr.h"
#include "sls-window.h"

typedef struct _slsGlWindow slsGlWindow;

typedef enum slsWindowRenderMode {
	SLS_WINDOW_SDL_RENDER,
	SLS_WINDOW_OGL_RENDER,
	SLS_WINDOW_GLES_RENDER
} slsWindowRenderMode;
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

	SDL_Window *window;
	SDL_Renderer *renderer;

	vec4f clear_color;

	/**
	 * @brief calls main loop
	 * @details [long description]
	 * 
	 * @param n "self"
	 * @param state_data user-defined state_data
	 * 
	 * @return void
	 */
	void (*run)				(slsGlWindow *self);

	/**
	 * @brief polls SDL events
	 * @details [long description]
	 * 
	 * @param n "self"
	 * @param state_data user-defined state_data
	 * 
	 * @return void
	 */
	void (*poll_events)		(slsGlWindow *self);
	void (*load_content)	(slsGlWindow *self);
	void (*update)			(slsGlWindow *self, double dt);
	
	void (*resize)			(slsGlWindow *self, int w, int h);
	void (*render)			(slsGlWindow *self, double dt);

	void (*clear)			(slsGlWindow *self, float r, float g, float b, float a);
	void (*swap_buffers)	(slsGlWindow *self);

	void *(*dtor)			(slsGlWindow *self);
};

slsGlWindow *slsGlWindow_create(const char *caption, void *data);
void *slsGlWindow_destroy(slsGlWindow *self);

void slsGlWindow_run	(slsGlWindow *self) slsDeprecated; 
void slsGlWindow_poll_events	(slsGlWindow *self) slsDeprecated;
void slsGlWindow_load_content (slsGlWindow *self) slsDeprecated;
void slsGlWindow_update (slsGlWindow *self, double dt) slsDeprecated;

void slsGlWindow_resize (slsGlWindow *self, int w, int h);
void slsGlWindow_render (slsGlWindow *self, double dt);

void sls_gl_init(slsGlWindow *self);

#endif