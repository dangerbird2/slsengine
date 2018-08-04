/**
 * @file ${FILE}
 * @brief 
 * @license ${LICENSE}
 * Copyright (c) 8/4/18, Steven
 * 
 **/
#include <sls-nuklear.h>
#include <slsmath.h>
#include <slsrenderer.h>
#include "slsapp.h"


void
sls_app_run(slsApp *self)
{
  self->should_close = false;
  self->is_showing_gui = false;
  self->renderer->clear_color = (slsVec4) {0.1, 0.5, 0.9, 1.0};

  while (!self->should_close) {
    sls_app_iter(self);
  }

}

void sls_app_gui(slsApp *self)
{

  slsVec4 *c = &self->renderer->clear_color;
  uint32_t flags = NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                   NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE;
  if (nk_begin(self->nuklear, "clear-color", nk_rect(40.f, 40.f, 250.0, 210.0), flags)) {
    nk_layout_row_begin(self->nuklear, NK_STATIC, 200.0, 4);
    {
      nk_layout_row_push(self->nuklear, 200.0);
      struct nk_colorf color = (struct nk_colorf) {c->r, c->g, c->b, c->a};
      color = nk_color_picker(self->nuklear, color, NK_RGB);
      *c = (slsVec4) {color.r, color.g, color.b, 1.0};
    }
    nk_layout_row_end(self->nuklear);
  }
  nk_end(self->nuklear);
}