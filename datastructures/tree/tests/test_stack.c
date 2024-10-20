#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_stack() {
    Stack *stack = NULL;

    Node *node1 = create_node(10, RED);
    s_append(&stack, node1);

    Node *node2 = create_node(20, RED);
    s_append(&stack, node2);

    Node *node3 = create_node(30, RED);
    s_append(&stack, node3);

    printf("\nstack data 1 = %d\n", stack->node->data);
    printf("\nstack data 2 = %d\n", stack->next->node->data);

    Node *top_node = s_pop(&stack);
    printf("\ntop_node = %d\n", top_node->data);

    Node *next_node = s_pop(&stack);
    printf("\nnext_node = %d\n", next_node->data);

    Node *last_node = s_pop(&stack);
    printf("\nlast_node = %d\n", last_node->data);

    Node *empty_node = s_pop(&stack);


}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of stack()", test_stack);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
