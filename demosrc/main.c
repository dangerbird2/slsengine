#include <GL/glew.h>

#include "../src/slsengine.h"
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

void demo_render(slsGlWindow *self, void *data);
void init_rsc(slsGlWindow *window);
void free_rsc();
void Demo_render (slsGlWindow *self, void *data);

static slsContentManager *sMgr = NULL;
static slsShader *sShader = NULL;
static slsMesh *sMesh = NULL;


void init_rsc(slsGlWindow *window)
{
	sMgr = slsContentManager_create();

	sShader = slsContentManager_load_shader(
		sMgr,
		"sShader",
		"content/s.vert",
		"content/s.frag"
	);

	sMesh = slsContentManager_loadExistingMesh(
		sMgr,
		"square",
		slsMesh_newSquareMesh());

	mat4x4 mat;
	mat4x4_scale(mat, sMesh->transform, 0.5);
	mat4x4_dup(sMesh->transform, mat);
}

void free_rsc()
{
	slsContentManager_destroy(sMgr);
}

void Demo_render (slsGlWindow *self, void *data)
{
	
	glClear(
		GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);

	slsMsg(sMesh, draw, sShader, GL_TRIANGLES);

	SDL_GL_SwapWindow(self->super->window);
}

SLbool demo(int *argc, char const **argv[])
{
	slsGlWindow *window = NULL;
	window = slsGlWindow_create("demo", NULL);
	g_return_val_if_fail(window != NULL, false);

	init_rsc(window);

	window->render = Demo_render;

	if (window->run != NULL){
		window->run(window, NULL);
	}
	free_rsc();
	slsMsg(window, dtor);
	return true;
}


int main(int argc, char const *argv[])
{
	assert(init_Sls());
	atexit(quit_Sls);

	assert(demo(&argc, &argv));
	return 0;
}