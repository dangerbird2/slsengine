#ifndef SLS_RENDERER_H
#define SLS_RENDERER_H

#include "common.h"
#include "results.h"

#include "slsmath.h"
#include "slsapp.h"
#include "sls-geometry.h"

SLS_BEGIN_CDECLS
typedef struct slsCamera {
  slsMat4 projection;
  slsMat4 transform;
} slsCamera;

typedef struct slsRenderBuffers
{
  GLuint vbo;
  GLuint ibo;
  GLuint vao;
} slsRenderBuffers;

static inline slsRenderBuffers *sls_create_buffers(slsRenderBuffers *self)
{
  GLuint buffers[2];
  glGenBuffers(2, buffers);
  self->vbo = buffers[0];
  self->ibo = buffers[1];

  glGenVertexArrays(1, &self->vao);
  return self;
}

static inline slsRenderBuffers *sls_delete_buffers(slsRenderBuffers *self)
{
  GLuint buffers[] = {self->vbo, self->ibo};
  glDeleteBuffers(2, buffers);
  glDeleteVertexArrays(1, &self->vao);

  return self;
}



typedef struct slsGrid slsGrid;


typedef struct slsRenderer {
  int width, height;

  slsCamera main_camera;

  slsVec4 clear_color;

  slsGrid *grid;

  GLuint sprite_program;
  slsRenderBuffers sprite_buffers;
  slsRenderBuffers tilemap_buffers;

} slsRenderer;





slsRenderer *sls_create_renderer(slsRenderer *self, SDL_Window *window, SDL_GLContext ctx, slsResultCode *result_out);
slsRenderer *sls_delete_renderer(slsRenderer *self);

void sls_renderer_clear(slsRenderer *self);

void sls_renderer_onresize(slsRenderer *self, int width, int height);

void sls_renderer_draw_sprite(slsRenderer *self, float rotation_theta);

void sls_render_sprite_system(slsRenderer *self, slsEntityWorld *world);

struct slsGridParams {
  float row_size;
  float col_size;

  slsVec3 origin;

  size_t n_cols;
  size_t n_rows;

};

/**
 * @brief Renderer for debug grid
 */
struct slsGrid {
  struct slsGridParams params;
  slsRenderBuffers buffers;
  GLuint shader_program;
  slsMat4 transform;
};

slsGrid *sls_create_grid(slsGrid *self, slsResultCode *result_out,
                         struct slsGridParams const *params);

slsGrid *sls_delete_grid(slsGrid *self);

SLS_END_CDECLS
#endif // !SLS_RENDERER_H
