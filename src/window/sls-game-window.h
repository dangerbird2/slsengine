#ifndef __SLS_GAME_WINDOW_H__
#define __SLS_GAME_WINDOW_H__

#include "sls-window.h"

/**
 * Game window setup
 */

slsWindow *slsWindow_new_gameWindow();
void slsWindow_free_gameWindow(slsWindow *game_window);

/**
 * game window callback functions
 */
void sls_gameWindow_run            (slsWindow *self, void *userdata);
void sls_gameWindow_poll_events    (slsWindow *self, void *userdata);
void sls_gameWindow_load_content   (slsWindow *self, void *userdata);

void sls_gameWindow_update         (slsWindow *self, double dt, void *userdata);
void sls_gameWindow_fixed_update   (slsWindow *self, double dt, void *userdata);

void sls_gameWindow_resize         (slsWindow *self, int w, int h, void *userdata);

void sls_gameWindow_render         (slsWindow *self, void *userdata);



#endif
