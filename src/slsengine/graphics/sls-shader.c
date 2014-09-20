#include "../stdhdr.h"
#include "sls-shader.h"
#include "shaderutils.h"



slsShader *slsShader_create(char const *shader_name, char const *vspath, char const *fspath)
{
	/*
	 * allocate self & check for memory error
	 */
	slsShader *self = NULL;
	self = malloc(sizeof(slsShader));
	g_return_val_if_fail(self != NULL, NULL);

	/*
	 * create GString name -- must me freed in destructor
	 */
	self->name = g_string_new(shader_name);

	/*
	 * create and compile GLSL program using shaderutils.h functions
	 */
	self->program = create_program(vspath, fspath);

	/*
	 * get attribute locations, and store indices in slsShaderAttributes &
	 * slsShaderUnifs structs
	 */
	self->attributes = (slsShaderAttributes) {
		.vertPosition = get_attrib(self->program, "vertPosition"),
		.vertNormal = 	get_attrib(self->program, "vertNormal"),
		.vertUv = 		get_attrib(self->program, "vertUv")
	};

	self->uniforms = (slsShaderUnifs) {
		.projection = 	get_uniform(self->program, "projection"),
		.view = 		get_uniform(self->program, "view"),
		.model = 		get_uniform(self->program, "model"),
		.normal = 		get_uniform(self->program, "normal")
	};

	self->dtor = slsShader_destroy;
	self->enableAttrs = slsShader_enableAttrs;
	self->disableAttrs = slsShader_disableAttrs;

	return self;
}
void slsShader_destroy(slsShader *self)
{
	g_return_if_fail(self);
	if (self->name) {g_string_free(self->name, TRUE);}

	// delete the program
	glDeleteProgram(self->program);

	if (self) {free(self);}
}

void slsShader_enableAttrs(slsShader *self)
{
	SLint attributes[] = {
		self->attributes.vertPosition,
		self->attributes.vertNormal,
		self->attributes.vertUv};

	
	glUseProgram(self->program);
	for (int i=0; i<sizeof(attributes)/sizeof(SLint); i++) {
		glEnableVertexAttribArray(attributes[i]);
	}
}

void slsShader_disableAttrs(slsShader *self)
{
	SLint attributes[] = {
		self->attributes.vertPosition,
		self->attributes.vertNormal,
		self->attributes.vertUv};

	for (int i=0; i<sizeof(attributes)/sizeof(SLint); i++) {
		glDisableVertexAttribArray(attributes[i]);
	}

	glUseProgram(0);
}

void sls_push_matrix_unif(slsMat4f const *M, SLint uniform)
{

	if (uniform < 0) {return;}
	vec4f const *m = M->mat;
	float arr[16] = {
		m[0].x, m[0].y, m[0].z, m[0].w,
		m[1].x, m[1].y, m[1].z, m[1].w,
		m[2].x, m[2].y, m[2].z, m[2].w,
		m[3].x, m[3].y, m[3].z, m[3].w,
	};
	glUniformMatrix4fv(uniform, 1, true, arr);
}