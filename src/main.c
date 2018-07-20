#include "common.h"
#include "slsapp.h"
#include "slsmacros.h"

static void
sls_exit_cleanup()
{
  SDL_Quit();
}
int
main(int argc, char** argv)
{
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    sls_log_err("Init failed: %s", SDL_GetError());
    exit(-1);
  }
  atexit(sls_exit_cleanup);

  slsApp app;

  sls_create_app(&app);
  sls_app_run(&app);
  sls_delte_app(&app);

  return 0;
}
