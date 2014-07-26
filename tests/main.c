#include <glib.h>
#include "window-test.h"


int main(int argc, char *argv[]) {

	g_test_init(&argc, &argv, NULL);
	
	run_window_tests();

	return g_test_run();
}
