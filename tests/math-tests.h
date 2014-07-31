#ifndef __SLS_MATH_TESTS_H__
#define __SLS_MATH_TESTS_H__

#include <glib.h>
#include "../src/slsengine.h"

typedef struct {
    vec2i a;
    vec2i b;
} vec2iFix;

void run_math_tests();

void vec2i_test_overflow();

void vec2i_setup(vec2iFix *fix, gconstpointer data);
void vec2i_teardown(vec2iFix *fix, gconstpointer data);
void vec2i_test_add(vec2iFix *fix, gconstpointer data);

#endif
