#include "../stdhdr.h"
#include "sls-mainscene.h"
#include "sls-statestack.h"
#include "../graphics/sls-content.h"
#include "../graphics/sls-mesh.h"
#include "sls-gamewindow.h"
#include "../linalg/sls-mat4.h"

slsStateNode *slsMainScene_new()
{
	__block slsStateNode *self = NULL;
	__block slsMesh *mesh = NULL;
	__block slsShader *shader = NULL;
	__block slsMat4f projection;
	__block slsMat4f view;

	view = projection = slsMat4f_identity();

	self = slsStateNode_new();
	check_mem(self);
	self->cb_type = SLS_STATE_CALLBACK_BLOCK;

	slsStateBlocks cb = {};

	cb.start = ^(){
		if (!self->host && self->host->window) {
			return;
		}
		slsContentManager *mgr = self->host->window->mgr;
		if (!mgr) {
			return;
		}
		mesh = slsMesh_newSquareMesh();
		if (mesh) {
			slsContentManager_loadExistingMesh(
				mgr,
				"mesh",
				mesh);
		}
		shader = slsContentManager_load_shader(
			mgr,
			"shader",
			"s.vert",
			"s.frag");
	};
	cb.end = ^() {};

	cb.resize = ^(int w, int h) {
		double aspect = w/(double)h;
		projection = slsMat4f_ortho(
			-aspect, aspect,
			-1, 1,
			-1, 1
		);
		//slsMat4f_print(&projection);
		sls_push_matrix_unif(&projection, shader->uniforms.projection);

	};

	cb.poll_events = ^(SDL_Event *e) {};
	cb.update = ^(double dt)
	{

	};
	cb.draw = ^(double dt) {
		slsMsg(mesh, draw, shader, GL_TRIANGLES);
	};

	self->cb_blocks = sls_stateblocks_copy(&cb);

	return self;
error:
	
	if (self && self->dtor) {
		slsMsg(self, dtor);
	}
	return NULL;
}
