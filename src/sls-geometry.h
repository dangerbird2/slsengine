#ifndef SLS_GEOMETRY_H
#define SLS_GEOMETRY_H

#include "common.h"
#include "slsmath.h"

SLS_BEGIN_CDECLS

/**
 * @brief GPU storage for a mesh vertex
 */
typedef struct slsVertex {
  slsVec3 position;
  slsVec3 normal;
  slsVec3 color;
  slsVec2 uv;
} slsVertex;

typedef struct slsMesh {
  slsVertex* verts;
  size_t n_verts;
  uint32_t* indices;
  size_t n_indices;
} slsMesh;

slsMesh*
sls_create_sprite_geometry(slsMesh* self);

slsMesh*
sls_create_mesh_grid(slsMesh* self);

slsMesh*
sls_delete_gpumesh(slsMesh* self);

SLS_END_CDECLS
#endif // !SLS_GEOMETRY_H
