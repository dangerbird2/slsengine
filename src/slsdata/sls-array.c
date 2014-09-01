#include "sls-array.h"
#include "slsdata-hdr.h"

/**
 * defines the number of elements (with byte size of n_elem * elem_size)
 * increased when memory is automaticaly added
 */
#define SLS_ARRAY_ALLOCATION_BUFFER 10

slsArray *slsArray_new(size_t element_size, slsFreeFunc free_func)
{
	slsArray *self = NULL;
	self = calloc(1, sizeof(slsArray));
	check_mem(self);

	self->element_size = element_size;
	self->free_func = free_func;
	self->len = 0;
	self->allocation_buffer = SLS_ARRAY_ALLOCATION_BUFFER;

	self->memory = self->element_size * self->allocation_buffer;

	// allocate data
	self->data = malloc(self->memory);

	return self;

error:
	slsArray_free(self);
	return NULL;
}

void slsArray_free(slsArray *self)
{
	if (!self) {return;}
	if (self->data && self->free_func) {
		for (int i=0; i<self->len; i++) {
			slsArray_index(self, void *, i);
		}
	}
	if (self->data) {
		free(self->data);
	}
	free(self);
}

char *slsArray_getIndexPtr(slsArray *self, size_t i)
{
	check(i < self->len, "slsArray: Index Error!!");

	return self->data + (self->element_size * i);

error:
	return NULL;
}


void slsArray_insert(slsArray *self, size_t n_elements, char *data)
{
	size_t new_size = self->element_size * (n_elements + self->len);
	if (new_size > self->memory) {
		char *alloc = realloc(self->data, self->element_size * (new_size + self->allocation_buffer));
		assert(alloc);
	}

	
}