#ifndef __SLS_ENGINE_HEADERS_H__
#define __SLS_ENGINE_HEADERS_H__

/****************************************
 * include glib
 ***************************************/

#include <glib-2.0/glib.h>

#include <CoreFoundation/CoreFoundation.h>

/****************************************
 * macro for possible emscripten port
 ****************************************/
#ifdef EMSCRIPTEN
	#include <emscripten.h>
	#include <GLES/gl2.h>
#else
 	/**
 	 * by default, use glew
 	 */
	#include <GL/glew.h>
#endif


/****************************************
 * sdl includes
 ****************************************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

/****************************************
 * standard library includes
 ****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

/****************************************
 * my pre-defined primitive types
 ****************************************/
#include <apr_general.h>
#include <apr_tables.h>
#include <apr_hash.h>

#include "types.h"
#include "macros/dbg.h"
#include "linalg/vectypes.h"
#include "macros/macros.h"

#endif
