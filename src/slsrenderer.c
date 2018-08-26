#include "slsrenderer.h"

#include "shaderutils.h"
#include "sls-geometry.h"

static inline void
setup_sprite_buffers(slsRenderBuffers* self);
static char const vs_source[] =
  "uniform mat4 modelview;\n"
  "uniform mat4 projection;\n"
  "layout (location=0) in vec3 vert_pos;\n"
  "layout (location=1) in vec2 vert_uv;\n"
  "out vec2 frag_uv;\n"
  "void main()\n"
  "{\n"
  "   frag_uv = vert_uv;\n"
  "   gl_Position = projection * modelview * vec4(vert_pos.xyz, 1.0);\n"
  "}";

static char const fs_source[] =
  "out vec4 frag_color;\n"
  "in vec2 frag_uv;\n"
  "void main()\n"
  "{\n"
  "   if (gl_FrontFacing){\n"
  "     frag_color = vec4(1.0f, frag_uv.s, frag_uv.t, 1.0f);\n"
  "   } else { \n"
  "     frag_color = vec4(0.5, 1.0, 0.0, 1.0);\n"
  "   }\n"
  "}";

static slsMesh sprite_mesh;
static bool mesh_initialized = false;

slsRenderer *sls_create_renderer(slsRenderer *self, SDL_Window *window, SDL_GLContext ctx,
                                 slsResultCode *result_out)
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



  create_buffers(&self->sprite_buffers);
  create_buffers(&self->tilemap_buffers);
  if (!mesh_initialized) {
    sls_create_sprite_geometry(&sprite_mesh);
    mesh_initialized = true;
  }

  self->sprite_program = program;

  // setup buffer data

  setup_sprite_buffers(&self->sprite_buffers);



  return self;

error:
  return sls_delete_renderer(self);
}

slsRenderer *sls_delete_renderer(slsRenderer *self)
{
  while (glGetError() != GL_NO_ERROR) {
  }
  if (mesh_initialized) {
    mesh_initialized = false;
    sls_delete_gpumesh(&sprite_mesh);
  }
  if (glIsProgram(self->sprite_program)) {
    glDeleteProgram(self->sprite_program);
  }

  delete_buffers(&self->sprite_buffers);
  delete_buffers(&self->tilemap_buffers);
  //assert(glGetError() == GL_NO_ERROR);
  return self;
}

void sls_renderer_onresize(slsRenderer *self, int width, int height)
{
  self->width = width;
  self->height = height;
  glViewport(0, 0, width, height);
  mat4x4_ortho(self->main_camera.projection.m, 0, (float)width/8.f, 0, (float)height/8.f, 0.0, 100.0);
}

void sls_renderer_clear(slsRenderer *self)
{
  glClearColor(self->clear_color.r, self->clear_color.g, self->clear_color.b,
               self->clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void sls_renderer_draw_sprite(slsRenderer *self, float rotation_theta)
{
  glBindVertexArray(self->sprite_buffers.vao);

  uint32_t modelview_id = glGetUniformLocation(self->sprite_program, "modelview");
  uint32_t projection_id = glGetUniformLocation(self->sprite_program, "projection");

  float mA[4][4], mB[4][4];
  mat4x4_identity(mA);
  mat4x4_rotate(mA, mA, 1, 0.6, 1, rotation_theta);
  mat4x4_translate(mB, 0, 0, -10);
  mat4x4_mul(self->main_camera.transform.m, mB, mA);

  glUniformMatrix4fv(modelview_id, 1, GL_FALSE, (float *) self->main_camera.transform.m);
  glUniformMatrix4fv(projection_id, 1, GL_FALSE,
                     (float *) self->main_camera.projection.m);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void sls_render_sprite_system(slsRenderer *self, slsEntityWorld *world)
{

  int32_t modelview_id = glGetUniformLocation(self->sprite_program, "modelview");
  int32_t projection_id = glGetUniformLocation(self->sprite_program, "projection");

  glUseProgram(self->sprite_program);
  glUniformMatrix4fv(projection_id, 1, GL_FALSE, (float *) self->main_camera.projection.m);
  glBindVertexArray(self->sprite_buffers.vao);


  size_t n_entities = 0;
  for (int i = 0; i < world->length; ++i) {
    if ((world->masks[i] & SLS_SYSTEM_RENDERSPRITE) != SLS_SYSTEM_RENDERSPRITE) { continue; }
    n_entities++;
    glUniformMatrix4fv(modelview_id, 1, GL_FALSE,
                       (float *) world->transforms[i].m);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  }
}


  static inline void setup_sprite_buffers(slsRenderBuffers *self){
  glBindVertexArray(self->vao);
  glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ibo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(slsVertex) * sprite_mesh.n_verts,
               (void *) sprite_mesh.verts,
               GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * sprite_mesh.n_indices,
               (void *) sprite_mesh.indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        false,
                        sizeof(slsVertex),
                        (void *) offsetof(slsVertex, position));

  glVertexAttribPointer(1,
                        2,
                        GL_FLOAT,
                        false,
                        sizeof(slsVertex),
                        (void *) offsetof(slsVertex, uv));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}
