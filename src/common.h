
#ifndef SLS_COMMON_H
#define SLS_COMMON_H
#include <GL/glew.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum slsResultCode slsResultCode;
enum slsResultCode {
  SLS_OK = (int)true,
  SLS_SUCCESS = (int)true,
  SLS_ERROR,
  SLS_SHADER_COMPILE_ERROR,
  SLS_PROGRAM_LINK_ERROR,
  SLS_N_RESULTS
};

static inline void
sls_set_result(slsResultCode* nullable_out, slsResultCode code)
{
  if (nullable_out) {
    *nullable_out = code;
  }
}

#endif // !SLS_COMMON_H
