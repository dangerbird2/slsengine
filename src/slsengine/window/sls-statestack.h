#ifndef __SLS_TYPE_STATESTACK_H__
#define __SLS_TYPE_STATESTACK_H__



#include <inttypes.h>
#include <SDL2/SDL.h>
#include "sls-glwindow.h"


typedef struct _slsStateNode slsStateNode;
typedef struct _slsStateStack slsStateStack;
typedef struct _slsStateCallbacks slsStateCallbacks;

struct _slsStateCallbacks {
    void (*dealloc)    (void *state_data);

    void (*start)			(void *state_data);

    void (*resize)			(void *state_data, int w, int h);
    void (*poll_events)		(void *state_data, SDL_Event *event);

    void (*update) 			(void *state_data, double dt);
    void (*draw) 			(void *state_data, double dt);
};


struct _slsStateNode {
	slsStateNode *prev;
	slsStateNode *next;
	slsStateStack *host;

	void *state_data;
    slsStateCallbacks state_callbacks;

	slsStateNode *(*init)	(slsStateNode *self);
	void (*dtor)			(slsStateNode *self);


};

struct _slsStateStack {
	slsStateNode *top;
	int32_t count;

	slsGlWindow *window;

	slsStateStack *(*init)	(slsStateStack *self, slsGlWindow *window);
	void (*dtor)			(slsStateStack *self);
	void (*clear)			(slsStateStack *self);

	void (*push)			(slsStateStack *self, slsStateNode *node);
	slsStateNode *(*peek)	(slsStateStack *self);
	slsStateNode *(*pop)	(slsStateStack *self);
};

slsStateNode *slsStateNode_alloc();
slsStateNode *slsStateNode_init(slsStateNode *self);
slsStateNode *slsStateNode_new();
void slsStateNode_dtor(slsStateNode *self);

slsStateStack *slsStateStack_alloc();
slsStateStack *slsStateStack_init(slsStateStack *self, slsGlWindow *window);
slsStateStack *slsStateStack_new(slsGlWindow *window);
void slsStateStack_dtor (slsStateStack *self);

void slsStateStack_clear(slsStateStack *self);
void slsStateStack_push	(slsStateStack *self, slsStateNode *node);
slsStateNode *slsStateStack_peek (slsStateStack *self);
slsStateNode *slsStateStack_pop	(slsStateStack *self);



#endif