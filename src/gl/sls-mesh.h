#ifndef __SLS_MESH_H__
#define __SLS_MESH_H__

#include <GL/glew.h>
#include "../types.h"

typedef struct _slsMesh slsMesh;
typedef struct _slsVertex slsVertex;

struct _slsVertex {
	float position[3];
	float normal[3];
	float uv[2];
};

struct _slsMesh {
	SLuint vbo;
	SLuint ibo;

	/* number of vert elements*/
	SLuint n_verts;
	/* number of allocated vert elements*/
	SLuint n_alloced_verts;
	slsVertex *vertices;

	/* number of index elements*/
	SLuint n_elements;
	/* number of allocated index elements*/
	SLuint n_alloced_elements;
	SLuint *indices;
};

/**
 * @brief allocates a mesh struct
 * @details creates a mesh object, including vert and index arrays.
 * @return mesh
 */
slsMesh *slsMesh_alloc();

void slsMesh_free(slsMesh *mesh);

void slsMesh_load_verts(slsMesh *mesh, slsVertex *verts, SLuint n_verts);
void slsMesh_load_elements(slsMesh *mesh, slsVertex *elements, SLuint n_elements);

#endif