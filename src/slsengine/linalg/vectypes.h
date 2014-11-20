#ifndef __SLS_VEC_TYPES_H__
#define __SLS_VEC_TYPES_H__

#include <math.h>
#include <stdio.h>
#include "../types.h"
#include <stdbool.h>

/**s
 * macro to declare vector-type variable of user's choidce
 */
#define vector(type, n) type __attribute__((ext_vector_type(n)))

 /**
  * macro to add clang vector attribute to variable
  * used in defining lib's vector type
  */
#define __ext_vector(n) __attribute__((ext_vector_type(n)))

typedef float vec4f __ext_vector(4);
typedef float vec3f __ext_vector(3);
typedef float vec2f __ext_vector(2);

typedef double vec4d __ext_vector(4);
typedef double vec3d __ext_vector(3);
typedef double vec2d __ext_vector(2);

typedef int vec4i __ext_vector(4);
typedef int vec3i __ext_vector(3);
typedef int vec2i __ext_vector(2);


/**
 * utility macros for printing vectors in a consistent manner
 */
#define print_vec4(v) {printf("{%f %f %f %f}\n", v.x, v.y, v.z, v.w);}


#define print_vec4_short(v) do{								\
	printf("{%4f %4f %4f %4f}\n", v.x, v.y, v.z, v.w);	\
}while(0)
#define print_vec3(v) do{printf("{%f %f %f}\n", v.x, v.y, v.z);}while(0)
#define print_vec2(v) do{printf("{%f %f}\n", v.x, v.y);}while(0)


/**
 * Vec3f operations
 */


static inline float vec3f_dot(vec3f a, vec3f b)
{
	float sum = 0;
	for (int i=0; i<3; i++)	{
		sum += a[i] * b[i];
	}
	return sum;
}

static inline vec3f vec3f_mul_scalar(vec3f a, float n)
{
	return (vec3f) {a.x*n, a.y*n, a.z*n};
}

static inline vec3f vec3f_add_scalar(vec3f a, float n)
{
	return (vec3f) {a.x+n, a.y+n, a.z+n};
}

static inline vec3f vec3f_sub_scalar(vec3f a, float n)
{
	return (vec3f) {a.x-n, a.y-n, a.z-n};
}

static inline vec3f vec3f_div_scalar(vec3f a, float n)
{
	return (vec3f) {a.x/n, a.y/n, a.z/n};
}

static inline float vec3f_length(vec3f a)
{
	return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

static inline vec3f vec3f_normalize(vec3f a)
{
	float l = vec3f_length(a);
	return a / ((vec3f) {l, l, l});
}

/**
 * Vecr4f operations
 */

static inline vec4f vec4f_mul_scalar(vec4f a, float n)
{
	return (vec4f) {a.x*n, a.y*n, a.z*n, a.w*n};
}

static inline vec4f vec4f_add_scalar(vec4f a, float n)
{
	return (vec4f) {a.x+n, a.y+n, a.z+n, a.w+n};
}

static inline vec4f vec4f_sub_scalar(vec4f a, float n)
{
	return (vec4f) {a.x-n, a.y-n, a.z-n, a.w-n};
}

static inline vec4f vec4f_div_scalar(vec4f a, float n)
{
	return (vec4f) {a.x/n, a.y/n, a.z/n, a.w/n};
}




static inline float vec4f_dot(vec4f a, vec4f b)
{
	return vec3f_dot(a.xyz, b.xyz) + a.w * b.w;
}

static inline float vec4f_length(vec4f a)
{
	return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w*a.w));
}

static inline vec4f vec4f_normalize(vec4f a)
{
	float l = vec4f_length(a);
	return a / ((vec4f) {l, l, l, l});
}

static inline bool vec4f_eq(vec4f a, vec4f b) {
	bool eq = true;
	for (int i=0; i<4; i++) {
		if (a[i] != b[i]) {
			eq = false;
		}
	}

	return eq;
}

static inline bool vec3f_eq(vec3f a, vec3f b)
{
	return vec4f_eq(
		(vec4f) {a.x, a.y, a.z, 0.0f},
		(vec4f) {b.x, b.y, b.z, 0.0f}
	);
}

#if 0

static inline void vec4f_toArray(float arr[4], vec4f v) //__attribute__((deprecated))
{
	arr[0] = v.x;
	arr[1] = v.y;
	arr[2] = v.z;
	arr[3] = v.w;
}
#endif

static inline float const * vec4f_to_ptr(vec4f const *v)
{
	union converter {
		vec4f const *v;
		float const *ptr;
	};
	union converter conv = {.v=v};
	return conv.ptr;
}

#endif
