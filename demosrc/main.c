#include "../src/slsengine.h"
#include "stdio.h"

#include <assert.h>

SLbool demo(int *argc, char const **argv[])
{
	slsGlWindow *window = NULL;
	window = slsGlWindow_create("demo", NULL);
	g_return_val_if_fail(window != NULL, false);

	if (window->run != NULL){
		window->run(window, NULL);
	}

	window->dtor(window);
	return true;
}

int main(int argc, char const *argv[])
{
	assert(init_Sls());
	atexit(quit_Sls);

	assert(demo(&argc, &argv));
	return 0;
}