#ifndef SLS_GEOMETRY_H
#define SLS_GEOMETRY_H
#include "common.h"
#include "slsmath.h"
SLS_BEGIN_CDECLS

/**
 * @brief GPU storage for a mesh vertex
 */
typedef struct slsGpuVertex
{
  slsVec3 position;
  slsVec3 normal;
  slsVec2 uv;
} slsGpuVertex;

typedef struct slsGpuMesh {
  slsGpuVertex *verts;
  size_t n_verts;
  uint32_t *indices;
  size_t n_indices;
} slsGpuMesh;

slsGpuMesh *sls_create_sprite_geometry(slsGpuMesh *self);

slsGpuMesh *sls_delete_gpumesh(slsGpuMesh *self);



SLS_END_CDECLS
#endif // !SLS_GEOMETRY_H
