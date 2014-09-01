#include <glib.h>

extern void run_mesh_tests();
extern void run_content_tests();
extern void run_math_tests();
extern void run_component_tests();

int main(int argc, char *argv[])
{

    g_test_init(&argc, &argv, NULL);
    

    run_math_tests();
    
    run_component_tests();

    run_content_tests();
    run_mesh_tests();

    return g_test_run();
}
