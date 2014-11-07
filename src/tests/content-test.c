#include <slsengine/slsengine.h>
#include <glib.h>

#include <SDL2/SDL.h>

typedef struct {
	slsContentManager *mgr;
	slsGlWindow *window;
} contentFix;

/**
 * forward declarations
 */
void content_teardown(contentFix *fix, gconstpointer data);
void content_setup(contentFix *fix, gconstpointer data);


void content_setup(contentFix *fix, gconstpointer data)
{
	fix->window = slsGlWindow_create("test", NULL);
	fix->mgr = slsContentManager_alloc();
    slsMsg(fix->mgr, init);
}
/**
 * test implementation
 */

void content_teardown(contentFix *fix, gconstpointer data)
{
	slsMsg(fix->window, dtor);
    //slsMsg(fix->mgr, dtor);
}

void content_test(contentFix *fix, gconstpointer data)
{
	g_assert(!fix->mgr->content);
}

void content_texture_test(contentFix *fix, gconstpointer data)
{
	char const *key = "tex";
	char const *path = "content/tileset.png";
	SDL_Texture *tex = slsContentManager_load_texture(fix->mgr, fix->window->super->renderer, key, path);
	// assert tex != NULL
	g_assert(tex);
}

void content_shader_test(contentFix *fix, gconstpointer data)
{
	char const *key = "shader";
	char const *vs = "content/s.vert";
	char const *fs = "content/s.frag";

	slsShader *shad = slsContentManager_load_shader(fix->mgr, key, vs, fs);
	

	g_assert(shad);
	
}

void run_content_tests()
{
#if 0
	g_test_add(
		"/Content/content_test",
		contentFix,
		NULL,
		content_setup,
		content_test,
		content_teardown
	);

	g_test_add(
		"/Content/texture_test",
		contentFix,
		NULL,
		content_setup,
		content_texture_test,
		content_teardown
	);

	g_test_add(
		"/Content/shader_test",
		contentFix,
		NULL,
		content_setup,
		content_shader_test,
		content_teardown
	);
#endif
}