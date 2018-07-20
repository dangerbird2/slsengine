#include "common.h"
#include "slsapp.h"
#include "slsmacros.h"

static void
on_exit()
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
  atexit(on_exit);

  slsApp app;

  sls_create_app(&app);
  sls_app_run(&app);
  sls_delte_app(&app);
  slsResult *res = sls_resultf(SLS_OK, "everything's good %s\n", "bob");
  sls_log_info("%s", res->message);

  return 0;
}
