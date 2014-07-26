#ifndef __SLS_GAME_PADDLE_H__
#define __SLS_GAME_PADDLE_H__

#include "behavior.h"
#include <SFML/Graphics.h>

// a pong paddle
typedef struct _slsPongPaddle slsPongPaddle;

struct _slsPongPaddle {
	//int player;
	slsBehavior *behavior;
	sfVector2f position;

	sfSprite *sprite;
	sfRenderWindow *window;
};

slsPongPaddle *slsPongPaddle_create(
	sfSprite *sprite,
	sfRenderWindow *window
);
void slsPongPaddle_destroy(slsPongPaddle *self)
	__attribute__((nonnull(1)));

#endif