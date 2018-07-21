#ifndef SLS_RENDERER_H
#define SLS_RENDERER_H

#include "common.h"
#include "results.h"

#include "slsmath.h"

SLS_BEGIN_CDECLS
typedef struct slsCamera {
  slsMat4 projection;
  slsMat4 transform;
} slsCamera;

typedef struct slsRenderer {
  int width, height;

  GLuint phong_program;
  slsCamera main_camera;

} slsRenderer;

slsRenderer *sls_create_renderer(slsRenderer *self, SDL_Window *window, SDL_GLContext ctx, slsResultCode *result_out);
slsRenderer *sls_delete_renderer(slsRenderer *self);

void sls_renderer_onresize(slsRenderer *self, int width, int height);

SLS_END_CDECLS
#endif // !SLS_RENDERER_H
