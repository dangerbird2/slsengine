#include "../src/slsengine.h"
#include <stdlib.h>
#include <glib.h>

typedef struct {
    vec2i a;
    vec2i b;
} vec2iFix;

void run_math_tests();

void vec2i_test_overflow();

void vec2i_setup(vec2iFix *fix, gconstpointer data);
void vec2i_teardown(vec2iFix *fix, gconstpointer data);
void vec2i_test_add(vec2iFix *fix, gconstpointer data);


void vec2i_setup(vec2iFix *fix, gconstpointer data)
{
    fix->a = (vec2i) {g_test_rand_int(), g_test_rand_int()};
    fix->b = (vec2i) {g_test_rand_int(), g_test_rand_int()};
}
void vec2i_teardown(vec2iFix *fix, gconstpointer data)
{}

void vec2i_test_add(vec2iFix *fix, gconstpointer data)
{
    vec2i c = fix->a + fix->b;
    g_assert((c.x == fix->a.x + fix->b.x));
    g_assert((c.y == fix->a.y + fix->b.y));
}



void vec2i_test_overflow()
{
    // this test ensures vector types have same range as normal types
    vec2i a = {0, 0};
    int b = 0;

    int incr = 100000;
    while(b >= 0) {


        a.x += incr;
        b += incr;
        g_assert(a.x == b);
    }
}


void run_math_tests()
{
    g_test_add_func("/Math/vec2i/overflow", vec2i_test_overflow);
    g_test_add("/Math/vec2i/add",
        vec2iFix, NULL, vec2i_setup,
        vec2i_test_add, vec2i_teardown);
}
