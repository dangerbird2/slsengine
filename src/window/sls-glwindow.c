#include "sls-glwindow.h"
#include "sls-window.h"
#include "../stdhdr.h"

#include <stdlib.h>

slsGlWindow *slsGlWindow_create(const char *caption, void *data)
{
	slsGlWindow *self = NULL;
	self = malloc(sizeof(slsGlWindow));
	g_return_val_if_fail(self, NULL);

	// instantiate super, return null if it fails
	self->super = NULL;
	self->super = slsWindow_create(caption, NULL);
	g_return_val_if_fail(self->super, NULL);


	self->name = self->super->name;

	// set slsGlWindow callbacks
	self->run = slsGlWndow_run;
	self->poll_events = slsGlWndow_poll_events;
	self->load_content = slsGlWndow_load_content;
	self->update = slsGlWndow_update;
	self->resize = slsGlWndow_resize;
	self->render = slsGlWndow_render;
	self->dtor = slsGlWindow_destroy;

	self->is_open = false;

	return self;

}

void *slsGlWindow_destroy(slsGlWindow *self)
{
	g_return_val_if_fail(self, NULL);
	void *data = self->data;

	if (self->super) {slsWindow_destroy(self->super);}
	if (self) {free(self);}

	return data;
}

void slsGlWndow_run	(slsGlWindow *self, void *data)
{
	self->is_open = true;
	while(self->is_open) {
		self->poll_events(self, data);

		self->update(self, 0.0, data);

		self->render(self, data);
	}
}
void slsGlWndow_poll_events	(slsGlWindow *self, void *data)
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			self->is_open = false;
		}
	}
}
void slsGlWndow_load_content (slsGlWindow *self, void *data){}
void slsGlWndow_update (slsGlWindow *self, double dt, void *data){}

void slsGlWndow_resize (slsGlWindow *self, int w, int h, void *data){}
void slsGlWndow_render (slsGlWindow *self, void *data){}