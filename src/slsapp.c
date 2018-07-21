
#include "slsapp.h"

static void
handle_sdlevents(slsApp* self);

slsApp*
sls_create_app(slsApp* self)
{
  *self = (slsApp){ 0 };
  self->window = SDL_CreateWindow("window",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  640,
                                  480,
                                  SDL_WINDOW_OPENGL |
                                    SDL_WINDOW_RESIZABLE |
                                    SDL_WINDOW_SHOWN);
#ifndef __EMSCRIPTEN__
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#endif
  self->ctx = SDL_GL_CreateContext(self->window);
  SDL_GL_MakeCurrent(self->window, self->ctx);
  glewExperimental = GL_TRUE;

  GLenum err;
  if ((err = glewInit()) != GLEW_OK) {
    sls_log_err("glew initialization failed %s", glewGetErrorString(err));
    exit(-1);
  }

  return self;
}
slsApp*
sls_delete_app(slsApp* self)
{
  if (self->window) {
    SDL_DestroyWindow(self->window);
  }
  return self;
}

void
sls_app_run(slsApp* self)
{
  self->should_close = false;
  glClearColor(1.0, 0.0, 1.0, 1.0);
  while (!self->should_close) {
    handle_sdlevents(self);

    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(self->window);

  }
}

static void
handle_sdlevents(slsApp* self)
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        self->should_close = true;
        break;
      case SDL_WINDOWEVENT:
        break;
      default:
        continue;
    }
  }
}
