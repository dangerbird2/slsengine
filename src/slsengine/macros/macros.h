#ifndef __SLS_MACROS_H__
#define __SLS_MACROS_H__

#include <stdlib.h>
#include <string.h>
#include "dbg.h"

#define slsMsg(obj, method, ...) ((obj->method)((obj), ##__VA_ARGS__))

static inline void *sls_objalloc(void const *klass, size_t size)
{
	void *obj = NULL;

	check(klass, "'klass' must be non-null");
	obj = calloc(1, size);
	check_mem(obj);
	memcpy(obj, klass, size);


	return obj;

error:
	if (obj) {
		free(obj);
	}
	return NULL;
}

static inline void *sls_xobjalloc(void const *klass, size_t size)
{
	void *obj = sls_objalloc(klass, size);

	if (!obj) {
		abort();
	}

	return obj;
}

/**
 * @brief autofree attribute
 * @details [long description]
 * 
 * @param  fn: a function that takes a pointer to the attributed
 * object
 */
#define slsAF(fn) __attribute__((cleanup(fn)))

#define slsDeprecated __attribute__((deprecated))


#endif //__SLS_MACROS_H__
