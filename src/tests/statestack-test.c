#include <glib.h>
#include <slsengine/slsengine.h>

typedef struct stateFix {
    slsStateNode *node;
    slsStateStack *stack;
}stateFix;

void run_statestack_tests();
void statestack_test_setup(stateFix *fix, void const *data);
void statestack_test_teardown(stateFix *fix, void const *data);



void statestack_test_setup(stateFix *fix, void const *data)
{
	fix->stack = slsStateStack_new(NULL);
	slsStateStack *stack = fix->stack;

	size_t n = (size_t) data;
	for (int i=0; i<n; ++i) {
		slsMsg(stack, push, slsStateNode_new());
	}
}
void statestack_test_teardown(stateFix *fix, void const *data)
{
	if (fix->stack && fix->stack->dtor) {
		slsMsg(fix->stack, dtor);
	}
}

void node_test_A()
{
    slsStateNode *node = NULL;
    node = slsStateNode_new(NULL);
    g_assert(node);

    slsMsg(node, dtor);
}
/**
 * @brief tests stack push method, and that pushing the stack updates
 * the stack length counter
 * @details creates a nuber of nodes, and ensures that stack can traverse it
 */
void stack_test_count(stateFix *fix, void const *data)
{
	slsStateStack *stack = fix->stack;
	size_t n = (size_t) data;

	g_assert(stack->count == n);
	slsStateNode *node = stack->top;
	for (int i=0; i< stack->count-1; i++) {
		g_assert(node->next);

		// push method should make node's host the stack
		g_assert(node->host == stack);

		// ensure that node->next isn't null
		node = node->next;
	}
	// at this point, node->next should be NULL, as we have reached the end count
	g_assert(!node->next);
}

/**
 * @brief tests stack pop method
 * @details 
 */
void stack_test_pop(stateFix *fix, void const *data)
{
	slsStateStack *stack = fix->stack;
	size_t n = (size_t) data;

	for (int i=0; i<n/10; i++) {
		slsStateNode *node = slsMsg(stack, pop);

		// poping the node should erase its host pointer
		g_assert(node->host == NULL);

		slsMsg(node, dtor);
		node = NULL;
	}
	g_assert(stack->count == n - (n/10));
	//debug("%d", stack->count);
}


void run_statestack_tests()
{
	const size_t n = 1000;
    g_test_add_func("/States/node_test_a", node_test_A);

    struct testTup {
    	char const *name;
    	void (* const fn)(stateFix *, void const*);
    };

    struct testTup const tests[] = {
    	{"/States/stack_test_count", stack_test_count},
    	{"/States/stack_test_pop", stack_test_pop}
    };
    const int len = sizeof(tests)/sizeof(struct testTup);
    for (int i=0; i< len; i++) {
    	g_test_add(
	    	tests[i].name,
	    	stateFix,
	    	(const void*)n,
	    	statestack_test_setup,
	    	tests[i].fn,
	    	statestack_test_teardown
		);
	}
}