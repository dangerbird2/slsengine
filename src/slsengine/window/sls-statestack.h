#ifndef __SLS_TYPE_STATESTACK_H__
#define __SLS_TYPE_STATESTACK_H__



#include <inttypes.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// foreward declaration of slsGameWindow
typedef struct _slsGameWindow slsGameWindow;

typedef struct _slsStateNode slsStateNode;
typedef struct _slsStateStack slsStateStack;
typedef struct _slsStateCallbacks slsStateCallbacks;

struct _slsStateCallbacks {
    void (*end)   			(slsStateNode *state);

    void (*start)			(slsStateNode *state);

    void (*resize)			(slsStateNode *state, int w, int h);
    void (*poll_events)		(slsStateNode *state, SDL_Event *event);

    void (*update) 			(slsStateNode *state, double dt);
    void (*draw) 			(slsStateNode *state, double dt);
};


struct _slsStateNode {
	slsStateNode *prev;
	slsStateNode *next;
	slsStateStack *host;

	void *state_data;
	// anonymous union allows calling calllback functions
	// as struct member
	
    slsStateCallbacks callbacks;


	slsStateNode *(*init)	(slsStateNode *self);
	void (*dtor)			(slsStateNode *self);


};

struct _slsStateStack {
	slsStateNode *top;
	int32_t count;

	// indicates whether scene memory is managed by stack
	// scenes can be managed by the stack, or by external
	// memory mgmt. defaults to true
	bool owns_scenes;

	slsGameWindow *window;

	slsStateStack *(*init)	(slsStateStack *self, slsGameWindow *window);
	void (*dtor)			(slsStateStack *self);
	void (*clear)			(slsStateStack *self);

	void (*push)			(slsStateStack *self, slsStateNode *node);
	slsStateNode *(*peek)	(slsStateStack *self);
	slsStateNode *(*pop)	(slsStateStack *self);
};


slsStateNode *slsStateNode_init(slsStateNode *self);
slsStateNode *slsStateNode_new();
void slsStateNode_dtor(slsStateNode *self);

slsStateStack *slsStateStack_init(slsStateStack *self, slsGameWindow *window);
slsStateStack *slsStateStack_new(slsGameWindow *window);
void slsStateStack_dtor (slsStateStack *self);

void slsStateStack_clear(slsStateStack *self);
void slsStateStack_push	(slsStateStack *self, slsStateNode *node);
slsStateNode *slsStateStack_peek (slsStateStack *self);
slsStateNode *slsStateStack_pop	(slsStateStack *self);

const slsStateNode sls_statenode_class();
const slsStateStack sls_statestack_class();


#endif