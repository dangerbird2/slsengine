#include "../stdhdr.h"
#include "sls-gamewindow.h"
#include "sls-glwindow.h"
#include "sls-clock.h"
#include "sls-statestack.h"
#include <time.h>

void _slsGameWindow_handle_wevent(slsGameWindow *self, SDL_WindowEvent const *wevent);

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
    .render = slsGameWindow_render,
    .run= slsGameWindow_run
};

const slsGameWindow sls_gamewindow_class()
{
    return sls_gamewindow_proto;
}



slsGameWindow *slsGameWindow_alloc()
{
    return sls_objalloc(&sls_gamewindow_proto, sizeof(slsGameWindow));
}

slsGameWindow *_slsGameWindow_create(slsGameWindow *self, char const *caption, int w, int h)
{
    if (!self) {return NULL;}

    // set self to class prototype
    *self = sls_gamewindow_proto;

    self->super = slsGlWindow_create(caption, NULL);
    check_mem(self->super);

    // create scene stack
    self->states = slsStateStack_new(self);
    check_mem(self->states)
    self->states->window = self;

    // todo: add window manipulation methods to avoid direct SDL calls
    self->window = self->super->window;
    self->renderer = self->super->renderer;
    SDL_SetWindowSize(self->window, w, h);

    // load content
    self->mgr = slsContentManager_new("projects/slsengine/content");
    check_mem(self->mgr);
    if (self->load_content) {
        slsMsg(self, load_content);
    }

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
    self->is_open = true;

    while(self->is_open) {
        timeA = timeB;
        timeB = clock();
        double dt = sls_diffclock(timeA, timeB);

        slsMsg(self, poll_events);
        slsMsg(self, update, dt);
        slsMsg(self, render, dt);
        
        
    }
}

void _slsGameWindow_handle_wevent(slsGameWindow *self, SDL_WindowEvent const *wevent)
{

    if (wevent->event == SDL_WINDOWEVENT_RESIZED) {
        int w = wevent->data1;
        int h = wevent->data2;
        if (self->super && self->super->resize) {
            slsMsg(self->super, resize, w, h);
        }

        slsStateNode *top = self->states->top;
        if (top) {
            slsNodeMsg(top, resize, w, h);
        }
    }
}

void slsGameWindow_poll_events (slsGameWindow *self)
{
    
    SDL_Event event;
    slsStateNode *top = self->states->top;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            self->is_open = false;
        } else if (event.type == SDL_WINDOWEVENT) {
            _slsGameWindow_handle_wevent(self, &(event.window));
        }

        if (top) {
            slsNodeMsg(top, poll_events, &event);
        }
    }

}
void slsGameWindow_load_content (slsGameWindow *self)
{

}

void slsGameWindow_update(slsGameWindow *self, double dt)
{
    slsStateNode *top = self->states->top;
    if (top) {
        slsNodeMsg(top, update, dt);
    }
}

void slsGameWindow_render(slsGameWindow *self, double dt)
{
    check(self->super, "slsGlWindow missing");

    slsMsg(self->super, clear);

    slsStateNode *top = self->states->top;
    if (top) {
        slsNodeMsg(top, draw, dt);
    }

    slsMsg(self->super, swap_buffers);

    return;
error:
    return;
}

void slsGameWindow_dtor(slsGameWindow *self)
{
    if (!self) {return;}
    if (self->super) {slsMsg(self->super, dtor);}
    if (self->states) {slsMsg(self->states, dtor);}
    if (self->mgr) {slsMsg(self->mgr, dtor);}

    free (self);
}

void slsGameWindow_autofree(slsGameWindow **self_ptr)
{
    if (!self_ptr) {return;}

    slsMsg((*self_ptr), dtor);
}