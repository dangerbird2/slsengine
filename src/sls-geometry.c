#include "sls-geometry.h"

slsGpuMesh* sls_create_sprite_geometry(slsGpuMesh* self)
{
  slsVec3 positions[] = {
    {-1.f, -1.f, 0.f},
    {1.f, -1.f, 0.f},
    {1.f, 1.f, 0.f},
    {-1.f, 1.f, 0.f},
  };
  slsVec3 normal = {0.0, 0.0, 1.0};
  slsVec2 uvs[] = {
    {0.0, 0.0},
    {1.0, 0.0},
    {1.0, 1.0},
    {0.0, 1.0}
  };
  uint32_t indices[] = {0, 1, 2, 2, 3, 0};
  self->verts = calloc(4, sizeof(slsGpuVertex));
  self->indices = calloc(6, sizeof(uint32_t));
  self->n_verts = 4;
  self->n_indices = 6;

  for (int i = 0; i < 4; ++i)
  {
    self->verts[i] =
      (slsGpuVertex) {
        .position = positions[i],
        .normal = normal,
        .uv = uvs[i]
      };
  }
  memcpy(self->indices, indices, sizeof(indices));
  return self;
}

slsGpuMesh* sls_delete_gpumesh(slsGpuMesh* self)
{
  free(self->indices);
  free(self->verts);
  self->n_indices = 0;
  self->n_verts = 0;
  return self;
}
