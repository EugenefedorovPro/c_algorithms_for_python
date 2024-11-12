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
    size_t size = get_stack_size(&stack);
    CU_ASSERT(size == 1);

    Node *node2 = create_node(20, RED);
    s_append(&stack, node2);

    Node *node3 = create_node(30, RED);
    s_append(&stack, node3);

    Node *peeked_node = s_peek(&stack);
    CU_ASSERT(peeked_node->data == 30);
    Node *peeked_node2 = s_peek(&stack);
    CU_ASSERT(peeked_node2->data == 30);

    print_all_stack(&stack);


    size_t size1 = get_stack_size(&stack);
    printf("\nstack size1 = %zu\n", size1);
    CU_ASSERT(size1 == 3);
    

    Node *top_node = s_pop(&stack);
    printf("\ntop_node = %d\n", top_node->data);
    CU_ASSERT(top_node->data == 30);

    Node *next_node = s_pop(&stack);
    printf("\nnext_node = %d\n", next_node->data);
    CU_ASSERT(next_node->data == 20);

    Node *last_node = s_pop(&stack);
    printf("\nlast_node = %d\n", last_node->data);
    CU_ASSERT(last_node->data == 10);

    Node *empty_node = s_pop(&stack);
    CU_ASSERT(empty_node == NULL);
    size_t size2 = get_stack_size(&stack);
    CU_ASSERT(size2 == 0);

    // free_stack() test
    Node *node4 = create_node(10, RED);
    s_append(&stack, node4);
    Node *node5 = create_node(20, RED);
    s_append(&stack, node5);

    CU_ASSERT(get_stack_size(&stack) == 2);
    free_stack(&stack);
    CU_ASSERT(stack == NULL);

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
