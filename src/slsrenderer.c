#include "slsrenderer.h"
#include <common.h>

#include "shaderutils.h"

/**
 * sets up vertex buffer attributes to follow slsVertex layout.
 * Attribute binding values [0, 1, ...etc] are in order of slsVertex fields
 * @param self
 */
static inline void
setup_buffers_layout(slsRenderBuffers* self);

void
create_sprite_buffers(slsRenderer* self);

void
create_grid_geom(struct slsGridParams const* params,
                 uint32_t* indices,
                 slsVertex* verts);

static char const vs_source[] =
#ifdef SLS_GLES
  "precision mediump float;\n"
#endif
  "uniform mat4 modelview;\n"
  "uniform mat4 projection;\n"
  "layout (location=0) in vec3 vert_pos;\n"
  "layout (location=3) in vec2 vert_uv;\n"
  "out vec2 frag_uv;\n"
  "void main()\n"
  "{\n"
  "   frag_uv = vert_uv;\n"
  "   gl_Position = projection * modelview * vec4(vert_pos.xyz, 1.0);\n"
  "}";

static char const fs_source[] =
#ifdef SLS_GLES
  "precision mediump float;\n"
#endif
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

slsRenderer*
sls_create_renderer(slsRenderer* self,
                    SDL_Window* window,
                    SDL_GLContext ctx,
                    slsResultCode* result_out)
{
  sls_set_result(result_out, SLS_OK);

  int width, height;
  SDL_GetWindowSize(window, &width, &height);
  *self = (slsRenderer){.clear_color = { 1.0, 0.0, 1.0, 1.0 } };

  sls_renderer_onresize(self, width, height);
  float fov = 60.f * M_PI / 180.f;
  sls_mat4_identity(&self->main_camera.transform);

  GLuint vs, fs, program;
  vs = sls_create_shader(NULL, vs_source, GL_VERTEX_SHADER);
  fs = sls_create_shader(NULL, fs_source, GL_FRAGMENT_SHADER);
  program = sls_link_program(result_out, vs, fs);
  sls_check(!result_out || *result_out == SLS_OK, "sprite program link failed");

  sls_create_buffers(&self->sprite_buffers);
  sls_create_buffers(&self->tilemap_buffers);
  if (!mesh_initialized) {
    sls_create_sprite_geometry(&sprite_mesh);
    mesh_initialized = true;
  }

  self->sprite_program = program;

  // setup buffer data
  slsResultCode grid_res;
  struct slsGridParams grid_params = {.n_cols = 10,
                                      .n_rows = 10,
                                      .col_size = 1.0,
                                      .row_size = 1.0,
                                      .origin = { 0.f, 0.f } };
  self->grid =
    sls_create_grid(malloc(sizeof(slsGrid)), &grid_res, &grid_params);
  if (grid_res != SLS_OK) {
    free(self->grid);
    sls_log_err("could not create grid!");
  }

  create_sprite_buffers(self);

  return self;

error:
  return sls_delete_renderer(self);
}

void
create_sprite_buffers(slsRenderer* self)
{
  setup_buffers_layout(&self->sprite_buffers);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(slsVertex) * sprite_mesh.n_verts,
               (void*)sprite_mesh.verts,
               GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(uint32_t) * sprite_mesh.n_indices,
               (void*)sprite_mesh.indices,
               GL_STATIC_DRAW);
}

slsRenderer*
sls_delete_renderer(slsRenderer* self)
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

  if (self->grid) {
    free(sls_delete_grid(self->grid));
  }

  sls_delete_buffers(&self->sprite_buffers);
  sls_delete_buffers(&self->tilemap_buffers);
  return self;
}

void
sls_renderer_onresize(slsRenderer* self, int width, int height)
{
  self->width = width;
  self->height = height;
  glViewport(0, 0, width, height);
  mat4x4_ortho(self->main_camera.projection.m,
               0,
               (float)width / 8.f,
               0,
               (float)height / 8.f,
               0.0,
               100.0);
}

