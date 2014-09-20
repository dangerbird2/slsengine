#include "../stdhdr.h"
#include "sls-gamewindow.h"

static const slsGameWindow slsGameWindow_proto = {
    .super = NULL,
    .states = NULL,
    .init = slsGameWindow_init,
    .initWithSize = slsGameWindow_initWithSize,
    .dtor = slsGameWindow_dtor,
    .run= slsGameWindow_run
};

slsGameWindow *slsGameWindow_alloc()
{
    slsGameWindow *self = NULL;
    self = calloc(1, sizeof(slsGameWindow));
    check_mem(self);
    memcpy(self, &slsGameWindow_proto, sizeof(slsGameWindow));
    return self;

error:
    return NULL;
}

slsGameWindow *__slsGameWindow_create__(slsGameWindow *self, char const *caption, int w, int h)
{
    if (!self) {return NULL;}

    self->super = slsGlWindow_create(caption, (void*) self);
    check_mem(self->super);

    // create scene stack
    self->states = slsStateStack_new(self->super);

    // todo: add window manipulation methods to avoid direct SDL calls
    SDL_SetWindowSize(self->super->window, w, h);

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
    return __slsGameWindow_create__(self, caption, def_w, def_h);
}
slsGameWindow *slsGameWindow_initWithSize(slsGameWindow *self, char const *caption, int w, int h)
{
    if (!self) {return NULL;}

    return __slsGameWindow_create__(self, caption, w, h);
}

void slsGameWindow_run(slsGameWindow *self)
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