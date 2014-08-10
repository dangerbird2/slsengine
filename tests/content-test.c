#include "content-test.h"
#include "../src/slsengine.h"
#include <glib.h>

#include <SDL2/SDL.h>

typedef struct {
	slsContentManager *mgr;
	slsGlWindow *window;
} contentFix;

void content_setup(contentFix *fix, gconstpointer data)
{
	fix->window = slsGlWindow_create("test", NULL);
	fix->mgr = slsContentManager_create();
}

void content_teardown(contentFix *fix, gconstpointer data)
{
	slsContentManager_destroy(fix->mgr);
	fix->window->dtor(fix->window);
}

void content_test(contentFix *fix, gconstpointer data)
{
	g_assert(fix->mgr->textures);
	g_assert(fix->mgr->shaders);
}

void content_texture_test(contentFix *fix, gconstpointer data)
{
	char const *key = "tex";
	char const *path = "content/tileset.png";
	SDL_Texture *tex = slsContentManager_load_texture(fix->mgr, fix->window->super->renderer, key, path);
	// assert tex != NULL
	g_assert(tex);

	// find tex in mgr's hash table
	SDL_Texture *tex2 = g_hash_table_lookup(fix->mgr->textures, key);
	g_assert(tex == tex2);
}

void run_content_tests()
{
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
}