#ifndef __SLS_TYPE_GAME_WINDOW_H__
#define __SLS_TYPE_GAME_WINDOW_H__

#include "sls-glwindow.h"
#include "sls-statestack.h"

typedef struct _slsGameWindow slsGameWindow;
struct _slsGameWindow {
    slsGlWindow *super;
    slsStateStack *states;

    slsGameWindow *(*init)          (slsGameWindow *self, char const *caption);
    slsGameWindow *(*initWithSize)  (slsGameWindow *self, char const *caption, int w, int h);
    void (*dtor)                    (slsGameWindow *self);

    void (*run)                     (slsGameWindow *self);
};

slsGameWindow *slsGameWindow_alloc();
slsGameWindow *slsGameWindow_init(slsGameWindow *self, char const *caption);
slsGameWindow *slsGameWindow_initWithSize(slsGameWindow *self, char const *caption, int w, int h);

void slsGameWindow_dtor(slsGameWindow *self);
slsGameWindow *__slsGameWindow_create__(slsGameWindow *self, char const *caption, int w, int h);

void slsGameWindow_run(slsGameWindow *self);

#endif /*__SLS_TYPE_GAME_WINDOW_H__*/