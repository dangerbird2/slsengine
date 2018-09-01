/**
 * @file ${FILE}
 * @brief
 * @license ${LICENSE}
 * Copyright (c) 8/4/18, Steven
 *
 **/
#include "slsapp.h"
#include <slsmath.h>
#include <slsrenderer.h>

void
sls_app_run(slsApp* self)
{
  self->should_close = false;
  self->is_showing_gui = false;
  self->renderer->clear_color = (slsVec4){ 0.1, 0.5, 0.9, 1.0 };
  self->last_time = sls_get_time();

  while (!self->should_close) {
    sls_app_iter(self);
  }
}

void
sls_app_gui(slsApp* self)
{
#if 0
  slsVec4 *c = &self->renderer->clear_color;
  uint32_t flags = NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                   NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE;
  struct nk_context *nk = self->nuklear;
  long player_sprite = -1;
  for (int i=0; i<self->world.length; ++i){
    slsComponentMask mask = self->world.masks[i];
    if ((mask & (SLS_COMPONENT_PLAYERCONTROLLED)) != 0){
      player_sprite = i;
      break;
    }
  }

  if (nk_begin(nk, "clear-color", nk_rect(40.f, 40.f, 250.0, 210.0), flags)) {
    nk_layout_row_begin(nk, NK_STATIC, 200.0, 4);
    {
      nk_layout_row_push(nk, 200.0);
      struct nk_colorf color = (struct nk_colorf) {c->r, c->g, c->b, c->a};
      color = nk_color_picker(nk, color, NK_RGB);
      *c = (slsVec4) {color.r, color.g, color.b, 1.0};
    }
    nk_layout_row_end(nk);

  }
  nk_end(nk);
#endif
}
