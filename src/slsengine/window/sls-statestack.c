#include "../stdhdr.h"
#include "sls-statestack.h"

static const slsStateNode slsStateNode_proto = {
	.prev = NULL,
	.next = NULL,
	.host = NULL,
	.data = NULL,

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
	free(self);
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

}
slsStateNode *slsStateStack_pop	(slsStateStack *self)
{
	slsStateNode *node = self->top;
	if (!node) {return NULL;}
	
	self->top = node->next;
	if (node->next) {node->next->prev = NULL;}

	self->count --;
	return node;
}