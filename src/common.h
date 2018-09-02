
#ifndef SLS_COMMON_H
#define SLS_COMMON_H
#include "slsmacros.h"
#include "results.h"

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __EMSCRIPTEN__

#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <emscripten.h>

#define SLS_GLES
#else

#include <glad/glad.h>

#include <SDL.h>
#endif

#endif // !SLS_COMMON_H
