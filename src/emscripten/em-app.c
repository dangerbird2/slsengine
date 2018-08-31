/**
 * @file ${FILE}
 * @brief
 * @license ${LICENSE}
 * Copyright (c) 8/4/18, Steven
 *
 **/


#include "slsapp.h"


static slsApp *main_loop_app;
static void main_loop_fn(){
  assert(main_loop_app);
  if (main_loop_app->should_close){
    emscripten_cancel_main_loop();
    return;
  }
  sls_app_iter(main_loop_app);
}



void
sls_app_run(slsApp *self)
{
  self->should_close = false;
  self->is_showing_gui = true;

  glClearColor(1.0, 0.0, 1.0, 1.0);

  main_loop_app = self;
  emscripten_set_main_loop(main_loop_fn, 0, false);
}

void sls_app_gui(slsApp *self) {
  if (nk_begin(self->nuklear, "window", nk_rect(50, 50, 100, 100),
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
               NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

  }
  nk_end(self->nuklear);
}
