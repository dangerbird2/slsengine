#include "../stdhdr.h"
#include "sls-gamewindow.h"
#include "sls-glwindow.h"
#include <time.h>

static const slsGameWindow sls_gamewindow_proto = {
    .super = NULL,
    .states = NULL,
    .is_open = false,
    .init = slsGameWindow_init,
    .initWithSize = slsGameWindow_initWithSize,
    .dtor = slsGameWindow_dtor,
    .poll_events = slsGameWindow_poll_events,
    .load_content = slsGameWindow_load_content,
    .update = slsGameWindow_update,
    .run= slsGameWindow_run
};

static slsGameWindow const *sls_gamewindow_class = &sls_gamewindow_proto;

slsGameWindow *slsGameWindow_alloc()
{
    return (slsGameWindow *)sls_objalloc(sls_gamewindow_class, sizeof(slsGlWindow));
}

slsGameWindow *_slsGameWindow_create(slsGameWindow *self, char const *caption, int w, int h)
{
    if (!self) {return NULL;}

    self->super = slsGlWindow_create(caption, (void*) self);
    check_mem(self->super);

    // create scene stack
    self->states = slsStateStack_new(self->super);

    // todo: add window manipulation methods to avoid direct SDL calls
    self->window = self->super->window;
    self->renderer = self->super->renderer;
    SDL_SetWindowSize(self->window, w, h);

    return self;
error:
    if (self && self->dtor) {
        slsMsg(self, dtor);
    }
    return NULL;
}

slsGameWindow *slsGameWindow_init(slsGameWindow *self, char const *caption)
{
    if (!self) {return NULL;}
    int def_w = 800;
    int def_h = 800;
    return _slsGameWindow_create(self, caption, def_w, def_h);
}
slsGameWindow *slsGameWindow_initWithSize(slsGameWindow *self, char const *caption, int w, int h)
{
    if (!self) {return NULL;}

    return _slsGameWindow_create(self, caption, w, h);
}

void slsGameWindow_run(slsGameWindow *self)
{
    time_t timeA, timeB;
    timeA = timeB = clock();

    while(self->is_open) {
        timeA = timeB;
        timeB = clock();
        double dt = sls_diffclock(timeA, timeB);

        slsMsg(self, poll_events);
        slsMsg(self, update, dt);
        slsMsg(self, render, dt);
        
        
    }
}

void slsGameWindow_poll_events (slsGameWindow *self)
{
    
    SDL_Event event;
    

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            self->is_open = false;
        }
        
    }

}
void slsGameWindow_load_content (slsGameWindow *self)
{

}

void slsGameWindow_update(slsGameWindow *self, double dt)
{

}

void slsGameWindow_render(slsGameWindow *self, double dt)
{

}

void slsGameWindow_dtor(slsGameWindow *self)
{
    if (!self) {return;}
    if (self->super) {slsMsg(self->super, dtor);}
    if (self->states) {slsMsg(self->states, dtor);}

    free (self);
}

void slsGameWindow_autofree(slsGameWindow **self_ptr)
{
    if (!self_ptr) {return;}

    slsMsg((*self_ptr), dtor);
}