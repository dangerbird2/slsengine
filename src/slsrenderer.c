#include "slsrenderer.h"

#include "shaderutils.h"
#include "linmath.h"

static char const vs_source[] = "uniform mat4 modelview;\n"
  "uniform mat4 projection;\n"
  "layout (location=0) in vec3 vert_pos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = projection * modelview * vec4(vert_pos.xyz, 1.0);\n"
  "}";

static char const fs_source[] = "out vec4 frag_color;\n"
  "void main()\n"
  "{\n"
  "   frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
  "}";

static slsVec3 sprite_geom[] = {
  {-1.f, -1.f, 0.0f},
  {1.f, -1.f, 0.0f},
  {1.f, 1.f, 0.0f},
  {-1.f, 1.f, 0.0f},
};

static GLuint triangle_indices[] = {0, 1, 2, 2, 3, 0};

slsRenderer* sls_create_renderer(slsRenderer* self, SDL_Window* window, SDL_GLContext ctx,
                                 slsResultCode* result_out)
{
  sls_set_result(result_out, SLS_OK);

  int width, height;
  SDL_GetWindowSize(window, &width, &height);
  *self = (slsRenderer) {.clear_color={1.0, 0.0, 1.0, 1.0}};

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

  // setup buffer data
  glBindVertexArray(self->tri_vao);
  glBindBuffer(GL_ARRAY_BUFFER, self->tri_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->tri_ibo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(sprite_geom), (void *)sprite_geom,
               GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_indices),
               (void *)triangle_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3,GL_FLOAT, false, sizeof(float) * 3, (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);


  return self;

error:
  return sls_delete_renderer(self);
}

slsRenderer* sls_delete_renderer(slsRenderer* self)
{
  while (glGetError() != GL_NO_ERROR)
  {
  }
  if (glIsProgram(self->sprite_program))
  {
    glDeleteProgram(self->sprite_program);
  }

  if (glIsVertexArray(self->tri_vao))
  {
    glDeleteVertexArrays(1, &self->tri_vao);
  }
  if (glIsBuffer(self->tri_vbo))
  {
    GLuint buffers[] = {self->tri_vbo, self->tri_ibo};
    glDeleteBuffers(2, buffers);
  }
  //assert(glGetError() == GL_NO_ERROR);
  return self;
}

void sls_renderer_onresize(slsRenderer* self, int width, int height)
{
  self->width = width;
  self->height = height;
  glViewport(0, 0, width, height);
  float aspect = width / (float)height;
  float fov = 60.0 * M_PI / 180.0;
  mat4x4_perspective(self->main_camera.projection.m, fov, aspect, 0.0f, -100.f);
}

void sls_renderer_clear(slsRenderer* self)
{
  glClearColor(self->clear_color.r, self->clear_color.g, self->clear_color.b,
               self->clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void sls_renderer_draw_sprite(slsRenderer* self)
{
  glBindVertexArray(self->tri_vao);

  uint32_t modelview_id = glGetUniformLocation(self->sprite_program, "modelview");
  uint32_t projection_id = glGetUniformLocation(self->sprite_program, "projection");

  float mA[4][4], mB[4][4];
  mat4x4_identity(mA);
  mat4x4_rotate(mA, mA, 0, 1, 1, 1.80 * M_PI);
  mat4x4_translate(mB, 0, 0, -10);
  mat4x4_mul(self->main_camera.transform.m, mB, mA);

  glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (float*) self->main_camera.transform.m);
  glUniformMatrix4fv(projection_id, 1, GL_FALSE, (float*)self->main_camera.projection.m);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
