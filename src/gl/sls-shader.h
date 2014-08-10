#ifndef __SLS_SHADER_H__
#define __SLS_SHADER_H__

#include "../stdhdr.h"

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

	void (*dtor)	(slsShader *self);
};

slsShader *slsShader_create(char const *shader_name, char const *vspath, char const *fspath);
void slsShader_destroy(slsShader *self);

#endif