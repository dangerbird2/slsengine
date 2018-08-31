#include "common.h"
#include "results.h"
#include "shaderutils.h"
#include "slsapp.h"
#include "slsmacros.h"
#include "sls-geometry.h"


static void
sls_exit_cleanup()
{
  SDL_Quit();
}

#ifndef SLS_TEST_RUNNER
int
main(int argc, char** argv)
{
  slsMesh grid_mesh;
  sls_create_mesh_grid(&grid_mesh);

  sls_delete_gpumesh(&grid_mesh);
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER )) {
    sls_log_err("Init failed: %s", SDL_GetError());
    exit(-1);
  }

  slsApp app;
  sls_create_app(&app);



  sls_app_run(&app);
  sls_delete_app(&app);
  sls_exit_cleanup();
  return 0;
}


#endif

