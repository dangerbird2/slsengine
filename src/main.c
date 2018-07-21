#include "common.h"
#include "results.h"
#include "shaderutils.h"
#include "slsapp.h"
#include "slsmacros.h"

static char const vs_source[] = "layout (location=0) in vec3 vert_pos;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = vec4(vert_pos.xyz, 1.0);\n"
                                "}";

static char const fs_source[] = "void main()\n"
                                "{\n"
                                "}";

static GLuint g_vs, g_fs, g_program;

static void
sls_exit_cleanup()
{
  SDL_Quit();
}
int
main(int argc, char** argv)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER )) {
    sls_log_err("Init failed: %s", SDL_GetError());
    exit(-1);
  }

  slsApp app;
  sls_create_app(&app);

  slsResultCode res;
  g_vs = sls_create_shader(vs_source, GL_VERTEX_SHADER);
  g_fs = sls_create_shader(fs_source, GL_FRAGMENT_SHADER);
  g_program = sls_link_program(&res, g_vs, g_fs);

  if (res != SLS_OK) {
    sls_log_err("link program error: %s",
                res == SLS_LINK_FAILED ? "program link error" : "unknown");
                sls_exit_cleanup();
    exit(-1);
  }

  sls_app_run(&app);
  sls_delete_app(&app);
  sls_exit_cleanup();
  return 0;
}
