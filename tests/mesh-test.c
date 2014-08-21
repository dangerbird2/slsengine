#include <glib.h>
#include "../src/slsengine.h"

#define MESH_DATA_ARRAY_SIZE 100

typedef struct {
	SLuint nverts;
	slsVertex verts[MESH_DATA_ARRAY_SIZE];

	SLuint nelems;
	SLuint elems[MESH_DATA_ARRAY_SIZE];
} meshData;

typedef struct {
	slsMesh *mesh;
	slsGlWindow *window;
	meshData data;
} meshFix;



void mesh_teardown(meshFix *fix, gconstpointer data);
void mesh_setup(meshFix *fix, gconstpointer data);
void mesh_testA(meshFix *fix, gconstpointer data);

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

}

void mesh_teardown(meshFix *fix, gconstpointer data)
{
	slsMesh_free(fix->mesh);
	fix->window->dtor(fix->window);
}

void mesh_testA(meshFix *fix, gconstpointer data)
{
	meshData *m = &(fix->data);
	for (int i=0; i<fix->data.nverts; i++) {
		printf("vert %i: %f %f %f", i, m->verts[i].position[0], m->verts[i].position[1], m->verts[i].position[2]);
	}
}

void run_mesh_tests()
{
	
	
	g_test_add(
		"/Mesh/vertA",
		meshFix,
		NULL,
		mesh_setup,
		mesh_testA,
		mesh_teardown
	);


}