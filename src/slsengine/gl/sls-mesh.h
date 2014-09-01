#ifndef __SLS_MESH_H__
#define __SLS_MESH_H__

#include <glib.h>
#include <GL/glew.h>
#include "../linalg/vectypes.h"
#include "../linalg/sls-mat4.h"
#include "../types.h"
#include "sls-shader.h"

typedef struct _slsMesh slsMesh;
typedef struct _slsVertex slsVertex;

struct _slsVertex {
	float position[3];
	float normal[3];
	float uv[2];
};

char *slsVertex_toString(slsVertex const *vert);

struct _slsMesh {
	SLuint vbo;
	SLuint ibo;

	GArray *vertices;
	GArray *indices;

	slsMat4f transform;

	/** methods */
	slsMesh *(*init) (slsMesh *self);
	void *(*dtor) (slsMesh *self);

	void (*loadVerts)(slsMesh *self, slsVertex *verts,
		SLuint n_verts,	SLenum buffer_usage);

	void (*loadElements)(slsMesh *self, SLushort *elements,
		SLuint n_elements, SLenum buffer_usage);

	void (*bindVbo)(slsMesh *self, SLenum buffer_usage);
	void (*bindIbo)(slsMesh *self, SLenum buffer_usage);

	void (*bindTransform)(slsMesh *self, SLint model);

	void (*draw)(slsMesh *self, slsShader *shader, SLenum draw_type);
};

/**
 * @brief allocates a mesh struct
 * @details creates a mesh object, including vert and index arrays.
 * @return mesh
 */
slsMesh *slsMesh_alloc();
slsMesh *slsMesh_init(slsMesh *self);

slsMesh *slsMesh_newSquareMesh();

void *slsMesh_free(slsMesh *mesh);

void slsMesh_loadVerts(slsMesh *mesh, slsVertex *verts,
	SLuint n_verts,	SLenum buffer_usage);
void slsMesh_loadElements(slsMesh *mesh, SLushort *elements,
	SLuint n_elements, SLenum buffer_usage);

void slsMesh_bindVbo(slsMesh *mesh, SLenum buffer_usage);
void slsMesh_bindIbo(slsMesh *mesh, SLenum buffer_usage);

void slsMesh_bindTransform(slsMesh *self, SLint model);

void slsMesh_draw(slsMesh *self, slsShader *shader, SLenum draw_type);

#endif