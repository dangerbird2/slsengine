#ifndef SLS_RENDERER_H
#define SLS_RENDERER_H

#include "common.h"
#include "results.h"


SLS_BEGIN_CDECLS

GLuint sls_compile_shader(GLenum shader_type, char const *path, slsResultCode *res_out);
GLuint sls_link_program(GLuint vertex_shader, GLuint fragment_shader, slsResultCode *res_out);


SLS_END_CDECLS
#endif // !SLS_RENDERER_H
