#ifndef __SLS_GL_WINDOW_H__
#define __SLS_GL_WINDOW_H__
#include "../stdhdr.h"
#include "sls-window.h"

typedef struct _slsGlWindow slsGlWindow;

struct _slsGlWindow {
	GString *name; // note: a pointer to slsWindow's name
	void *data;

	slsWindow *super;
	SLbool is_open;

	void (*run)				(slsGlWindow *self, void *data);
	void (*poll_events)		(slsGlWindow *self, void *data);
	void (*load_content)	(slsGlWindow *self, void *data);
	void (*update)			(slsGlWindow *self, double dt, void *data);
	
	void (*resize)			(slsGlWindow *self, int w, int h, void *data);
	void (*render)			(slsGlWindow *self, void *data);
	void *(*dtor)			(slsGlWindow *self);
};

slsGlWindow *slsGlWindow_create(const char *caption, void *data);
void *slsGlWindow_destroy(slsGlWindow *self);

void slsGlWndow_run	(slsGlWindow *self, void *data);
void slsGlWndow_poll_events	(slsGlWindow *self, void *data);
void slsGlWndow_load_content (slsGlWindow *self, void *data);
void slsGlWndow_update (slsGlWindow *self, double dt, void *data);

void slsGlWndow_resize (slsGlWindow *self, int w, int h, void *data);
void slsGlWndow_render (slsGlWindow *self, void *data);

#endif