#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_insert_rbt() {
    int is_test_all = 0;

    if (is_test_all) {
        // creates multiple trees with random nodes and print the last tree for visual control
        srand(time(NULL));

        /* insert_rbt(&root, 50); */
        /* insert_rbt(&root, -30); */
        /* /1* insert_rbt(&root, -40); *1/ */

        size_t number_nodes = 31;
        size_t number_trees = 1;
        int is_random = 0;
        TreeDebug *tree_debug = initiate_tree_debug();
        tree_debug =
            check_inserts_in_multiple_trees(&tree_debug, number_nodes, number_trees, is_random);
        CU_ASSERT(tree_debug->n_failed_rbt == 0);

        printf("\nNumber of fails = %d\n", tree_debug->n_failed_rbt);

        tree_to_dot(tree_debug->tree_root);
        free_tree(tree_debug->tree_root);
        free_tree_debug(tree_debug);
    }

    Node *root = NULL;
    insert_rbt(&root, -6);
    insert_rbt(&root, -3);
    insert_rbt(&root, -4);
    insert_rbt(&root, 5);
    insert_rbt(&root, 6);
    insert_rbt(&root, 4);
    insert_rbt(&root, -5);
    insert_rbt(&root, 5);
    insert_rbt(&root, -6);
    insert_rbt(&root, 3);
    /* insert_rbt(&root, 2); */

    char *issue = NULL;
    CU_ASSERT(is_rb_tree(root, &issue) == 1);
    tree_to_dot(root);
    free_tree(root);
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
