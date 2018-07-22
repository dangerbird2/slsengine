#include "slsrenderer.h"

#include "shaderutils.h"

static char const vs_source[] = "layout (location=0) in vec3 vert_pos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(vert_pos.xyz, 1.0);\n"
"}";

static char const fs_source[] = "out vec4 frag_color;\n"
"void main()\n"
"{\n"
"   frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}";

static slsVec3 basic_triangle[] = {
  { -0.5f, -0.5f, 0.0f },
  { 0.5f, -0.5f, 0.0f },
  { -0.0f, 0.5f, 0.0f}
};

slsRenderer *sls_create_renderer(slsRenderer *self, SDL_Window *window, SDL_GLContext ctx,
  slsResultCode *result_out)
{
  sls_set_result(result_out, SLS_OK);

  int width, height;
  SDL_GetWindowSize(window, &width, &height);
  *self = (slsRenderer) { 0 };

  sls_renderer_onresize(self, width, height);
  float fov = 60.f * M_PI / 180.f;
  sls_mat4_identity(&self->main_camera.transform);

  GLuint vs, fs, program;
  vs = sls_create_shader(vs_source, GL_VERTEX_SHADER);
  fs = sls_create_shader(fs_source, GL_FRAGMENT_SHADER);
  program = sls_link_program(result_out, vs, fs);
  sls_check(!result_out || *result_out == SLS_OK, "sprite program link failed");

  // setup vertex buffers
  GLuint buffers[2];
  glGenBuffers(2, buffers);
  self->tri_vbo = buffers[0];
  self->tri_ibo = buffers[1];

  glGenVertexArrays(1, &self->tri_vao);

  self->sprite_program = program;

  return self;

error:
  return sls_delete_renderer(self);
}

slsRenderer *sls_delete_renderer(slsRenderer *self)
{
  while(glGetError() != GL_NO_ERROR){}
  if (glIsProgram(self->sprite_program)) {
    glDeleteProgram(self->sprite_program);
  }

  if (glIsVertexArray(self->tri_vao)) {
    glDeleteVertexArrays(1, &self->tri_vao);
  }
  if (glIsBuffer(self->tri_vbo)) {
    GLuint buffers[] = { self->tri_vbo, self->tri_ibo };
    glDeleteBuffers(2, buffers);
  }
  //assert(glGetError() == GL_NO_ERROR);
  return self;
}

void sls_renderer_onresize(slsRenderer *self, int width, int height)
{
  self->width = width;
  self->height = height;
  glViewport(0, 0, width, height);
  float aspect = width / (float)height;
  float fov = 60.0 * M_PI / 180.0;
  mat4x4_perspective(self->main_camera.projection.m, fov, aspect, 0.0f, -100.f);

}
