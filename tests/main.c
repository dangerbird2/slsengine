#include <glib.h>
#include "window-test.h"
#include "math-tests.h"

int main(int argc, char *argv[]) {

    g_test_init(&argc, &argv, NULL);


    run_math_tests();
    //run_window_tests();
    run_component_tests();

    return g_test_run();
}
