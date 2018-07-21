#ifndef SLS_RENDERER_H
#define SLS_RENDERER_H

#include "common.h"
#include "results.h"


SLS_BEGIN_CDECLS

typedef struct slsRenderer {
  int width, height;

} slsRenderer;

slsRenderer *sls_create_renderer(slsRenderer *self, SDL_Window *window, SDL_GLContext ctx, slsResultCode *result_out);
slsRenderer *sls_delete_renderer(slsRenderer *self);

void sls_renderer_onresize(slsRenderer *self, int width, int height);

SLS_END_CDECLS
#endif // !SLS_RENDERER_H
