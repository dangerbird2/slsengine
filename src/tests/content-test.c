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
void content_teardown(contentFix *fix, void const *data);
void content_setup(contentFix *fix, void const *data);


void content_setup(contentFix *fix, void const *data)
{
	fix->window = slsGlWindow_create("test", NULL);
	fix->mgr = slsContentManager_new(NULL);
}
/**
 * test implementation
 */

void content_teardown(contentFix *fix, void const *data)
{
	slsMsg(fix->window, dtor);
	if (fix->mgr) {
    	slsMsg(fix->mgr, dtor);
	}
}

void content_path_test(contentFix *fix, void const *data)
{
	g_assert(fix->mgr->assets_dir);
	log_info("\n%s", fix->mgr->assets_dir->str);
}

void content_test(contentFix *fix, void const *data)
{
	g_assert(fix->mgr->content);
}

void content_texture_test(contentFix *fix, void const *data)
{
	char const *key = "tex";
	char const *path = "tileset.png";
	SDL_Texture *tex = slsContentManager_load_texture(fix->mgr, fix->window->super->renderer, key, path);
	// assert tex != NULL
	g_assert(tex);
}

void content_shader_test(contentFix *fix, void const *data)
{
	char const *key = "shader";
	char const *vs = "s.vert";
	char const *fs = "s.frag";

	slsShader *shad = slsContentManager_load_shader(fix->mgr, key, vs, fs);
	

	g_assert(shad);
	
}

void run_content_tests()
{
	struct tup {
		char const *name;
		void (*fn)(contentFix*, void const*);
	};

	struct tup tests[] = {
		{"/Content/content_test", content_test},
		{"/Content/texture_test", content_texture_test},
		{"/Content/shader_test", content_shader_test},
		{"/Content/path_test", content_path_test}
	};
	int len = sizeof(tests)/sizeof(struct tup);

	for (int i=0; i<len; ++i) {
		g_test_add(
			tests[i].name,
			contentFix,
			NULL,
			content_setup,
			tests[i].fn,
			content_teardown
		);
	}

}