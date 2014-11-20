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
typedef struct _slsStateBlocks slsStateBlocks;

enum slsStateCBType {
	SLS_STATE_CALLBACK_FNPTR = 0,
	SLS_STATE_CALLBACK_BLOCK
};

struct _slsStateCallbacks {
    void (*end)   			(slsStateNode *state);

    void (*start)			(slsStateNode *state);

    void (*resize)			(slsStateNode *state, int w, int h);
    void (*poll_events)		(slsStateNode *state, SDL_Event *event);

    void (*update) 			(slsStateNode *state, double dt);
    void (*draw) 			(slsStateNode *state, double dt);
};

struct _slsStateBlocks {
    void (^end)   			(void);
    void (^start)			(void);

    void (^resize)			(int w, int h);
    void (^poll_events)		(SDL_Event *event);

    void (^update) 			(double dt);
    void (^draw) 			(double dt);
};

struct _slsStateNode {
	slsStateNode *prev;
	slsStateNode *next;
	slsStateStack *host;

	void *state_data;

	enum slsStateCBType cb_type;

	/**
	 * @brief anonymous union containing callback info
	 * @details allows the use of either clang-style
	 * block closures or traditional fn pointers
	 * for scene callbacks
	 */
	union {
    	slsStateCallbacks callbacks;
    	slsStateBlocks cb_blocks;
    };


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

slsStateBlocks sls_stateblocks_copy(slsStateBlocks const *blocks);
void sls_stateblocks_release(slsStateBlocks *blocks);

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

const slsStateNode sls_statenode_class(void);
const slsStateStack sls_statestack_class(void);

#define slsNodeMsg(obj, cb_name, ...) do { \
	slsStateNode *_state = obj; /* obj should be slsStateNode */ \
	if (!_state) {break;} \
	if (_state->cb_type == SLS_STATE_CALLBACK_FNPTR) { \
		if (_state->callbacks.cb_name) { \
			_state->callbacks.cb_name(_state, ##__VA_ARGS__); \
		} \
	} else { \
		if (_state->cb_blocks.cb_name) { \
			_state->cb_blocks.cb_name(__VA_ARGS__); /* closures do not need first arg placement */\
		} \
	} \
} while(0)

#endif