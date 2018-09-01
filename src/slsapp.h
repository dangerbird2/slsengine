#ifndef SLS_APP_H
#define SLS_APP_H

#include "common.h"
#include "slsmacros.h"
#include <ecs/slsworld.h>

SLS_BEGIN_CDECLS

typedef struct slsRenderer slsRenderer;

struct nk_context {
  char c;
};

typedef struct slsApp slsApp;
struct slsApp {
  SDL_Window* window;
  SDL_GLContext ctx;

  struct nk_context* nuklear;

  slsRenderer* renderer;
  bool should_close;
  bool is_showing_gui;

  slsEntityWorld world;

  double last_time;
  // input to rotate object
  int object_rotate_input;
  float object_rotation_radians;
};

slsApp*
sls_create_app(slsApp* app);

slsApp*
sls_delete_app(slsApp* app);

void
sls_app_run(slsApp* app);

void
sls_app_iter(slsApp* self);

void
sls_app_gui(slsApp* self);

void
sls_app_update(slsApp* self, double dt);

static inline double
sls_get_time()
{
  uint32_t ticks = SDL_GetTicks();
  return ticks / 1000.0;
}

SLS_END_CDECLS

#endif // !SLS_APP_H
