#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_insert_rbt() {
    // creates multiple trees with random nodes and print the last tree for visual control
    srand(time(NULL));
    Node *root = NULL;

    /* insert_rbt(&root, 50); */
    /* insert_rbt(&root, -30); */
    /* /1* insert_rbt(&root, -40); *1/ */

    size_t number_nodes = 31;
    size_t number_trees = 1;
    int is_random = 0;
    int n_fails = check_inserts_in_multiple_trees(&root, number_nodes, number_trees, is_random);
    CU_ASSERT(n_fails == 0);

    printf("\nNumber of fails = %d\n", n_fails);


    tree_to_dot(root);
    free(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of insert_rbt()", test_insert_rbt);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
