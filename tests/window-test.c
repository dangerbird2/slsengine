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
    slsSprite *sprite = self->data;

    SDL_Rect dest = {0, 0, sprite->src_rect.w, sprite->src_rect.h};
    g_assert(sprite->texture != NULL);

    SDL_SetRenderDrawColor(
        self->renderer, self->clear_color.r, self->clear_color.g,
        self->clear_color.b, self->clear_color.a);
    SDL_RenderClear(self->renderer);

    SDL_RenderCopy(self->renderer, sprite->texture, NULL, NULL);

    SDL_RenderPresent(self->renderer);
};

void window_content_test(WindowFix *fix, gconstpointer data)
{
    SDL_Texture *tex = NULL;
    slsSprite *sprite = NULL;

    slsContentManager *mgr = slsContentManager_create();

    slsContentManager_load_texture(mgr, fix->window->renderer,
        "tilemap", "content/tileset.png");
    SDL_Rect src_rect = {0, 0, 16, 16};


    tex = g_hash_table_lookup(mgr->textures, "tilemap");
    sprite = slsSprite_create(tex, 10, 10, &src_rect);

    g_assert(tex != NULL);
    g_assert(sprite != NULL);

    fix->window->render = window_custom_render;
    fix->window->data = sprite;
    fix->window->run(fix->window, NULL);

    slsContentManager_destroy(mgr);
}
