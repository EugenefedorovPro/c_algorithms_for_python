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
    size_t cycles = 1;

    while (cycles > 0) {
        printf("\ncycles = %zu\n", cycles);
        size_t size = 25;
        srand(time(NULL));
        int *arr_rand_numbers = rand_numbers(size);
        create_rand_rbt(&root, &arr_rand_numbers, size);

        traverse_level_order(root);

        size_t n_node_to_rm = 25;
        remove_rand_nodes_from_rbt(&root, &arr_rand_numbers, size, n_node_to_rm);

        char *issue = NULL;
        int result = is_rb_tree(root, &issue);
        CU_ASSERT(result == 1);
        cycles--;
    }

    /* traverse_level_order(root); */

    /* size_t size_ins = 5; */
    /* int arr_nodes[] = {5, -6, 14, -2, 13}; */
    /* for (size_t i = 0; i < size_ins; i++) { */
    /*     insert_rbt(&root, arr_nodes[i]); */
    /* } */

    /* remove_rbt(&root, -6); */

    /* remove_rbt(&root, 0); */
    /* remove_rbt(&root, 7); */
    /* remove_rbt(&root, 4); */
    /* remove_rbt(&root, 9); */
    /* remove_rbt(&root, 2); */
    /* remove_rbt(&root, -10); */

    /* remove_rbt(&root, -3); */

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
