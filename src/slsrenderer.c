#include "slsrenderer.h"

slsRenderer *sls_create_renderer(slsRenderer *self, SDL_Window *window, SDL_GLContext ctx,
                                 slsResultCode *result_out)
{
  sls_set_result(result_out, SLS_OK);

  int width, height;
  SDL_GetWindowSize(window, &width, &height);
  *self = (slsRenderer) {0};
  sls_renderer_onresize(self, width, height);

  sls_mat4_identity(&self->main_camera.projection);
  sls_mat4_identity(&self->main_camera.transform);

  return self;
}

slsRenderer *sls_delete_renderer(slsRenderer *self)
{
  return self;
}

void sls_renderer_onresize(slsRenderer *self, int width, int height)
{
  self->width = width;
  self->height = height;
  glViewport(0, 0, width, height);
}
