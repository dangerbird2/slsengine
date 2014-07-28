#include "window-test.h"
#include <glib.h>
#include "../src/slsengine.h"
#include <stdio.h>
#include <Block.h>

void run_window_tests()
{
    g_test_add("/Window/content_test", WindowFix, NULL,
        window_fix_setup, window_content_test, window_fix_teardown
    );
    #if 0
    g_test_add("/Window/test_a", WindowFix, NULL,
        window_fix_setup, window_test_a, window_fix_teardown
    );
    #endif
}

void window_fix_setup(WindowFix *fix, gconstpointer data)
{
    g_assert(init_Sls());
    fix->window = slsWindow_new_gameWindow();
}
void window_fix_teardown(WindowFix *fix, gconstpointer data)
{
    slsWindow_free_gameWindow(fix->window);
    quit_Sls();
}

void window_test_a(WindowFix *fix, gconstpointer data)
{
    g_assert(fix->window != NULL);
    fix->window->run(fix->window, (void *) data);
}

void window_custom_render(slsWindow *self, void *data)
{
    SDL_Texture *tex = self->data;
    SDL_Rect dest = {0, 0, 0, 0};
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    SDL_SetRenderDrawColor(
        self->renderer, self->clear_color.r, self->clear_color.g,
        self->clear_color.b, self->clear_color.a);
    SDL_RenderClear(self->renderer);

    SDL_RenderCopy(self->renderer,  tex, NULL, &dest);

    SDL_RenderPresent(self->renderer);
};

void window_content_test(WindowFix *fix, gconstpointer data)
{
    SDL_Texture *tex = NULL;

    slsContentManager *mgr = slsContentManager_create();

    slsContentManager_load_texture(mgr, fix->window->renderer,
        "tilemap", "content/tileset.png");
    tex = g_hash_table_lookup(mgr->textures, "tilemap");

    g_assert(tex != NULL);

    fix->window->render = window_custom_render;
    fix->window->data = tex;
    fix->window->run(fix->window, NULL);

    slsContentManager_destroy(mgr);
}
