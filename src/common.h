
#ifndef SLS_COMMON_H
#define SLS_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "slsmacros.h"
#include "results.h"
#include <math.h>
#include <float.h>
#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>

#define SLS_GLES
#else

#include <glad/glad.h>

#include <SDL.h>
#endif

#endif // !SLS_COMMON_H
