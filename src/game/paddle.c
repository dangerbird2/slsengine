#include "paddle.h"
#include "behavior.h"

#include <SFML/Graphics.h>
#include "../macros/dbg.h"

#include <stdlib.h>


void paddle_update(slsBehavior * self, double dt);
void paddle_fixed_update(slsBehavior * self, double dt);
void paddle_start(slsBehavior * self);
void paddle_preload(slsBehavior * self);
void paddle_draw(slsBehavior * self);

slsPongPaddle *slsPongPaddle_create(
	sfSprite *sprite,
	sfRenderWindow *window)
{
	slsPongPaddle *self = malloc(sizeof(slsPongPaddle));
	check_mem(self);

	self->sprite = sprite;
	self->window = window;
	self->position = (sfVector2f) {0.0f, 0.0f};

	// self->behavior->data is now pointer to self
	self->behavior = slsBehavior_create(self);
	

	// set behavior callbacks
	self->behavior->start = paddle_start;
	self->behavior->preload = paddle_preload;
	self->behavior->update = paddle_update;
	self->behavior->fixed_update = paddle_fixed_update;
	self->behavior->draw = paddle_draw;
	
	return self;
error:
	log_err("slsPongPaddle_create memory failure");
	return NULL;
}
void slsPongPaddle_destroy(slsPongPaddle *self){

	self->behavior->destroy(self->behavior);

	free(self);
}

void paddle_update(slsBehavior * self, double dt){ }
void paddle_fixed_update(slsBehavior * self, double dt){ }
void paddle_start(slsBehavior * self){ }
void paddle_preload(slsBehavior * self){ }

void paddle_draw(slsBehavior * self)
{
	slsPongPaddle *cont = (slsPongPaddle *) self->container;
	if ((cont->window != NULL) &&
		(cont->window != NULL)) {
		sfRenderWindow_drawSprite(cont->window, cont->sprite, NULL);
	}
}