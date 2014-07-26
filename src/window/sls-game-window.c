#include "sls-game-window.h"

#include <SDL2/SDL.h>
#include <glib.h>
#include "../types.h"

static char *game_window_name = "game_window";

slsWindow *slsWindow_new_gameWindow()
{
    slsWindow *self = NULL;
    self = slsWindow_create(game_window_name, NULL);
    g_return_val_if_fail(self != NULL, NULL);

    self->run = sls_gameWindow_run;
    self->poll_events = sls_gameWindow_poll_events;
    self->load_content = sls_gameWindow_load_content;
    self->update = sls_gameWindow_update;
    self->fixed_update = sls_gameWindow_fixed_update;
    self->resize = sls_gameWindow_resize;
    self->render = sls_gameWindow_render;

    return self;
}
void slsWindow_free_gameWindow(slsWindow *game_window)
{
    slsWindow_destroy(game_window);
}

void sls_gameWindow_run (slsWindow *self, void *userdata)
{
    self->is_open = true;
    while (self->is_open) {
        self->poll_events(self, NULL);

        self->update(self, 0.0, NULL);

        self->render(self, NULL);
    }
}
void sls_gameWindow_poll_events (slsWindow *self, void *userdata)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            self->is_open = false;
        }
    }
}
void sls_gameWindow_load_content (slsWindow *self, void *userdata) { }

void sls_gameWindow_update (slsWindow *self, double dt, void *userdata) { }
void sls_gameWindow_fixed_update (slsWindow *self, double dt, void *userdata) { }

void sls_gameWindow_resize (slsWindow *self, int w, int h, void *userdata) { }

void sls_gameWindow_render (slsWindow *self, void *userdata)
{
    SDL_SetRenderDrawColor(
        self->renderer, self->clear_color.r, self->clear_color.g,
        self->clear_color.b, self->clear_color.a);
    SDL_RenderClear(self->renderer);

    // todo: draw logic

    SDL_RenderPresent(self->renderer);
}
