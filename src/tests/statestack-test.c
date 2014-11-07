#include <glib.h>
#include <slsengine/slsengine.h>

typedef struct stateFix {
    slsStateNode *node;
    slsStateStack *stack;
}stateFix;

void run_statestack_tests();
void statestack_test_setup(stateFix *fix, void const *data);
void statestack_test_teardown(stateFix *fix, void const *data);

void node_test_A()
{
    slsStateNode *node = NULL;
    node = slsStateNode_new(NULL);
    g_assert(node);

    slsMsg(node, dtor);
}


void run_statestack_tests()
{
    g_test_add_func("/States/node_test_a", node_test_A);
}