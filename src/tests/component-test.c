#include <glib.h>
#include <slsengine/slsengine.h>

typedef struct {
    slsWindow *window;
    slsEntityTable *entities;

} CompFix;

void run_component_tests();
void component_fix_setup(CompFix *fix, gconstpointer data);
void component_fix_teardown(CompFix *fix, gconstpointer data);
void component_test_a(CompFix *fix, gconstpointer data);

void run_component_tests()
{
    g_test_add("/Component/test_a", CompFix, NULL,
        component_fix_setup, component_test_a, component_fix_teardown
    );
}

void component_fix_setup(CompFix *fix, gconstpointer data){ }
void component_fix_teardown(CompFix *fix, gconstpointer data){ }

void component_test_a(CompFix *fix, gconstpointer data){ }
