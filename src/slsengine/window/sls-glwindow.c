#include "sls-glwindow.h"
#include "sls-window.h"
#include "sls-clock.h"
#include "../stdhdr.h"


#include <stdlib.h>

static const slsGlWindow slsGlWindow_proto = {
	.name = NULL,
	.data = NULL,
	.is_open = false,
	.window = NULL,
	.renderer = NULL,
	.clear_color = {1.f, 1.f, 1.f, 1.f},
	.run = slsGlWindow_run,
	.poll_events = slsGlWindow_poll_events,
	.load_content = slsGlWindow_load_content,
	.update = slsGlWindow_update,
	.resize = slsGlWindow_resize,
	.render = slsGlWindow_render,
	.dtor = slsGlWindow_destroy
};

slsGlWindow *slsGlWindow_create(const char *caption, void *data)
{
	slsGlWindow *self = NULL;
	self = malloc(sizeof(slsGlWindow));
	g_return_val_if_fail(self, NULL);

	memcpy(self, &slsGlWindow_proto, sizeof(slsGlWindow));

	self->super = slsWindow_create(caption, data);
	if (!self->super) {
		free(self);
		g_return_val_if_reached(NULL);	
	}
	self->name = self->super->name;
	self->window = self->super->window;
	self->renderer = self->super->renderer;

	// setup gl context
	sls_gl_init(self);

	return self;
}

void *slsGlWindow_destroy(slsGlWindow *self)
{
	g_return_val_if_fail(self, NULL);
	void *data = self->data;

	if (self->super) {slsWindow_destroy(self->super);}

	SDL_GL_DeleteContext(self->context);
	free(self);

	return data;
}

void slsGlWindow_run (slsGlWindow *self)
{
	#if 0
	self->is_open = true;

	uint64_t timeA, timeB;
	timeA = timeB = clock();

	while(self->is_open) {
		timeA = timeB;
		timeB = clock();
		double dt = sls_diffclock(timeA, timeB);

		slsMsg(self, poll_events);
		slsMsg(self, update, dt);
		slsMsg(self, render, dt);
		
		
	}

	#endif
}
void slsGlWindow_poll_events (slsGlWindow *self)
{
	
	SDL_Event event;
	

	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			self->is_open = false;
		}
		
	}

}
void slsGlWindow_load_content (slsGlWindow *self)
{
	
}
void slsGlWindow_update (slsGlWindow *self, double dt)
{
	
}

void slsGlWindow_resize (slsGlWindow *self, int w, int h)
{
	glViewport(0, 0, w, h);
}

void slsGlWindow_render (slsGlWindow *self, double dt)
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