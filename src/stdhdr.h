#ifndef __SLS_ENGINE_HEADERS_H__
#define __SLS_ENGINE_HEADERS_H__

/****************************************
 * include glib
 ***************************************/

#include <glib-2.0/glib.h>

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

/****************************************
 * my pre-defined primitive types
 ****************************************/
#include "types.h"
#include "macros/dbg.h"
#include "macros/constants.h"

#endif
