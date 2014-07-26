/**
 * This file defines the basic structure for handling
 * program's window context. it includes function pointers
 * for callbacks as well as basic SDL structures for window,
 * input, and render handling
 * 
 * finally, includes a run callback for calling a user-defined
 * main loop
 * 
 * uses a prototype-based OOP model
 * 
 */

#ifndef __SLS_WINDOW_H__
#define __SLS_WINDOW_H__

#include <SDL2/SDL.h>
#include "../types.h"

struct _slsWindow {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_GLContext gl_context;

	SLbool use_gl;
	SLbool is_open;

	void *user_data;


	/**
	 * timer info
	 */
	float total_time;
	float elapsed_time;
	float delta_time;

	float fixed_update_timer;

	/**
	 * @brief byte array for storing SDL key state
	 * @details during initialization, call
	 * 	SDL_GetKeyboardState to load handler
	 * 	
	 * 	during update, cal SDL_PumpEvents to update
	 * 	state
	 */
	SLbyte *keyboard_state;

	/**
	 * Callback functions
	 */
    void (*run)(struct _slsWindow *self, void *data);
    void (*poll_events)(struct _slsWindow *self, void *data);

    void (*on_load)(struct _slsWindow *self, void *data);

    void (*on_update)(struct _slsWindow *self, float dt, void *data);
    void (*on_fixed_update)(struct _slsWindow *self, float dt, void *data);

    void (*on_resize)(struct _slsWindow *self, int w, int h, void *data);
    void (*on_draw)(struct _slsWindow *self, void *data);

};

typedef struct _slsWindow slsWindow;

slsWindow *sls_new_window(int w, int h, const char *caption, int sdl_flags,
													void *user_data);

/**
 * @brief frees window
 * @details [long description]
 * 
 * @param window [description]
 * @return pointer to window user data
 */
void *sls_free_window(slsWindow *window);

float get_delta_time(float last_time);

/**
 * typedef callbacks for later use
 */
typedef    void (*runCallback)(struct _slsWindow *self, void *data);
typedef    void (*eventCallback)(struct _slsWindow *self, void *data);

typedef    void (*loadCallback)(struct _slsWindow *self, void *data);

typedef    void (*updateCallback)(struct _slsWindow *self, float dt, void *data);

typedef    void (*resizeCallback)(struct _slsWindow *self, int w, int h, void *data);
typedef    void (*drawCallback)(struct _slsWindow *self, void *data);

#endif