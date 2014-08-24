#include "sls-mesh.h"
#include "../stdhdr.h"
#include "../linalg/linmath.h"

#define SLS_MESH_INITIAL_N_ALLOC 20

// when index/vertex indices are resized, this is the buffer size allocated
#define SLS_MESH_ALLOC_BUFFER 20

extern int asprintf(char **, char const *, ...);

char *slsVertex_toString(slsVertex const *vert)
{
	char *buffer = NULL;

	int n = asprintf(&buffer, 
		"v: %f %f %f, n: %f %f %f, uv: %f %f",
		vert->position[0], vert->position[1], vert->position[2],
		vert->normal[0], vert->normal[1], vert->normal[2],
		vert->uv[0], vert->uv[1]);
	
	if (n < 0) {
		log_err("memory error: slsVertex_toString");
		return NULL;
	}

	return buffer;
}


slsMesh *slsMesh_alloc()
{
	slsMesh *mesh = NULL;
	mesh = malloc(sizeof(slsMesh));
	g_return_val_if_fail(mesh, NULL);

	mesh->vertices = g_array_new(false, true, sizeof(slsVertex));
	g_return_val_if_fail(mesh->vertices, NULL);

	mesh->indices = g_array_new(false, true, sizeof(SLuint));
	g_return_val_if_fail(mesh->indices, NULL);


	mesh->init = slsMesh_init;
	mesh->dtor = slsMesh_free;

	mesh->loadVerts = slsMesh_loadVerts;
	mesh->loadElements = slsMesh_loadElements;

	mesh->bindVbo = slsMesh_bindVbo;
	mesh->bindIbo = slsMesh_bindIbo;

	mesh->draw = slsMesh_draw;

	return slsMsg(mesh, init);
}

slsMesh *slsMesh_init(slsMesh *self)
{
	if (!self) {
		log_warn("self is NULL");
		return NULL;
	}

	/** generate buffers **/
	SLuint buffers[2];
	glGenBuffers(2, &(*buffers));
	self->vbo = buffers[0];
	self->ibo = buffers[1];

	mat4x4_identity(self->transform);

	slsMsg(self, bindIbo, GL_STATIC_DRAW);
	slsMsg(self, bindVbo, GL_STATIC_DRAW);

	return self;
}

slsMesh *slsMesh_newSquareMesh()
{
	slsVertex verts[]= (slsVertex[]){
		{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
		{{-1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
		{{ 1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{ 1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}
	};

	SLushort indices[] = {0, 1, 2, 3, 2, 0};
	slsMesh *self = NULL;
	self = slsMesh_alloc();
	g_return_val_if_fail(self, NULL);

	slsMsg(self, loadVerts, verts, 4, GL_STATIC_DRAW);
	slsMsg(self, loadElements, indices, 6, GL_STATIC_DRAW);

	return self;
}


void *slsMesh_free(slsMesh *mesh)
{
	if (!mesh) {g_return_val_if_reached(NULL);}

	GLuint buffers[] = {mesh->vbo, mesh->ibo};
	glDeleteBuffers(2, buffers);

	if (mesh->indices) {
		g_array_unref(mesh->indices);
	}
	if (mesh->vertices) {
		g_array_unref(mesh->vertices);
	}

	if (mesh) {
		free(mesh);
	}

	return NULL;
}

void slsMesh_loadVerts(slsMesh *mesh, slsVertex *verts,
	SLuint n_verts,	SLenum buffer_usage)
{
	// clear vertices
	if (mesh->vertices->len > 0) {
		g_array_remove_range(
			mesh->vertices,
			0,
			mesh->vertices->len);
	}

	g_array_append_vals(
		mesh->vertices,
		(gconstpointer) verts,
		n_verts);

	slsMsg(mesh, bindVbo, buffer_usage);
}

void slsMesh_loadElements(slsMesh *mesh, SLushort *elements,
	SLuint n_elements, SLenum buffer_usage)
{
	if (mesh->indices->len > 0) {
		g_array_remove_range(
			mesh->indices,
			0,
			mesh->indices->len);
	}

	g_array_append_vals(
		mesh->indices,
		(gconstpointer) elements,
		n_elements);

	slsMsg(mesh, bindIbo, buffer_usage);

}

void slsMesh_bindVbo(slsMesh *mesh, SLenum buffer_usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(slsVertex) * mesh->vertices->len,
		(void *) mesh->vertices->data,
		buffer_usage
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void slsMesh_bindIbo(slsMesh *mesh, SLenum buffer_usage)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(SLushort) * mesh->indices->len,
		(void *) mesh->indices->data,
		buffer_usage
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void slsMesh_draw(slsMesh *self, slsShader *shader, SLenum draw_type)
{
	slsMsg(shader, enableAttrs);

	glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ibo);

	// push model transform uniform
	SLint model = shader->uniforms.model;
	glUniformMatrix4fv(model, 1, false, &(self->transform[0][0]));

	glVertexAttribPointer (
		shader->attributes.vertPosition, 3,
		GL_FLOAT, GL_FALSE, sizeof(slsVertex),
		(const void*)offsetof(slsVertex, position));

	glVertexAttribPointer (
		shader->attributes.vertNormal, 3,
		GL_FLOAT, GL_FALSE, sizeof(slsVertex),
		(const void*)offsetof(slsVertex, normal));

	glVertexAttribPointer (
		shader->attributes.vertUv, 2,
		GL_FLOAT, GL_FALSE, sizeof(slsVertex),
		(const void*)offsetof(slsVertex, uv));


	glDrawElements(draw_type, self->indices->len, GL_UNSIGNED_SHORT, 0);

	slsMsg(shader, disableAttrs);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
