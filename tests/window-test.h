#ifndef __SLS_WINDOW_TEST_H__
#define __SLS_WINDOW_TEST_H__

#include "../src/slsengine.h"


typedef struct {
    slsWindow *window;
} WindowFix;

void run_window_tests();

void window_fix_setup(WindowFix *fix, gconstpointer data);
void window_fix_teardown(WindowFix *fix, gconstpointer data);

void window_test_a(WindowFix *fix, gconstpointer data);
void window_content_test(WindowFix *fix, gconstpointer data);

#endif
