#ifndef __SLS_TYPES_H__
#define __SLS_TYPES_H__

#include <stdint.h>
#include <stdbool.h>


// macro for string dup functions to prevent buffer overflows
// & such
#define SAFE_STRING_LEN 200

typedef int8_t SLbyte;
typedef int16_t SLshort;
typedef int32_t SLint;
typedef int64_t SLint64;

typedef uint8_t SLubyte;
typedef uint16_t SLushort;
typedef uint32_t SLuint;
typedef uint64_t SLuint64;

typedef bool SLbool;
typedef int32_t SLenum;

#endif
