/**
 * @file ${FILE}
 * @brief
 * @license ${LICENSE}
 * Copyright (c) 7/30/18, Steven
 *
 **/
#ifndef SLS_ENGINE_SLS_NUKLEAR_H
#define SLS_ENGINE_SLS_NUKLEAR_H

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#ifndef __EMSCRIPTEN__
#include <nk_private/nuklear_sdl_gl3.h>

#else
#include <nk_private/nuklear_sdl_gles2.h>

#endif

#endif // SLS_ENGINE_SLS_NUKLEAR_H
