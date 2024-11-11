#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_remove_nodes_from_rbt() {
    Node *root = NULL;
    size_t size = 7;
    int *arr_rand_numbers = rand_numbers(size);
    create_rand_rbt(&root, &arr_rand_numbers, size);
    traverse_level_order(root);
    size_t n_node_to_rm = 3;
    remove_rand_nodes_from_rbt(&root, &arr_rand_numbers, size, n_node_to_rm);
    traverse_level_order(root);

    tree_to_dot(root);
    free_tree(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of remove_nodes_from_rbt()", test_remove_nodes_from_rbt);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
