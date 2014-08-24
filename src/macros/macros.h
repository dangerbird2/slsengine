#ifndef __SLS_MACROS_H__
#define __SLS_MACROS_H__


#define slsMsg(obj, method, ...) (obj->method(obj, ##__VA_ARGS__))

#endif //__SLS_MACROS_H__
