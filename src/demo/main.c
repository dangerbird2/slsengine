#include <slsengine/slsengine.h>

int main(int argc, char const *argv[])
{
	if (!init_Sls()) {
		return -1;
	}
	atexit(quit_Sls);

	slsGameWindow* window slsGameWindowAF = slsGameWindow_alloc();
    slsMsg(window, initWithSize, "window", 600, 400);
	if (!window) {return -1;}

    slsMsg(window, run);

	return 0;
}