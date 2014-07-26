#include "sls-window.h"

#include <SDL2/SDL.h>
#include <glib.h>

#include "../types.h"
#include "../macros/dbg.h"
#include "sls-window.h"

#include <stdlib.h>
#include <string.h>

static int window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
static int window_height = 480;
static int window_width = 640;

slsWindow *slsWindow_create(const char *caption, void *data)
{
	slsWindow *self = NULL;
	self = malloc(sizeof(slsWindow));

	// ensure self allocated correctly
	g_return_val_if_fail(self != NULL, NULL);

	// create window name
	self->name = g_string_new(caption);
	self->is_open = false;

	// create window & renderer

	int window_created = SDL_CreateWindowAndRenderer (
		window_width, window_height, window_flags,
		&self->window, &self->renderer
	);
	if (window_created < 0) {
		g_printerr("%s\n", SDL_GetError());
		g_return_val_if_reached(NULL);
	}
	SDL_SetWindowTitle(self->window, self->name->str);
	//set clear color

	self->clear_color = (SDL_Color) {0x1F, 0x37, 0x68, 255};
	self->data = data;
	// clear callbacks
	slsWindow_clear_callbacks(self);

	return self;
}

void slsWindow_clear_callbacks(slsWindow *self)
{
	// set callbacks to NULL
	self->run = NULL;
	self->poll_events = NULL;
	self->load_content = NULL;
	self->update = NULL;
	self->fixed_update = NULL;
	self->resize = NULL;
	self->render = NULL;
}

void *slsWindow_destroy(slsWindow *self)
{
	// this function will preserve and return user data
	g_return_val_if_fail(self != NULL, NULL);
	void *data = self->data;

	if (self->window) {SDL_DestroyWindow(self->window);}
	if (self->renderer) {SDL_DestroyRenderer(self->renderer);}
	if (self->name) {g_string_free(self->name, TRUE);}

	if (self) {free(self);}

	return data;
}
