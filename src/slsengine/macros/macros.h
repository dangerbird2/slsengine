#ifndef __SLS_MACROS_H__
#define __SLS_MACROS_H__

#include <stdlib.h>
#include "dbg.h"

#define slsMsg(obj, method, ...) (obj->method(obj, ##__VA_ARGS__))

/**
 * @brief autofree attribute
 * @details [long description]
 * 
 * @param  fn: a function that takes a pointer to the attributed
 * object
 * @return [description]
 */
#define slsAF(fn) __attribute__((cleanup(fn)))


/**
* macro for standard char buffer size
*/

#define SLS_BUFFER_SIZE


#endif //__SLS_MACROS_H__
