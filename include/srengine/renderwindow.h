/**
 * slsRenderWindow is an alias of slsWindow
 * used for slsWindow Object that makes use of
 * SDL's rendering functions as opposed to openGL
 */

#ifndef __SLS_RENDER_WINDOW_H__
#define __SLS_RENDER_WINDOW_H__

#include "window.h"
#include "../types.h"
#include <SDL2/SDL.h>

typedef slsWindow slsRenderWindow;

slsRenderWindow *sls_create_renderWindow(int w, int h, const char *caption,
                                         void *user_data);

void *sls_free_RenderWindow(slsRenderWindow *window);

/**
 * @brief renderWindow main loop method
 * @details [long description]
 * 
 * @param self [description]
 * @param data [description]
 */
void renderWindow_run(slsRenderWindow *self, void *data);

void renderWindow_poll_events (slsRenderWindow *self, void *data);

void renderWindow_on_load(slsRenderWindow *self, void *data);

void renderWindow_on_update(slsRenderWindow *self, float dt, void *data);
void renderWindow_on_fixed_update(slsRenderWindow *self, float dt, void *data);

void renderWindow_on_resize(slsRenderWindow *self, int w, int h, void *data);
void renderWindow_on_draw(slsRenderWindow *self, void *data);

#endif