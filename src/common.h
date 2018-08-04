
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

#include <glad/glad.h>
#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <SDL2/SDL.h>

#else

#include <SDL.h>
#endif

#endif // !SLS_COMMON_H
