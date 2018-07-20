#ifndef SLS_APP_H
#define SLS_APP_H

#include "common.h"
#include "slsmacros.h"
SLS_BEGIN_CDECLS


typedef enum slsResultCode slsResultCode;
enum slsResultCode {
    SLS_OK=(int)true,
    SLS_SUCCESS=(int)true,
    SLS_ERROR,
    SLS_N_RESULTS
};



typedef struct slsApp slsApp;
struct slsApp {
  SDL_Window* window;
  SDL_GLContext ctx;
  bool should_close;
};

slsApp*
sls_create_app(slsApp* app);
slsApp*
sls_delte_app(slsApp* app);

void
sls_app_run(slsApp* app);

SLS_END_CDECLS

#endif // !SLS_APP_H
