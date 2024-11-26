#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_insert_rbt() {
    int is_test_all = 1;

    if (is_test_all) {
        // creates multiple trees with random nodes and print the last tree for visual control
        srand(time(NULL));

        /* insert_rbt(&root, 50); */
        /* insert_rbt(&root, -30); */
        /* /1* insert_rbt(&root, -40); *1/ */

        size_t number_nodes = 100;
        size_t number_trees = 100;
        int is_random = 0;
        TreeDebug *tree_debug = initiate_tree_debug();
        tree_debug =
            check_inserts_in_multiple_trees(&tree_debug, number_nodes, number_trees, is_random);
        CU_ASSERT(tree_debug->n_failed_rbt == 0);

        printf("\nnumber of generated trees = %zu of %zu nodes, with %d fails", number_trees, number_nodes, tree_debug->n_failed_rbt);
        printf("\nArr of random numbers of the last rb tree ");
        for (size_t i = 0; i < number_nodes; i ++) {
            printf("%d ", tree_debug->arr_tree_data[i]);
        }
        printf("\n");
        printf("issue of the last failed rb tree: %s\n\n", tree_debug->issue ? tree_debug->issue : "No fails");

        tree_to_dot(tree_debug->tree_root);

        free_tree_debug(tree_debug);
    }

    /* Node *root = NULL; */
    /* insert_rbt(&root, -6, "empty"); */
    /* insert_rbt(&root, -3, "empty"); */
    /* insert_rbt(&root, -4, "empty"); */
    /* insert_rbt(&root, 5, "empty"); */
    /* insert_rbt(&root, 6, "empty"); */
    /* insert_rbt(&root, 4, "empty"); */
    /* insert_rbt(&root, -5, "empty"); */
    /* insert_rbt(&root, 5, "empty"); */
    /* insert_rbt(&root, -6, "empty"); */
    /* insert_rbt(&root, 3, "empty"); */
    /* insert_rbt(&root, 2, "empty"); */

    /* char *issue = NULL; */
    /* CU_ASSERT(is_rb_tree(root, &issue) == 1); */

    /* traverse_level_order(root); */

    /* tree_to_dot(root); */
    /* free_tree(root); */
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
