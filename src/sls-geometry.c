#include "sls-geometry.h"

slsMesh*
sls_create_sprite_geometry(slsMesh* self)
{
  slsVec3 positions[] = {
    { -1.f, -1.f, 0.f },
    { 1.f, -1.f, 0.f },
    { 1.f, 1.f, 0.f },
    { -1.f, 1.f, 0.f },
  };
  slsVec3 normal = { 0.0, 0.0, 1.0 };
  slsVec2 uvs[] = { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } };
  uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
  self->verts = calloc(4, sizeof(slsVertex));
  self->indices = calloc(6, sizeof(uint32_t));
  self->n_verts = 4;
  self->n_indices = 6;

  for (int i = 0; i < 4; ++i) {
    self->verts[i] =
      (slsVertex){.position = positions[i], .normal = normal, .uv = uvs[i] };
  }
  memcpy(self->indices, indices, sizeof(indices));
  return self;
}

slsMesh*
sls_delete_gpumesh(slsMesh* self)
{
  free(self->indices);
  free(self->verts);
  self->n_indices = 0;
  self->n_verts = 0;
  return self;
}

slsMesh*
sls_create_mesh_grid(slsMesh* self)
{
  const size_t rows_per_chunk = 32;
  const size_t cols_per_chunk = 32;
  const size_t cells_per_chunk = rows_per_chunk * cols_per_chunk;

  const size_t n_vertices = 4 * cells_per_chunk;
  const size_t n_indices = 6 * cells_per_chunk;
  const float cell_size = 1.f;

  uint32_t* indices = calloc(n_indices, sizeof(*indices));
  slsVertex* verts = calloc(n_vertices, sizeof(*verts));

  uint32_t* index_itor = indices;
  slsVertex* vert_itor = verts;

  size_t loop_index = 0;
  for (int j = 0; j < rows_per_chunk; ++j) {
    for (int i = 0; i < cols_per_chunk; ++i, ++loop_index) {
      uint32_t vert_element_offset = 4 * (uint32_t)loop_index;
      float y = cell_size * j;
      float x = cell_size * i;

      uint32_t quad_indices[] = {
        vert_element_offset + 0, vert_element_offset + 1,
        vert_element_offset + 2,

        vert_element_offset + 2, vert_element_offset + 3,
        vert_element_offset + 0,
      };
      slsVertex quad_vert[] = {
        {.position = { x, y, 0.f } },
        {.position = { x + cell_size, y, 0.f } },
        {.position = { x + cell_size, y + cell_size, 0.f } },
        {.position = { x, y + cell_size, 0.f } }
      };

      memcpy(index_itor, quad_indices, sizeof(quad_indices));
      memcpy(vert_itor, quad_vert, sizeof(quad_vert));
      index_itor += 6;
      vert_itor += 4;
    }
  }

  *self = (slsMesh){.n_indices = n_indices,
                    .n_verts = n_vertices,
                    .verts = verts,
                    .indices = indices };

  return self;
}
