#ifndef __SLS_MAT4_H__
#define __SLS_MAT4_H__

#include "../types.h"
#include "vectypes.h"

typedef struct _slsMat4f slsMat4f;

struct _slsMat4f {
	vec4f mat[4];
};

bool slsMat4f_eq(slsMat4f const *A, slsMat4f const *B);

vec4f slsMat4f_getCol(slsMat4f const*A, int i);

slsMat4f slsMat4f_identity();
slsMat4f slsMat4f_translation(vec3f d);
slsMat4f slsMat4f_scale(vec3f d);

slsMat4f slsMat4f_mul(slsMat4f const *A, slsMat4f const *B);
slsMat4f slsMat4f_mul_scalar(slsMat4f const *A, float const n);
vec4f slsMat4f_mul_vec4f(slsMat4f const *M, vec4f v);

slsMat4f slsMat4f_ortho(
	double left,
	double right,
	double bottom,
	double top,
	double near,
	double far);
//slsMat4f slsMat4f_perspective();


/**
 * @brief copies matrix elements to float pointer
 * @details [long description]
 * 
 * @param arr : pointer to float array
 * @param M [description]
 */
static inline void slsMat4f_toArray(float arr[16], slsMat4f const*M)
{
	for (int i=0; i<4; i++) {
		vec4f_toArray(&arr[i * 4], M->mat[i]);
	}
}

static inline void slsMat4f_print(slsMat4f const *A)
{
	if (!A) {return;}
	for (int i=0; i<4; i++) {
		print_vec4_short(A->mat[i]);
	}

}

#endif