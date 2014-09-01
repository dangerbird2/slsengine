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

	self->window = self->super->window;
	self->renderer = self->super->renderer;

	if (!self->super) {
		free(self);
		g_return_val_if_reached(NULL);	
	}
	

	self->name = self->super->name;

	// set slsGlWindow callbacks
	self->run = slsGlWindow_run;
	self->poll_events = slsGlWindow_poll_events;
	self->load_content = slsGlWindow_load_content;
	self->update = slsGlWindow_update;
	self->resize = slsGlWindow_resize;
	self->render = slsGlWindow_render;
	self->dtor = slsGlWindow_destroy;

	// setup gl context
	sls_gl_init(self);

	self->is_open = false;

	return self;

}

void *slsGlWindow_destroy(slsGlWindow *self)
{
	g_return_val_if_fail(self, NULL);
	void *data = self->data;

	if (self->super) {slsWindow_destroy(self->super);}

	SDL_GL_DeleteContext(self->context);
	if (self) {free(self);}

	return data;
}

void slsGlWindow_run (slsGlWindow *self, void *data)
{
	self->is_open = true;

	while(self->is_open) {
		self->poll_events(self, data);

		self->update(self, 0.0, data);

		self->render(self, data);
		
	}
}
void slsGlWindow_poll_events	(slsGlWindow *self, void *data)
{
	
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			self->is_open = false;
		}
		
	}

}
void slsGlWindow_load_content (slsGlWindow *self, void *data)
{
	
}
void slsGlWindow_update (slsGlWindow *self, double dt, void *data)
{

}

void slsGlWindow_resize (slsGlWindow *self, int w, int h, void *data)
{
	glViewport(0, 0, w, h);
}

void slsGlWindow_render (slsGlWindow *self, void *data)
{
	glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);


	SDL_GL_SwapWindow(self->super->window);
}

void sls_gl_init(slsGlWindow *self)
{
	// enable opengl for SDL
	self->context = SDL_GL_CreateContext(self->super->window);

	// enable glew
	GLenum err = glewInit(); // returns GLEW_OK if glew initializes
	if (GLEW_OK != err) {
		// something is wrong with glew
		log_info("Error: %s", glewGetErrorString(err));
		g_return_if_reached();
	}

#ifndef __SLS_QUIET__
	// log glew and GL version
	int major, minor;
	major = minor = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	log_info("Using GLEW %s\nUsing GL version %i.%i",
		glewGetString(GLEW_VERSION), major, minor);

#endif

	// set GL clear color
	self->clear_color = (vec4f){1.f, 1.f, 1.f, 1.f};
	glClearColor(self->clear_color.x, self->clear_color.y, self->clear_color.z, self->clear_color.w);

	// enable gl features
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}