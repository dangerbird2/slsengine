/**
 * this file describes a data structure containing
 * standard game callbacks
 * used to control game behavior
 * the behavior type is essentially a 
 * vtable for common callbacks
 */

#ifndef __SLS_BEHAVIOR_H__
#define __SLS_BEHAVIOR_H__ 

typedef struct _slsBehavior slsBehavior;

/**
 * Behavior clallbacks
 */
typedef void (*slsBehaviorCallback) 	(slsBehavior *self);
typedef void (*slsBehaviorUpdate) 		(slsBehavior * self, double dt);

typedef void *(*slsBehaviorDestructor)	(slsBehavior *self);

struct _slsBehavior {
	void *container;

	slsBehaviorDestructor destroy;

	slsBehaviorCallback start;
	slsBehaviorCallback preload;
	slsBehaviorUpdate update;
	slsBehaviorUpdate fixed_update;

	slsBehaviorCallback draw;
};

slsBehavior *slsBehavior_create(void *container);
void *slsBehavior_destroy(slsBehavior *self) __attribute__((nonnull(1)));

//default callbacks
void slsBehavior_start(slsBehavior *self);
void slsBehavior_preload(slsBehavior *self);
void slsBehavior_update(slsBehavior *self, double dt);
void slsBehavior_fixed_update(slsBehavior *self, double dt);

void slsBehavior_draw(slsBehavior *self);

#endif