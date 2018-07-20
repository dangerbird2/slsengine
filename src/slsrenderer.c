#include "slsrenderer.h"
#ifndef __EMSCRIPTEN__

char *sls_from_base_path(char const *relative_path)
{
    char *bin_path = SDL_GetBasePath();
    char *path = NULL;
    int len = sprintf(NULL, "%s/%s", bin_path, relative_path);
    path = malloc(len + 1);
    len = sprintf(path, "%s/%s", bin_path, relative_path);

    SDL_free(bin_path);
    return path;
}

#endif

static char *read_from_file(char const *path)
{
    FILE *fp = fopen(path, "r");
    char *buffer = NULL;

    return buffer;
}

GLuint sls_compile_shader(GLenum shader_type, char const *path, slsResultCode *res_out)
{
    GLuint shader = 0;
    shader = glCreateShader(shader_type);
    char *source = read_from_file(path);
    sls_checkmem(source);

    return shader;

    error:
    sls_set_res(res_out, SLS_COMPILE_FAILED);
    return 0;


}
GLuint sls_link_program(GLuint vertex_shader, GLuint fragment_shader, slsResultCode *res_out)
{
    GLuint program;
    program = glCreateProgram();
    return program;
}