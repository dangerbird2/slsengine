#include "../stdhdr.h"
#include "sls-mat4.h"

slsMat4f slsMat4f_identity()
{
	return (slsMat4f) { .mat = {
		(vec4f) {1.0f, 0.0f, 0.0f, 0.0f},
		(vec4f) {0.0f, 1.0f, 0.0f, 0.0f},
		(vec4f) {0.0f, 0.0f, 1.0f, 0.0f},
		(vec4f) {0.0f, 0.0f, 0.0f, 1.0f}}};
}

slsMat4f slsMat4f_translation(vec3f d)
{
	slsMat4f M = slsMat4f_identity();
	
	M.mat[0].w = d.x;
	M.mat[1].w = d.y;
	M.mat[2].w = d.z;
	return M;
}

slsMat4f slsMat4f_scale(vec3f d)
{
	slsMat4f M = slsMat4f_identity();
	M.mat[0][0] = d.x;
	M.mat[1][1] = d.y;
	M.mat[2][2] = d.z;

	return M;
}

bool slsMat4f_eq(slsMat4f const *A, slsMat4f const *B)
{
	bool eq = true;
	for (int i=0; i<4; i++) {
		if (!vec4f_eq(A->mat[i], B->mat[i])) {
			eq = false;
		}
	}
	return eq;
}

slsMat4f slsMat4f_mul_scalar(slsMat4f const *A, float const n)
{
	slsMat4f m;
	for (int i=0; i<4; i++) {
		m.mat[0] = vec4f_mul_scalar(m.mat[0], n);
	}
	return m;
}

vec4f slsMat4f_getCol(slsMat4f const*A, int i)
{
	vec4f const*Ap = A->mat;
	return (vec4f) {Ap[0][i], Ap[1][i], Ap[2][i], Ap[3][i]};
}

slsMat4f slsMat4f_mul(slsMat4f const *A, slsMat4f const *B)
{
	slsMat4f M = slsMat4f_identity();
	vec4f *m = M.mat;
	vec4f const *a = A->mat;
	vec4f const *b = B->mat;

	for (int j=0; j<4; j++) {
		for (int i=0; i<4; i++) {
			float ab = 0.0f;
			for (int k=0; k<4; k++) {
				ab += a[k][i] * b[j][k];
			}
			m[j][i] = ab;
		}
	}

	return M;
}

vec4f slsMat4f_mul_vec4f(slsMat4f const *M, vec4f v)
{
	vec4f r = {0, 0, 0, 0};
	for (int i=0; i<4; i++) {
		r[i] = vec4f_dot(M->mat[i], v);
	}

	return r;
}

