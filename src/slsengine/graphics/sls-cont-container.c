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
		self->data = data;
	}
}

slsContentContainer *slsContentContainer_new(
	slsContentType type, void *data,
	void (*custom_data_dtor)(void *data))
{
	slsContentContainer *self = calloc(1, sizeof(slsContentContainer));
	g_return_val_if_fail(self, NULL);

	self->ref = 1;
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
	// do not free state_data if state_data is NULL
	if (!self->data) {

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
		self->custom_data_dtor(self->data);
	}

	free(self);

}

const void *slsContentContainer_retain(CFAllocatorRef allocator, const void *value)
{
	slsContentContainer *self = (slsContentContainer *) value;
	self->ref ++;
	return value;
}

void slsContentContainer_release(CFAllocatorRef allocator, const void *value)
{
	slsContentContainer *self = (slsContentContainer *) value;
	self->ref --;
	if (self->ref < 1) {
		slsMsg(self, dtor);
	}
}


Boolean slsContentContainer_cmp(const void *value1, const void *value2)
{
	slsContentContainer *c1 = (slsContentContainer *) value1;
	slsContentContainer *c2 = (slsContentContainer *) value2;
	if ((!c1) || (!c2)) {return false;}
	
	if (c1->type != c2->type) { return false;}

	// check if pointers point to the same state_data
	if (c1->data != c2->data) {
		return false;
	}
	return true;
}