#include "sls-mesh.h"
#include "../stdhdr.h"

#define SLS_MESH_INITIAL_N_ALLOC 20

// when index/vertex indices are resized, this is the buffer size allocated
#define SLS_MESH_ALLOC_BUFFER 20

slsMesh *slsMesh_alloc()
{
	slsMesh *mesh = NULL;
	mesh = malloc(sizeof(slsMesh));
	g_return_val_if_fail(mesh != NULL, NULL);

	/** generate buffers **/
	SLuint buffers[2];
	glGenBuffers(2, &(*buffers));
	mesh->vbo = buffers[0];
	mesh->ibo = buffers[1];

	mesh->n_verts = 0;
	mesh->n_alloced_verts = SLS_MESH_INITIAL_N_ALLOC;
	mesh->vertices = calloc(SLS_MESH_INITIAL_N_ALLOC, sizeof(slsVertex));

	if (!mesh->vertices) {
		slsMesh_free(mesh);
		g_return_val_if_reached(NULL);
	}

	mesh->n_elements = 0;
	mesh->n_alloced_elements = SLS_MESH_INITIAL_N_ALLOC;
	mesh->indices = calloc(SLS_MESH_INITIAL_N_ALLOC, sizeof(SLuint));

	if (!mesh->indices) {
		slsMesh_free(mesh);
		g_return_val_if_reached(NULL);
	}

	return mesh;

}

void slsMesh_free(slsMesh *mesh)
{
	if (!mesh) {g_return_if_reached();}

	GLuint buffers[] = {mesh->vbo, mesh->ibo};
	glDeleteBuffers(2, buffers);

	if (mesh->indices) {
		free(mesh->indices);
	}
	if (mesh->vertices) {
		free(mesh->vertices);
	}

	if (mesh) {
		free(mesh);
	}

}

void slsMesh_load_verts(slsMesh *mesh, slsVertex *verts, SLuint n_verts)
{
	/** realloc vertex pointer if necessary **/
	if (n_verts >= mesh->n_alloced_verts) {
		SLuint allocation = n_verts + SLS_MESH_ALLOC_BUFFER;
		realloc(mesh->vertices,
			allocation * sizeof(slsVertex));
		mesh->n_alloced_verts = allocation;
	}

	/** set new vert pointer length */
	mesh->n_verts = n_verts;

	/** copy verts to mesh->verts **/
	memcpy(mesh->vertices, verts, sizeof(slsVertex) * n_verts);
}