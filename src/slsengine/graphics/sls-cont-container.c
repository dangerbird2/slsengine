#include "../stdhdr.h"
#include "sls-cont-container.h"

void slsContentContainer_setData(slsContentContainer *self,
	slsContentType type, void *data)
{
	if (type == SLS_CONTENT_TEXTURE) {
		self->t = (SDL_Texture *) data;
	}
	else if (type == SLS_CONTENT_MESH) {
		self->m = (slsMesh *)data;
	}
	else if (type == SLS_CONTENT_SPRITE) {
		self->sp = (slsSprite *)data;
	}
	else if (type == SLS_CONTENT_SHADER) {
		self->sh = (slsShader *)data;
	}
	else {
		self->v = data;
	}
}

slsContentContainer *slsContentContainer_new(
	slsContentType type, void *data,
	void (*custom_data_dtor)(void *data))
{
	slsContentContainer *self = calloc(1, sizeof(slsContentContainer));
	g_return_val_if_fail(self, NULL);

	self->ref = 1;
	self->callbacks = slsContentContainer_callbackProto;
	self->type = type;

	self->setData = slsContentContainer_setData;
	self->dtor = slsContentContainer_dtor;

	if (custom_data_dtor){
		self->custom_data_dtor = custom_data_dtor;
	}
	else {
		self->custom_data_dtor = NULL;
	}
	

	slsMsg(self, setData, type, data);

	return self;
}

void slsContentContainer_dtor(slsContentContainer *self)
{
	if (!self) {return;}
	// do not free data if data is NULL
	if (!self->v) {

	}
	else if (self->type == SLS_CONTENT_TEXTURE) {
		SDL_DestroyTexture(self->t);
	}
	else if (self->type == SLS_CONTENT_SHADER) {
		slsMsg(self->sh, dtor);
	}
	else if (self->type == SLS_CONTENT_SPRITE) {
		slsSprite_destroy(self->sp);
	}
	else if (self->custom_data_dtor != NULL) {
		self->custom_data_dtor(self->v);
	}

	free(self);

}

const void *slsContentContainer_retain(CFAllocatorRef allocator, const void *value)
{
	slsContentContainer *self = (slsContentContainer *) value;
	self->ref ++;
	return value;
}