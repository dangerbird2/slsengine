#include <glib.h>
#include <slsengine/slsengine.h>
#include <stdio.h>

#define MESH_DATA_ARRAY_SIZE 100

typedef struct {
	SLuint nverts;
	slsVertex verts[MESH_DATA_ARRAY_SIZE];

	SLuint nelems;
	SLushort elems[MESH_DATA_ARRAY_SIZE];
} meshData;

typedef struct {
	slsMesh *mesh;
	slsGlWindow *window;
	meshData data;
} meshFix;



void mesh_teardown(meshFix *fix, gconstpointer data);
void mesh_setup(meshFix *fix, gconstpointer data);

void mesh_setup(meshFix *fix, gconstpointer data)
{
	fix->window = slsGlWindow_create("test", NULL);
	fix->mesh = slsMesh_alloc();

	fix->data.nverts = 10;
	fix->data.nelems = 10;
	for (int i=0; i<fix->data.nverts; i++) {
		for (int j=0; j<3; j++) {
			fix->data.verts[i].position[j] = 
				(float) g_test_rand_double_range(-1.0, 1.0);
			fix->data.verts[i].normal[j] = 
				(float) g_test_rand_double_range(-1.0, 1.0);
		} 
	}

	slsMsg(fix->mesh, loadVerts,
		fix->data.verts, fix->data.nverts, GL_STATIC_DRAW);

	slsMsg(fix->mesh, loadElements,
		fix->data.elems, fix->data.nelems, GL_STATIC_DRAW);

}

void mesh_teardown(meshFix *fix, gconstpointer data)
{
	slsMesh_free(fix->mesh);
	fix->window->dtor(fix->window);
}

void mesh_vertTest(meshFix *fix, gconstpointer data)
{
	slsMesh *mesh = fix->mesh;
	

#if 0
	for (int i=0; i<mesh->vertices->len; i++) {
		char const *vstr = slsVertex_toString(
			&g_array_index(mesh->vertices, slsVertex, i));

		printf("%s\n", vstr);

		free ((void *) vstr);

	}
#endif
	g_assert(mesh->vertices->len == fix->data.nverts);
}

void mesh_indexTest(meshFix *fix, gconstpointer data)
{
	slsMesh *mesh = fix->mesh;
	

	if (mesh->indices->len != fix->data.nelems) {
		log_err("mesh->indices->len == %i", mesh->indices->len);

		g_test_fail();
	}
	
}

void mesh_bufferTest(meshFix *fix, gconstpointer data)
{
	slsMesh *mesh = fix->mesh;

	GLint vbo_size, ibo_size;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);

	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &vbo_size);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &ibo_size);

	if (ibo_size != mesh->indices->len *  sizeof(SLushort)) {
		log_err("ibo_size %i != mesh indices size %lu", ibo_size, 
			sizeof(SLushort) * mesh->indices->len);
	}

	if (vbo_size != mesh->vertices->len *  sizeof(slsVertex)) {
		log_err("vbo_size %i != mesh vertices size", vbo_size);
	}


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void run_mesh_tests()
{
	struct meshTup {
		char const *name;
		void (* const fn)(meshFix*, void const *);
	};

	struct meshTup tests[] = {
		{"/Mesh/vertTest", mesh_vertTest},
		{"/Mesh/indexTest", mesh_indexTest},
		{"/Mesh/bufferTest", mesh_bufferTest}
	};
	const int len = sizeof(tests)/sizeof(struct meshTup);
	for (int i=0; i<len; ++i) {
		g_test_add(
			tests[i].name,
			meshFix,
			NULL,
			mesh_setup,
			tests[i].fn,
			mesh_teardown);
	}

}