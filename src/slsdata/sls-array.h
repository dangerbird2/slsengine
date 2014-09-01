#ifndef __SLS_DYNAMIC_ARRAY_H__
#define __SLS_DYNAMIC_ARRAY_H__

#include "../macros/types.h"

typedef struct slsArray slsArray;
typedef void (*slsFreeFunc)(void *data);

struct slsArray {
	char *data;
	size_t memory;
	size_t len;
	size_t element_size;

	size_t allocation_buffer;
	slsFreeFunc free_func;
};

slsArray *slsArray_new(size_t element_size, slsFreeFunc free_func);
void slsArray_free(slsArray *self);

void slsArray_insert(slsArray *self, size_t n_elements, char *data);

char *slsArray_getIndexPtr(slsArray *self, size_t i);
/**
 * @brief macro for obtaining index to element in array
 * @details the macro casts slsArray_getIndexPtr to pointer
 * of specified type,
 * and dereferences itsel
 * 
 * @param self slsArray object
 * @param T element type
 * @param i element index
 */
#define slsArray_index(self, T, i) *((T *) slsArray_getIndexPtr(self, i))


#endif