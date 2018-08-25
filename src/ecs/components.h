
/**
 * @file ${FILE}
 * @brief 
 * @license ${LICENSE}
 * Copyright (c) 8/17/18, Steven
 * 
 **/
#ifndef SLS_ENGINE_COMPONENTS_H
#define SLS_ENGINE_COMPONENTS_H

#include <common.h>
#include <slsmath.h>

SLS_BEGIN_CDECLS

typedef struct slsPlayerInput {
  slsVec2 moveAxis;
}slsPlayerInput;

typedef struct slsMotion {
  slsVec2 velocity;
  float speed;
} slsMotion;




SLS_END_CDECLS

#endif //SLS_ENGINE_COMPONENTS_H
