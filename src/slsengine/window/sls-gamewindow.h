#ifndef __SLS_TYPE_GAME_WINDOW_H__
#define __SLS_TYPE_GAME_WINDOW_H__

#include "sls-glwindow.h"
#include "sls-statestack.h"

typedef struct _slsGameWindow slsGameWindow;
struct _slsGameWindow {
    slsGlWindow *super;
    slsStateStack *states;
    bool is_open;

    /**
     * @brief pointer to SDL window object
     * @details note: memory not owned by this object. by destructing self->super,
     * window will free
     */
    SDL_Window *window;

    /**
     * @brief pointer to SDL renderer objectv
     * @details note: memory not owned by this object. by destructing self->super,
     * renderer will free
     */
    SDL_Renderer *renderer;

    slsGameWindow *(*init)          (slsGameWindow *self, char const *caption);
    slsGameWindow *(*initWithSize)  (slsGameWindow *self, char const *caption, int w, int h);
    void (*dtor)                    (slsGameWindow *self);

	void (*poll_events)				(slsGameWindow *self);
	void (*load_content)			(slsGameWindow *self);
	void (*update)					(slsGameWindow *self, double dt);

	void (*render)					(slsGameWindow *self, double dt);
    

    void (*run)                     (slsGameWindow *self);
};

slsGameWindow *slsGameWindow_alloc();
slsGameWindow *slsGameWindow_init(slsGameWindow *self, char const *caption);
slsGameWindow *slsGameWindow_initWithSize(slsGameWindow *self, char const *caption, int w, int h);

void slsGameWindow_dtor(slsGameWindow *self);
slsGameWindow *_slsGameWindow_create(slsGameWindow *self, char const *caption, int w, int h);

void slsGameWindow_run(slsGameWindow *self);

void slsGameWindow_poll_events	(slsGameWindow *self);
void slsGameWindow_load_content (slsGameWindow *self);

void slsGameWindow_update (slsGameWindow *self, double dt);

void slsGameWindow_autofree(slsGameWindow **self_ptr);

const slsGameWindow sls_gamewindow_class();

#define slsGameWindowAF slsAF(slsGameWindow_autofree)

#endif /*__SLS_TYPE_GAME_WINDOW_H__*/