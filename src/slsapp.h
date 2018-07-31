#ifndef SLS_APP_H
#define SLS_APP_H

#include "common.h"
#include "slsmacros.h"
SLS_BEGIN_CDECLS


typedef struct slsRenderer slsRenderer;

typedef struct slsApp slsApp;
struct slsApp {
  SDL_Window* window;
  SDL_GLContext ctx;

  struct nk_context *nuklear;

  slsRenderer *renderer;
  bool should_close;
};

slsApp*
sls_create_app(slsApp* app);
slsApp*
sls_delete_app(slsApp* app);

void
sls_app_run(slsApp* app);

SLS_END_CDECLS

#endif // !SLS_APP_H