void
sls_renderer_clear(slsRenderer* self)
{
  glClearColor(self->clear_color.r,
               self->clear_color.g,
               self->clear_color.b,
               self->clear_color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void
sls_renderer_draw_sprite(slsRenderer* self, float rotation_theta)
{
  glBindVertexArray(self->sprite_buffers.vao);

  GLint modelview_id = glGetUniformLocation(self->sprite_program, "modelview");
  GLint projection_id =
    glGetUniformLocation(self->sprite_program, "projection");

  float mA[4][4], mB[4][4];
  mat4x4_identity(mA);
  mat4x4_rotate(mA, mA, 1, 0.6, 1, rotation_theta);
  mat4x4_translate(mB, 0, 0, -10);
  mat4x4_mul(self->main_camera.transform.m, mB, mA);

  glUniformMatrix4fv(
    modelview_id, 1, GL_FALSE, (float*)self->main_camera.transform.m);
  glUniformMatrix4fv(
    projection_id, 1, GL_FALSE, (float*)self->main_camera.projection.m);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void
sls_render_sprite_system(slsRenderer* self, slsEntityWorld* world)
{

  int32_t modelview_id =
    glGetUniformLocation(self->sprite_program, "modelview");
  int32_t projection_id =
    glGetUniformLocation(self->sprite_program, "projection");

  glUseProgram(self->sprite_program);
  glUniformMatrix4fv(
    projection_id, 1, GL_FALSE, (float*)self->main_camera.projection.m);
  glBindVertexArray(self->sprite_buffers.vao);

  size_t n_entities = 0;
  for (int i = 0; i < world->length; ++i) {
    if ((world->masks[i] & SLS_SYSTEM_RENDERSPRITE) !=
        SLS_SYSTEM_RENDERSPRITE) {
      continue;
    }
    n_entities++;
    glUniformMatrix4fv(
      modelview_id, 1, GL_FALSE, (float*)world->transforms[i].m);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}

static inline void
setup_buffers_layout(slsRenderBuffers* self)
{
  glBindVertexArray(self->vao);
  glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ibo);

  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        false,
                        sizeof(slsVertex),
                        (void*)offsetof(slsVertex, position));

  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        false,
                        sizeof(slsVertex),
                        (void*)offsetof(slsVertex, normal));

  glVertexAttribPointer(2,
                        3,
                        GL_FLOAT,
                        false,
                        sizeof(slsVertex),
                        (void*)offsetof(slsVertex, color));

  glVertexAttribPointer(
    3, 2, GL_FLOAT, false, sizeof(slsVertex), (void*)offsetof(slsVertex, uv));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
}

static char const grid_vs_source[] =
#ifdef SLS_GLES
  "precision mediump float;\n"
#endif
  "uniform mat4 modelview;\n"
  "uniform mat4 projection;\n"
  "layout (location=0) in vec3 vert_pos;\n"
  "layout (location=1) in vec4 vert_color;\n"
  "layout (location=4) in vec2 vert_uv;\n"
  "out vec2 frag_uv;\n"
  "out vec4 frag_color;\n"
  "void main()\n"
  "{\n"
  "   frag_uv = vert_uv;\n"
  "   frag_color = vert_color;\n"
  "   gl_Position = projection * modelview * vec4(vert_pos.xyz, 1.0);\n"
  "}";

static char const grid_fs_source[] =
#ifdef SLS_GLES
  "precision mediump float;\n"
#endif
  "in vec2 frag_uv;\n"
  "in vec4 frag_color;\n"
  "out vec4 out_color;\n"
  "void main()\n"
  "{\n"
  "     out_color = frag_color;\n"
  "}";

static const struct slsGridParams default_params = {.origin = { 0.f, 0.f, 0.f },
                                                    .row_size = 1.f,
                                                    .col_size = 1.f,
                                                    .n_rows = 10,
                                                    .n_cols = 10 };

slsGrid*
sls_create_grid(slsGrid* self,
                slsResultCode* result_out,
                struct slsGridParams const* params)
{
  slsResultCode tmp;

  if (!params) {
    params = &default_params;
  }
  if (!result_out) {
    result_out = &tmp;
  }
  GLuint vs = sls_create_shader(result_out, grid_vs_source, GL_VERTEX_SHADER);
  sls_check(*result_out == SLS_OK, "compilation failed");
  GLuint fs = sls_create_shader(result_out, grid_fs_source, GL_FRAGMENT_SHADER);
  sls_check(*result_out == SLS_OK, "compilation failed");

  GLuint program = sls_link_program(result_out, vs, fs);
  sls_check(*result_out == SLS_OK, "program linking failed");

  *self = (slsGrid){.params = *params, .shader_program = program };
  sls_create_buffers(&self->buffers);

  // create geometry
  size_t n_indices = 2 * (params->n_cols + params->n_rows);
  size_t n_vertices = n_indices;
  uint32_t* indices = calloc(n_indices, sizeof(*indices));
  slsVertex* verts = calloc(n_vertices, sizeof(*verts));

  create_grid_geom(params, indices, verts);

  glBindVertexArray(self->buffers.vao);
  glBufferData(
    GL_ARRAY_BUFFER, sizeof(slsVertex) * n_vertices, verts, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(uint32_t) * n_vertices,
               indices,
               GL_STATIC_DRAW);
  glBindVertexArray(0);

  free(indices);
  free(verts);
  sls_set_result(result_out, SLS_OK);
  return self;
error:
  return sls_delete_grid(self);
}

void
create_grid_geom(struct slsGridParams const* params,
                 uint32_t* indices,
                 slsVertex* verts)
{
  float col_size_half = (params->col_size * params->n_cols) / 2.f;
  float row_size_half = (params->row_size * params->n_rows) / 2.f;

  size_t index = 0;

  for (int i = 0; i < params->n_cols; ++i) {
    float x = (params->col_size * i) - col_size_half;
    indices[index] = (uint32_t)index;
    verts[index] = (slsVertex){.position = { x, row_size_half, 0.f },
                               .color = { 0.4, 0.4, 0.4 } };

    index++;
    indices[index] = (uint32_t)index;
    verts[index] = (slsVertex){.position = { x, row_size_half, 0.f },
                               .color = { 0.2, 0.2, 0.2 } };
    index++;
  }

  for (int j = 0; j < params->n_rows; ++j) {
    float y = (params->row_size * j) - row_size_half;
    indices[index] = (uint32_t)index;
    verts[index] = (slsVertex){.position = { -col_size_half, y, 0.f },
                               .color = { 0.2, 0.2, 0.2 } };

    index++;
    indices[index] = (uint32_t)index;
    verts[index] = (slsVertex){.position = { col_size_half, y, 0.f },
                               .color = { 0.4, 0.4, 0.4 } };
    index++;
  }
}

slsGrid*
sls_delete_grid(slsGrid* self)
{
  self->params = (struct slsGridParams){ 0 };
  if (glIsBuffer(self->buffers.vbo)) {
    sls_delete_buffers(&self->buffers);
  }
  if (glIsProgram(self->shader_program)) {
    glDeleteProgram(self->shader_program);
  }
  return self;
}
