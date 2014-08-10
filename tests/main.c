#include <glib.h>
#include "math-tests.h"
#include "component-test.h"
#include "content-test.h"

int main(int argc, char *argv[]) {

    g_test_init(&argc, &argv, NULL);
    

    run_math_tests();
    
    run_component_tests();

    run_content_tests();

    return g_test_run();
}
