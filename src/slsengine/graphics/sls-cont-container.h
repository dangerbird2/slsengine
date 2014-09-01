#ifndef __SLS_CONTENT_CONTAINER__
#define __SLS_CONTENT_CONTAINER__

#include <SDL2/SDL.h>
#include <CoreFoundation/CoreFoundation.h>

#include "sls-sprite.h"
#include "../gl/sls-mesh.h"
#include "../gl/sls-shader.h"

typedef struct slsContentContainer slsContentContainer;

typedef enum {
	SLS_CONTENT_VOID = 0,
	SLS_CONTENT_TEXTURE,
	SLS_CONTENT_MESH,
	SLS_CONTENT_SPRITE,
	SLS_CONTENT_SHADER,
	SLS_CONTENT_AUDIO
} slsContentType;

struct slsContentContainer{
	slsContentType type;
	
	CFDictionaryValueCallBacks callbacks;

	unsigned ref;

	union {
		void *v;
		SDL_Texture *t;
		slsSprite *sp;
		slsShader *sh;
		slsMesh *m;
	};

	void (*setData)(slsContentContainer *self,
		slsContentType type, void *data);

	void (*custom_data_dtor)(void *data);
	void (*dtor)(slsContentContainer *self);
};

slsContentContainer *slsContentContainer_new(
	slsContentType type, void *data, void (*custom_data_dtor)(void *data));

void slsContentContainer_dtor(slsContentContainer *self);

void slsContentContainer_setData(slsContentContainer *self,
	slsContentType type, void *data);


/* dictionary value callback functions */
const void *slsContentContainer_retain(CFAllocatorRef allocator, const void *value);
void slsContentContainer_release(CFAllocatorRef allocator, const void *value);
CFStringRef slsContentContainer_copyString(const void *value);
Boolean slsContentContainer_cmp(const void *value1, const void *value2);


static const CFDictionaryValueCallBacks
slsContentContainer_callbackProto = {
	.version = 1,
	.retain = slsContentContainer_retain,
	.release = slsContentContainer_release,
	.copyDescription = slsContentContainer_copyString,
	.equal = slsContentContainer_cmp
};

#endif