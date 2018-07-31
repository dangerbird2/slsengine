
#include "slsapp.h"
#include "slsrenderer.h"
#include "sls-nuklear.h"

static void sls_app_iter(slsApp *self);


#ifdef __EMSCRIPTEN__


static slsApp *main_loop_app;
static void main_loop_fn(){
  assert(main_loop_app);
  if (main_loop_app->should_close){
    emscripten_cancel_main_loop();
    return;
  }
  sls_app_iter(main_loop_app);
}

#endif

static void
handle_sdlevents(slsApp *self);

slsApp *
sls_create_app(slsApp *self)
{
  *self = (slsApp) {0};
  self->window = SDL_CreateWindow("window",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  640,
                                  480,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                  SDL_WINDOW_SHOWN);
#ifndef __EMSCRIPTEN__
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#endif
  self->ctx = SDL_GL_CreateContext(self->window);
  SDL_GL_MakeCurrent(self->window, self->ctx);

  slsResultCode result = SLS_OK;

#ifndef __EMSCRIPTEN__
  glewExperimental = GL_TRUE;

  GLenum err;
  if ((err = glewInit()) != GLEW_OK) {
    sls_log_err("glew initialization failed %s", glewGetErrorString(err));
    exit(-1);
  }
#endif
  self->nuklear = nk_sdl_init(self->window);

  struct nk_font_atlas *atlas;
  nk_sdl_font_stash_begin(&atlas);

  nk_sdl_font_stash_end();

  self->renderer = sls_create_renderer(malloc(sizeof(slsRenderer)), self->window,
                                       self->ctx, &result);
  sls_check(result == SLS_OK, "create_renderer failed: %s",
            sls_result_code_tostring(result));


  return self;

error:

  return sls_delete_app(self);
}

slsApp *
sls_delete_app(slsApp *self)
{

  nk_sdl_shutdown();
  if (self->renderer) {
    sls_delete_renderer(self->renderer);
    free(self->renderer);
  }

  if (self->window) {
    SDL_DestroyWindow(self->window);
  }
  return self;
}

void
sls_app_run(slsApp *self)
{
  self->should_close = false;
  glClearColor(1.0, 0.0, 1.0, 1.0);
#ifndef __EMSCRIPTEN__
  while (!self->should_close) {
    sls_app_iter(self);
  }
#else
  main_loop_app = self;
  emscripten_set_main_loop(main_loop_fn, 0, false);
#endif
}

static void sls_app_iter(slsApp *self)
{
  handle_sdlevents(self);

  if (nk_begin(self->nuklear, "window", nk_rect(50, 50, 100, 100),
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
               NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

  }
  nk_end(self->nuklear);


  glClearColor(0.f, 0.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);
  nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);


  SDL_GL_SwapWindow(self->window);
}


static void
handle_windowevent(slsApp *self, SDL_WindowEvent const *windowevent);

static void
handle_sdlevents(slsApp *self)
{
  nk_input_begin(self->nuklear);
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        self->should_close = true;
        break;
      case SDL_WINDOWEVENT:
        handle_windowevent(self, &event.window);
        break;
      default:

        break;
    }
    nk_sdl_handle_event(&event);
  }
  nk_input_end(self->nuklear);
}

static void
handle_windowevent(slsApp *self, SDL_WindowEvent const *windowevent)
{
  switch (windowevent->event) {
    case SDL_WINDOWEVENT_RESIZED:

      sls_renderer_onresize(self->renderer, windowevent->data1, windowevent->data2);
      break;
    default:
      break;
  }
}
