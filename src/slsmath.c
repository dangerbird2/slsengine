/**
 * @file ${FILE}
 * @brief 
 * @license ${LICENSE}
 * Copyright (c) 7/21/18, Steven
 * 
 **/
#include "slsmath.h"

#define RAYMATH_IMPLEMENTATION


float sls_vec2_dot(slsVec2 const *a, slsVec2 const *b)
{
  float acc = 0.0;
  acc += a->x * b->x;
  acc += a->y * b->y;
  return acc;
}

float sls_vec3_dot(slsVec3 const *a, slsVec3 const *b)
{
  float acc = 0.0;
  acc += a->x * b->x;
  acc += a->y * b->y;
  acc += a->z * b->z;

  return acc;
}

float sls_vec4_dot(slsVec4 const *a, slsVec4 const *b)
{
  float acc = 0.0;

  acc += a->x * b->x;
  acc += a->y * b->y;
  acc += a->z * b->z;
  acc += a->w * b->w;
  return acc;
}