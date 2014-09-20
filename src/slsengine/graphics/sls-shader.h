#ifndef __SLS_SHADER_H__
#define __SLS_SHADER_H__

#include <GL/glew.h>
#include "../linalg/sls-mat4.h"

typedef struct _slsShader slsShader;
typedef struct _slsShaderAttributes slsShaderAttributes;
typedef struct _slsShaderUnifs slsShaderUnifs;

struct _slsShaderAttributes{
	GLint vertPosition;
	GLint vertNormal;
	GLint vertUv;
};

struct _slsShaderUnifs{
	// matrix uniforms
	GLint projection;
	GLint view;
	GLint model;
	GLint normal;
};

struct _slsShader {
	GString *name;
	GLuint program;

	slsShaderAttributes attributes;
	slsShaderUnifs uniforms;
	// methods
	void (*enableAttrs)(slsShader*self);
	void (*disableAttrs)(slsShader*self);
	void (*dtor)	(slsShader *self);
};

slsShader *slsShader_create(char const *shader_name, char const *vspath, char const *fspath);
void slsShader_destroy(slsShader *self);
void slsShader_enableAttrs(slsShader *self);
void slsShader_disableAttrs(slsShader *self);

void sls_push_matrix_unif(slsMat4f const *M, SLint uniform);

#endif