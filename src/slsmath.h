/**
 * @file ${FILE}
 * @brief 
 * @license ${LICENSE}
 * Copyright (c) 7/21/18, Steven
 * 
 **/
#ifndef SLS_ENGINE_SLSMATH_H
#define SLS_ENGINE_SLSMATH_H

#include "common.h"
#include <linmath.h>


SLS_BEGIN_CDECLS

#define SLS_EPSILON_FLOAT 0.01

static inline bool sls_nearf(float a, float b, float epsilon)
{
  float abs_a = fabsf(a);
  float abs_b = fabsf(b);

  float diff = fabsf(a - b);
  if (a == b) { return true; }
  if (a == 0 || b == 0 || diff < FLT_MIN)
  {
    return diff < (epsilon * FLT_MIN);
  }
  return diff / fminf(abs_a + abs_b, FLT_MAX) < epsilon;
}


typedef union slsVec2
{
  struct
  {
    float x, y;
  };

  struct
  {
    float r, g;
  };

  struct
  {
    float s, t;
  };

  float array[2];
} slsVec2;


typedef union slsVec3
{
  struct
  {
    float x, y, z;
  };

  struct
  {
    float r, g, b;
  };

  struct
  {
    float s, t, p;
  };

  float array[3];
} slsVec3;


typedef union slsVec4
{
  struct
  {
    float x, y, z, w;
  };

  struct
  {
    float r, g, b, a;
  };

  struct
  {
    float s, t, p, q;
  };

  float array[4];
} slsVec4;

typedef union slsQuat
{
  // math-style access
  struct
  {
    float a, b, c, d;
  };

  // vector-style access
  struct
  {
    float x, y, z, w;
  };

  float array[4];
} slsQuat;

static inline slsVec2
sls_vec2_make(float x, float y)
{
  const slsVec2 v = {x, y};
  return v;
}

static inline slsVec3
sls_vec3_make(float x, float y, float z)
{
  slsVec3 v = {x, y, z};
  return v;
}

static inline slsVec4
sls_vec4_make(float x, float y, float z, float w)
{
  slsVec4 v = {x, y, z, w};
  return v;
}

/**
 * @brief 3x3 Matrix in right-handed column major format
 * @details for binding to openGL uniforms, `transpose` parameter
 * should be GL_FALSE
 */
typedef struct
{
  float m[3][3];
} slsMat3;

/**
 * @brief 4x4 Matrix in right-handed column major format
 * @details for binding to openGL uniforms, `transpose` parameter
 * should be GL_FALSE
 */
typedef struct
{
  float m[4][4];
} slsMat4;


float sls_vec2_dot(slsVec2 const* a, slsVec2 const* b);

float sls_vec3_dot(slsVec3 const* a, slsVec3 const* b);

float sls_vec4_dot(slsVec4 const* a, slsVec4 const* b);


slsMat3* sls_mat3_identity(slsMat3* out);

slsMat4* sls_mat4_identity(slsMat4* out);


SLS_END_CDECLS

#endif //SLS_ENGINE_SLSMATH_H
