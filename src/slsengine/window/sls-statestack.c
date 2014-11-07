#include "../stdhdr.h"
#include "sls-statestack.h"
#include "sls-gamewindow.h"

static slsStateCallbacks const slsStateCallbacks_proto = {
    .end = NULL,
    .start = NULL,
    .resize = NULL,
    .poll_events = NULL,
    .update = NULL,
    .draw = NULL
};

static const slsStateNode sls_statenode_proto = {
	.prev = NULL,
	.next = NULL,
	.host = NULL,

	.state_data = NULL,
    .callbacks = {
	    .end = NULL,
	    .start = NULL,
	    .resize = NULL,
	    .poll_events = NULL,
	    .update = NULL,
	    .draw = NULL
	},

	.init = slsStateNode_init,
	.dtor = slsStateNode_dtor,

};


slsStateNode *slsStateNode_init(slsStateNode *self)
{
	if (!self) {return NULL;}
	*self = sls_statenode_proto;

	return self;
}
void slsStateNode_dtor(slsStateNode *self)
{
	if (!self) {return;}

    if (self->callbacks.end) {
        self->callbacks.end(self);
    }

	free(self);
}

slsStateNode *slsStateNode_new()
{
    slsStateNode *self =  sls_objalloc(&sls_statenode_proto, sizeof(slsStateNode));
    if (!self) {return NULL;}
    slsMsg(self, init);
    return self;
}


/**
 * 
 * slsSceneStack functions
 * 
 */

static const slsStateStack sls_statestack_proto = {
	.top = NULL,
	.count = 0,
	.window = NULL,
	.owns_scenes = true,
	.init = slsStateStack_init,
	.dtor = slsStateStack_dtor,
	.clear = slsStateStack_clear,
	.push = slsStateStack_push,
	.peek = slsStateStack_peek,
	.pop = slsStateStack_pop
};

slsStateStack *slsStateStack_init(slsStateStack *self, slsGameWindow *window)
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
		slsStateNode *node = slsMsg(self, pop);
		// only destruct scene if stack owns scene memory
		if (self->owns_scenes) {
			slsMsg(node, dtor);
		}
	}
}

void slsStateStack_push	(slsStateStack *self, slsStateNode *node)
{
	if ((!self) || (!node)) {return;}
	slsStateNode *top = self->top;
	
	node->next = top;
	node->prev = NULL;
	node->host = self;
	if (node->callbacks.start) {
		slsMsg(node, callbacks.start);
	}

	if (top) {top->prev = node;}

	++self->count;
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
	top->host = NULL;

	--self->count;
	return top;
}

slsStateStack *slsStateStack_new(slsGameWindow *window)
{
    slsStateStack *self = sls_objalloc(&sls_statestack_proto, sizeof(slsStateStack));
    if (!self) {return NULL;}

    slsMsg(self, init, window);
    return self;
}

const slsStateNode sls_statenode_class()
{
	return sls_statenode_proto;

}
const slsStateStack sls_statestack_class()
{
	return sls_statestack_proto;
}