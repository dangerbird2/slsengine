
#include "slsapp.h"
#include "slsrenderer.h"


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
#ifndef __EMSCRIPTEN__
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    sls_log_err("could not load GLAD");
    exit(255);
  }
#endif


  self->renderer = sls_create_renderer(malloc(sizeof(slsRenderer)), self->window,
                                       self->ctx, &result);
  sls_check(result == SLS_OK, "create_renderer failed: %s",
            sls_result_code_tostring(result));

  sls_create_world(&self->world, 256);

  slsMat4 sprite_xform;
  mat4x4_identity(sprite_xform.m);
  mat4x4_translate(sprite_xform.m, 30.f, 20.f, 0.0);

  long sprite = sls_world_create_sprite(&self->world, &sprite_xform);
  mat4x4_translate(sprite_xform.m, 30.f, 10.f, 0.0);
  sls_world_create_sprite(&self->world, &sprite_xform);
  mat4x4_identity(sprite_xform.m);
  long player_sprite = sls_world_create_sprite(&self->world, &sprite_xform);
  self->world.masks[player_sprite] |=
      SLS_COMPONENT_PLAYERCONTROLLED | SLS_COMPONENT_MOVEMENT;
  self->world.motions[player_sprite].speed = 10.f;


  return self;

error:

  return sls_delete_app(self);
}

slsApp *
sls_delete_app(slsApp *self)
{

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



  sls_app_update(self, dt);

  sls_renderer_clear(self->renderer);

  sls_render_sprite_system(self->renderer, &self->world);


  SDL_GL_SwapWindow(self->window);
}


static void
handle_windowevent(slsApp *self, SDL_WindowEvent const *windowevent);

static void
handle_sdlevents(slsApp *self)
{
  SDL_Event event;
  const bool is_showing_gui = self->is_showing_gui;

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
  }
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

static slsVec2 get_axes()
{
  uint8_t const *keys = SDL_GetKeyboardState(NULL);
  slsVec2 res = {0, 0};
  if (keys[SDL_SCANCODE_W]) {
    res.y += 1.f;
  }
  if (keys[SDL_SCANCODE_S]) {
    res.y -= 1.f;
  }
  if (keys[SDL_SCANCODE_D]) {
    res.x += 1.f;
  }
  if (keys[SDL_SCANCODE_A]) {
    res.x -= 1.f;
  }
  return res;
}


void sls_app_update(slsApp *self, double dt)
{
  slsEntityWorld *world = &self->world;
  for (int i = 0; i < world->length; ++i) {
    const slsComponentMask mask = world->masks[i];
    if ((mask & (SLS_COMPONENT_MOVEMENT | SLS_COMPONENT_PLAYERCONTROLLED)) != 0) {
      // player movement system
      slsVec2 axis = get_axes();
      slsVec2 tmp = axis;
      float len = vec2_len(axis.array);
      if(len >= 0.01f) {
        vec2_norm(axis.array, tmp.array);
      }

      vec2_scale(axis.array, axis.array, world->motions[i].speed);
      world->motions[i].velocity = axis;
    }
    if ((mask & (SLS_COMPONENT_MOVEMENT | SLS_COMPONENT_TRANSFORM) )!= 0){
      slsVec2 move;
      vec2_scale(move.array, world->motions[i].velocity.array, (float)dt);
      slsMat4 tmp, res = {};
      mat4x4_translate(tmp.m, move.x, move.y, 0.f);
      mat4x4_mul(res.m, world->transforms[i].m, tmp.m);
      world->transforms[i] = res;

    }
  }
}
