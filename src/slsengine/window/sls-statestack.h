#ifndef __SLS_TYPE_STATESTACK_H__
#define __SLS_TYPE_STATESTACK_H__

typedef struct _slsStateNode slsStateNode;
typedef struct _slsStateStack slsStateStack;
typedef struct _slsStateCallbacks slsStateCallbacks;

#include <inttypes.h>
#include <SDL2/SDL.h>
#include "sls-glwindow.h"


struct _slsStateNode {
	slsStateNode *prev;
	slsStateNode *next;
	slsStateStack *host;

	void *data;

	slsStateNode *(*init)	(slsStateNode *self);

	void (*dtor)			(slsStateNode *self);

	void (*start)			(slsStateNode *self);

	void (*resize)			(slsStateNode *self, int w, int h);
	void (*poll_events)		(slsStateNode *self, SDL_Event *event);

	void (*update) 			(slsStateNode *self, double dt);
	void (*draw) 			(slsStateNode *self, double dt);

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
void slsStateNode_dtor(slsStateNode *self);

slsStateStack *slsStateStack_alloc();
slsStateStack *slsStateStack_init(slsStateStack *self, slsGlWindow *window);
void slsStateStack_dtor (slsStateStack *self);

void slsStateStack_clear(slsStateStack *self);
void slsStateStack_push	(slsStateStack *self, slsStateNode *node);
slsStateNode *slsStateStack_peek (slsStateStack *self);
slsStateNode *slsStateStack_pop	(slsStateStack *self);



#endif