#include <GL/glew.h>

#include "../src/slsengine.h"
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

void demo_render(slsGlWindow *self, void *data);
void init_rsc(slsGlWindow *window);
void free_rsc();
void Demo_render (slsGlWindow *self, void *data);

static slsContentManager *sMgr;
static slsShader *sShader;


void init_rsc(slsGlWindow *window)
{
	sMgr = slsContentManager_create();

	sShader = slsContentManager_load_shader(
		sMgr,
		"sShader",
		"content/s.vert",
		"content/s.frag"
	);
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

	glUseProgram(sShader->program);
	glEnableVertexAttribArray(sShader->attributes.vertPosition);
	glEnableVertexAttribArray(sShader->attributes.vertUv);
	GLfloat triangle_vertices[] = {
		0.0,  0.8,
	   -0.8, -0.8,
		0.8, -0.8
	};

	GLfloat triangle_uv[] = {
		0.0, 0.0,
		0.5, 1.0,
		1.0, 0.0
	};

	/* Describe our vertices array to OpenGL (it can't guess its format automatically) */
	glVertexAttribPointer(
		sShader->attributes.vertPosition, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0, // no extra data between each position
		triangle_vertices  // pointer to the C array
	);

	glVertexAttribPointer(
		sShader->attributes.vertUv, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0, // no extra data between each position
		triangle_uv  // pointer to the C array
	);

	/* Push each element in buffer_vertices to the vertex shader */
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(sShader->attributes.vertPosition);
	glDisableVertexAttribArray(sShader->attributes.vertUv);

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
	window->dtor(window);
	return true;
}


int main(int argc, char const *argv[])
{
	assert(init_Sls());
	atexit(quit_Sls);

	assert(demo(&argc, &argv));
	return 0;
}