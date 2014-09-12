#include "../stdhdr.h"
#include "sls-statestack.h"

static slsStateCallbacks const slsStateCallbacks_proto = {
    .dealloc = NULL,
    .start = NULL,
    .resize = NULL,
    .poll_events = NULL,
    .update = NULL,
    .draw = NULL
};

static const slsStateNode slsStateNode_proto = {
	.prev = NULL,
	.next = NULL,
	.host = NULL,

	.state_data = NULL,
    .state_callbacks = {},

	.init = slsStateNode_init,
	.dtor = slsStateNode_dtor,

};

slsStateNode *slsStateNode_alloc()
{
	slsStateNode *self = NULL;
	self = calloc(1, sizeof(slsStateNode));
	if (!self) {
		log_err("slsStateNode_alloc: memory error");
		return NULL;
	}
	memcpy(self, &slsStateNode_proto, sizeof(slsStateNode));
    self->state_callbacks = slsStateCallbacks_proto;

	return self;
}
slsStateNode *slsStateNode_init(slsStateNode *self)
{
	if (!self) {return NULL;}

	return self;
}
void slsStateNode_dtor(slsStateNode *self)
{
	if (!self) {return;}

    if (self->state_callbacks.dealloc) {
        self->state_callbacks.dealloc(self->state_data);
    }

	free(self);
}

slsStateNode *slsStateNode_new()
{
    slsStateNode *self = slsStateNode_alloc();
    if (!self) {return NULL;}
    slsMsg(self, init);
    return self;
}


/**
 * 
 * slsSceneStack functions
 * 
 */

static const slsStateStack slsStateStack_proto = {
	.top = NULL,
	.count = 0,
	.window = NULL,
	.init = slsStateStack_init,
	.dtor = slsStateStack_dtor,
	.clear = slsStateStack_clear,
	.push = slsStateStack_push,
	.peek = slsStateStack_peek,
	.pop = slsStateStack_pop
};

slsStateStack *slsStateStack_alloc()
{
	slsStateStack *self = NULL;
	self = calloc(1, sizeof(slsStateStack));
	if (!self) {
		log_err("slsStateStack_alloc: memory error");
		return NULL;
	}
	memcpy(self, &slsStateStack_proto, sizeof(slsStateStack));

	return self;
}

slsStateStack *slsStateStack_init(slsStateStack *self, slsGlWindow *window)
{
	self->window = window;
	return self;
}

void slsStateStack_dtor (slsStateStack *self)
{
	if (!self) {return;}
	slsMsg(self, clear);

	free(self);
}

void slsStateStack_clear(slsStateStack *self)
{
	while (self->top != NULL) {
		slsMsg(slsMsg(self, pop), dtor);
	}
}

void slsStateStack_push	(slsStateStack *self, slsStateNode *node)
{
	if ((!self) || (!node)) {return;}
	slsStateNode *top = self->top;
	
	node->next = top;
	node->prev = NULL;

	if (top) {top->prev = node;}

	self->count ++;
	self->top = node;
}
slsStateNode *slsStateStack_peek (slsStateStack *self)
{
	if (!self) {return NULL;}
    return self->top;
}
slsStateNode *slsStateStack_pop	(slsStateStack *self)
{
	slsStateNode *top = self->top;
	if (!top) {return NULL;}
	
	self->top = top->next;
	if (top->next) {top->next->prev = NULL;}

	self->count --;
	return top;
}

slsStateStack *slsStateStack_new(slsGlWindow *window)
{
    slsStateStack *self = slsStateStack_alloc();
    if (!self) {return NULL;}

    slsMsg(self, init, window);
    return self;
}
