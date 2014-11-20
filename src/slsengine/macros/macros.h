#ifndef __SLS_MACROS_H__
#define __SLS_MACROS_H__

#include <stdlib.h>
#include <string.h>
#include "dbg.h"

/**
 * @brief calls a function pointer, implicitly entering host struct
 * as first argument
 * @details uses gcc's type inference and statement expr extension to allow entering an
 * rvalue created or modified by a function without calling the function
 * twice, e.g. calling slsMsg(new_foo(), bar) doesn't expand to new_foo()->bar(new_foo()),
 * but rather ({typeof(foo) _obj = new_foo(); _obj->bar(_obj);})
 * 
 * @param obj: a pointer to a struct with 'method' function pointer
 * @param method: name of function pointer contained by object
 * @param ...: additional arguments to 'method'
 * 
 * @return return value of function pointed to
 */

#define slsMsg(obj, method, ...) ({ \
 	typeof(obj) _obj = obj; \
 	(_obj)->method((_obj), ##__VA_ARGS__); \
 })

/**
 * @brief macro for safe deletion of object
 * @details if obj is non-null and has a dtor method
 * (compilation will fail if it doesn't), slsDelete
 * will alias obj as _obj, call slsMsg(_obj, dtor), then free memory
 * 
 * TODO: rewrite dtor functions so that memory does not release memory.
 * this will allow the use of object values on the stack or as
 * a part of other structs/unions
 * 
 * @param  [description]
 * @return [description]
 */
#define slsDelete(obj) do{ 		\
	typeof(obj) _obj = (obj); 	\
	if (!_obj) { break; } 		\
	if (_obj->dtor) { 			\
		_obj->dtor(_obj); 	\
	} 							\
	free(obj); 					\
}while(0)

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
