/**
 * @file
 * @brief
 * @detail
 * From the OpenGL Programming wikibook:
 * http://en.wikibooks.org/wiki/OpenGL_Programming
 * This file is in the public domain.\n
 * Contributors: Sylvain Beucler
 * modified by: Steven Shea
 */

#ifndef _SLS_SHADERUTILS_H_
#define _SLS_SHADERUTILS_H_

#include "common.h"
#include "slsmacros.h"
#include "results.h"

char*
sls_file_read(const char* filename);

typedef enum slsGLObjectType {
  SLS_TYPE_SHADER,
  SLS_TYPE_PROGRAM,
  SLS_N_TYPES
} slsGLObjectType;
void
_sls_print_log(GLuint object,
               slsGLObjectType type,
               char const* file,
               char const* func,
               long line);

/**
 * @brief macro to automatically insert debugging info to _sls_print_log
 */
#define sls_print_log(object_GLuint, type)                                     \
  do {                                                                         \
    _sls_print_log((object_GLuint), (type), __FILE__, __FUNCTION__, __LINE__); \
  } while (0)

GLuint
sls_create_shader(const char* source, GLenum type) SLS_NONNULL(1);

GLuint
_sls_link_program(slsResultCode* out_result,
                  GLuint vertex,
                  GLuint frag,
                  GLuint geom,
                  bool has_geometry_shader,
                  GLint gs_input,
                  GLint g_output,
                  GLint gs_vertices);

/**
 * Links a Program with an attached geometry shader
 **/
static inline GLuint
sls_link_program_gs(slsResultCode* out_result,
                    GLuint vertex,
                    GLuint frag,
                    GLuint geom)
{
  return _sls_link_program(out_result, vertex, frag, geom, true, 0, 0, 0);
}
/**
 * Links a Fragment and vertex shader
 **/
static inline GLuint
sls_link_program(slsResultCode* out_result, GLuint vertex, GLuint frag)
{
  return _sls_link_program(out_result, vertex, frag, 0, false, 0, 0, 0);
}

#endif
