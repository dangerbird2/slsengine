#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "../macros/dbg.h"
#include "behavior.h"

slsBehavior *slsBehavior_create(void *container)
{
	slsBehavior *self = malloc(sizeof(slsBehavior));
	check_mem(self);

	self->container = container;

	self->destroy = slsBehavior_destroy;

	self->start = slsBehavior_start;
	self->preload = slsBehavior_preload;
	self->update = slsBehavior_update;
	self->fixed_update = slsBehavior_fixed_update;
	self->draw = slsBehavior_draw;

	return self;

error:
	log_err("memory error: slsBehavior_create failed");
	return NULL;
}
void *slsBehavior_destroy(slsBehavior *self)
{
	check_mem(self);
	void *container = self->container;

	if(self != NULL) {
		free(self);
	}
	self = NULL;
	return container;

error:
	log_err("self is NULL. slsBehavior_destroy failed");
	return NULL;
}

void slsBehavior_start(slsBehavior *self)
{
	log_err("not implemented");
}
void slsBehavior_preload(slsBehavior *self)
{
	log_err("not implemented");
}
void slsBehavior_update(slsBehavior *self, double dt)
{
	log_err("not implemented");
}
void slsBehavior_fixed_update(slsBehavior *self, double dt)
{
	log_err("not implemented");
}

void slsBehavior_draw(slsBehavior *self)
{
	log_err("not implemented");
}