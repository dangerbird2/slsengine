#ifndef SLS_RESULT_H
#define SLS_RESULT_H
#include "common.h"

SLS_BEGIN_CDECLS

typedef enum slsResultCode {
  SLS_OK = (int)true,
  SLS_SUCCESS = (int)true,
  SLS_ERROR,
  SLS_COMPILE_FAILED,
  SLS_LINK_FAILED,
  SLS_N_RESULTS
} slsResultCode;

/**
 *
 **/
static inline char const*
sls_result_code_tostring(slsResultCode code)
{
  static const char* code_strings[] = {
    "SLS_OK = (int)true", "SLS_ERROR",     "SLS_COMPILE_FAILED",
    "SLS_LINK_FAILED",    "SLS_N_RESULTS",
  };
  static char const unknown_code[] = "code not found";
  switch (code) {
    case SLS_OK:
      return code_strings[0];

    case SLS_ERROR:
      return code_strings[1];
    case SLS_COMPILE_FAILED:
      return code_strings[2];
    case SLS_LINK_FAILED:
      return code_strings[3];
    case SLS_N_RESULTS:
      return code_strings[4];
    default:
      return unknown_code;
  }
}

static inline void
sls_set_result(slsResultCode* res_ptr, slsResultCode code)
{
  if (res_ptr) {
    *res_ptr = code;
  }
}

SLS_END_CDECLS

#endif // !  SLS_RESULT_H
