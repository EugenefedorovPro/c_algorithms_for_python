#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_check_removes_in_multiple_trees() {
    TreeDebug *tree_debug = initiate_tree_debug();
    size_t number_nodes = 30;
    size_t number_trees = 10;
    int is_random = 1;
    tree_debug =
        check_removes_in_multiple_trees(&tree_debug, number_nodes, number_trees, is_random);

    printf("\nissue = %s\n", tree_debug->issue);

    printf("\narray of last tree data: ");
    if (tree_debug->arr_tree_data) {
        for (size_t i = 0; i < number_nodes; i++) {
            printf("%d, ", tree_debug->arr_tree_data[i]);
        }
        printf("\n");
    } else {
        printf("\ntree_debug->arr_tree_data is empty\n");
    }

    printf("\nnumber of failed red black trees = %d\n", tree_debug->n_failed_rbt);

    printf("\nsize of removed numbers = %zu\n", tree_debug->size_of_removed_numbers);

    if (tree_debug->arr_of_removed_numbers) {
        printf("\narr of removed numbers: ");
        for (size_t i = 0; i < tree_debug->size_of_removed_numbers; i++) {
            printf("%d, ", tree_debug->arr_of_removed_numbers[i]);
        }
        printf("\n");
    }

    printf("\nnumber of trees created and checked = %zu\n", number_trees);
    
    tree_to_dot(tree_debug->tree_root);
    free_tree_debug(tree_debug);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite,
                "test of test_check_removes_in_multiple_trees()",
                test_check_removes_in_multiple_trees);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
