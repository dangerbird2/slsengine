
#include "slsapp.h"
#include "slsrenderer.h"
#include "sls-nuklear.h"



#ifdef __EMSCRIPTEN__


#endif

static void
handle_sdlevents(slsApp *self);

static void setup_gl_attributes(slsApp *self)
{
#ifndef __EMSCRIPTEN__
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#endif
}

slsApp *
sls_create_app(slsApp *self)
{
  *self = (slsApp) {0};
  slsResultCode result = SLS_OK;

  self->window = SDL_CreateWindow("window",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  640,
                                  480,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                  SDL_WINDOW_SHOWN);

  setup_gl_attributes(self);
  self->ctx = SDL_GL_CreateContext(self->window);
  SDL_GL_MakeCurrent(self->window, self->ctx);

  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    sls_log_err("could not load GLAD");
    exit(255);
  }
  self->nuklear = nk_sdl_init(self->window);

  struct nk_font_atlas *atlas;
  nk_sdl_font_stash_begin(&atlas);

  nk_sdl_font_stash_end();

  self->renderer = sls_create_renderer(malloc(sizeof(slsRenderer)), self->window,
                                       self->ctx, &result);
  sls_check(result == SLS_OK, "create_renderer failed: %s",
            sls_result_code_tostring(result));

  sls_create_world(&self->world, 256);

  slsMat4 sprite_xform;
  mat4x4_identity(sprite_xform.m);
  mat4x4_translate(sprite_xform.m, 100.f, 20.f, 0.0);

  long sprite = sls_world_create_sprite(&self->world, &sprite_xform);
  return self;

error:

  return sls_delete_app(self);
}

slsApp *
sls_delete_app(slsApp *self)
{

  nk_sdl_shutdown();
  sls_destroy_world(&self->world);

  if (self->renderer) {
    sls_delete_renderer(self->renderer);
    free(self->renderer);
  }

  if (self->window) {
    SDL_DestroyWindow(self->window);
  }
  return self;
}

void sls_app_iter(slsApp *self)
{
  double dt, now;
  now = sls_get_time();
  dt = now - self->last_time;
  self->last_time = now;
  handle_sdlevents(self);

  if (self->is_showing_gui) {
    sls_app_gui(self);
  }

  sls_app_update(self, dt);

  sls_renderer_clear(self->renderer);

  sls_render_sprite_system(self->renderer, &self->world);

  if (self->is_showing_gui) {
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
  }

  SDL_GL_SwapWindow(self->window);
}


static void
handle_windowevent(slsApp *self, SDL_WindowEvent const *windowevent);

static void
handle_sdlevents(slsApp *self)
{
  SDL_Event event;
  const bool is_showing_gui = self->is_showing_gui;
  if (is_showing_gui) nk_input_begin(self->nuklear);

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        self->should_close = true;
        break;
      case SDL_WINDOWEVENT:
        handle_windowevent(self, &event.window);
        break;
      case SDL_KEYDOWN: {
        SDL_KeyboardEvent *key;
        key = &event.key;



        bool is_shift = 0 != (key->keysym.mod & KMOD_SHIFT);
        if (key->keysym.sym == SDLK_BACKQUOTE && is_shift) {
          self->is_showing_gui = !self->is_showing_gui;
        }
        break;
      }
      default:
        break;
    }
    if (is_showing_gui) nk_sdl_handle_event(&event);
  }
  if (is_showing_gui) nk_input_end(self->nuklear);
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


void sls_app_update(slsApp *self, double dt)
{
  const uint8_t *keyboard_state = SDL_GetKeyboardState(NULL);
  self->object_rotate_input = 0;
  if(keyboard_state[SDL_SCANCODE_D]) {
    self->object_rotate_input += 1;
  }
  if (keyboard_state[SDL_SCANCODE_A]){
    self->object_rotate_input -= 1;
  }

  if (self->object_rotate_input) {
    double angular_speed = 10.0;
    self->object_rotation_radians += (angular_speed * dt * (float)self->object_rotate_input);
  }
}