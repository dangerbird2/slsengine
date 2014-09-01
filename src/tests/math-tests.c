#include <slsengine/slsengine.h>
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

/**
 * @brief tests whether slsMat4f_identity produces an identity matrix
 * @details [long description]
 * 
 * @param m [description]
 */
void mat4f_identity()
{
    slsMat4f m = slsMat4f_identity();
    for (int i=0; i<4; i++) {
        g_assert(m.mat[i][i] == 1.0);
    }
}

/**
 * @brief assert that M1identity * M2identity = identity
 * @details [long description]
 * 
 * @param vec4f_eq_test [description]
 */
void mat_mul_identity()
{
    slsMat4f m1 = slsMat4f_identity();
    slsMat4f m2 = m1;
    slsMat4f m3 = slsMat4f_mul(&m1, &m2);

    if (!slsMat4f_eq(&m1, &m3)) {
        log_err("\n\nm1 * m2 does not equal identity!\n\n");
        printf("\nm1:\n"); slsMat4f_print(&m1);
        printf("\nm2:\n"); slsMat4f_print(&m2);
        printf("\nm1*m2:\n"); slsMat4f_print(&m3);
        g_test_fail();
    }
}

void mat_vec_mul()
{
    slsMat4f m1 = slsMat4f_identity();
    vec4f v1 = {1.0, 2.4, 0.1, 0.8};
    vec4f v2 = slsMat4f_mul_vec4f(&m1, v1);

    if (!vec4f_eq(v1, v2)) {
        log_err("\n\nm1*v1 != v1");
        print_vec4_short(v1);
        print_vec4_short(v2);
        g_test_fail();
    }

}

void vec4f_eq_test()
{
    vec4f a = {0.0f, 1.0f, 1.0f, 0.0f};
    vec4f b = {1.0f, 1.0f, 1.0f, 0.0f};
    vec4f c = {0.0f, 1.0f, 1.0f, 0.0f};

    g_assert(!vec4f_eq(a, b));
    g_assert(vec4f_eq(a, c));
}

void vec4f_dot_test()
{
    vec4f a = {2.f, 1.f, 3.f, 1.f};
    vec4f b = {3.f, 4.f, 2.f, 1.f};
    float ans = 2.f*3.f + 1.f*4.f + 3.f*2.f + 1.f*1.f;
    g_assert(ans == vec4f_dot(a, b));

}

void run_math_tests()
{
    g_test_add_func("/Math/vec2i/overflow", vec2i_test_overflow);
    g_test_add_func("/Math/vec4f/eq", vec4f_eq_test);


    g_test_add("/Math/vec2i/add",
        vec2iFix, NULL, vec2i_setup,
        vec2i_test_add, vec2i_teardown);
    g_test_add_func("/Math/vec4f/dot", vec4f_dot_test);
    g_test_add_func("/Math/mat4f/identity", mat4f_identity);
    g_test_add_func("/Math/mat4f/mul", mat_mul_identity);
    g_test_add_func("/Math/mat4f/mulvec4", mat_vec_mul);
}
