#ifndef __SLS_COMPONENT_TEST_H__
#define __SLS_COMPONENT_TEST_H__

#include "../src/slsengine.h"


typedef struct {
    slsWindow *window;
    slsEntityTable *entities;

} CompFix;

void run_component_tests();

void component_fix_setup(CompFix *fix, gconstpointer data);
void component_fix_teardown(CompFix *fix, gconstpointer data);

void component_test_a(CompFix *fix, gconstpointer data);

#endif
