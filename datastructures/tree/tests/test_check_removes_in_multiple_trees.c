#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_check_removes_in_multiple_trees() {
    int is_many_trees = 1;

    if (is_many_trees) {
        TreeDebug *tree_debug = initiate_tree_debug();
        size_t number_nodes = 1000;
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

    } else {
        /* Node *root = NULL; */
        /* size_t size = 24; */
        /* int nodes[] = {4,  -16, 18, -23, -2, 13, 20, -25, -21, -10, 1, 9, */
        /*                15, 19,  21, -14, -7, -1, 3,  7,   11,  0,   2, 8}; */
        /* for (size_t i = 0; i < size; i++) { */
        /*     insert_rbt(&root, nodes[i]); */
        /* } */
        /* /1* remove_rbt(&root, -21); *1/ */

        // raversal level order
        /* level = 0, ids = 0, color = 0, data = -3 */
        /* level = 1, ids = 1, color = 0, data = -17 */
        /* level = 1, ids = 2, color = 0, data = 8 */

        /* level = 2, ids = 3, color = 0, data = -21 */
        /* level = 2, ids = 4, color = 0, data = -11 */
        /* level = 2, ids = 5, color = 0, data = 6 */
        /* level = 2, ids = 6, color = 1, data = 15 */

        /* level = 3, ids = 7, color = 0, data = -25 */
        /* level = 3, ids = 8, color = 0, data = -19 */
        /* level = 3, ids = 9, color = 0, data = -12 */
        /* level = 3, ids = 10, color = 0, data = -10 */
        /* level = 3, ids = 11, color = 0, data = 3 */
        /* level = 3, ids = 12, color = 0, data = 7 */
        /* level = 3, ids = 13, color = 0, data = 13 */
        /* level = 3, ids = 14, color = 0, data = 19 */

        /* level = 4, ids = 15, color = 1, data = -16 */
        /* level = 4, ids = 16, color = 1, data = -5 */
        /* level = 4, ids = 17, color = 0, data = 12 */
        /* level = 4, ids = 18, color = 0, data = 14 */
        /* level = 4, ids = 19, color = 0, data = 17 */
        /* level = 4, ids = 20, color = 0, data = 22 */
        /* level = 4, ids = 21, color = 1, data = 18 */
        /* level = 4, ids = 22, color = 1, data = 25 */

        // Level 0 (root)
        Node *root = create_node(-8, BLACK);

        // Level 1
        root->left = create_node(-18, BLACK);
        root->right = create_node(-3, BLACK);

        // Level 2
        root->left->left = create_node(-22, BLACK);
        root->left->right = create_node(-13, BLACK);
        root->right->left = create_node(-6, BLACK);
        root->right->right = create_node(14, RED);

        // Level 3 (left subtree)
        root->left->left->left = create_node(-25, BLACK);
        root->left->left->right = create_node(-21, BLACK);
        root->left->right->left = create_node(-15, BLACK);
        root->left->right->right = create_node(-9, BLACK);

        // Level 3 (right subtree)
        root->right->left->left = create_node(-7, BLACK);
        root->right->left->right = create_node(-4, BLACK);
        root->right->right->left = create_node(0, BLACK);
        root->right->right->right = create_node(18, BLACK);

        // Level 4 (left subtree)
        root->right->right->left->left = create_node(-1, BLACK);
        root->right->right->left->right = create_node(6, BLACK);

        // Level 4 (right subtree)
        root->right->right->right->left = create_node(15, BLACK);
        root->right->right->right->right = create_node(23, RED);

        // Level 5 (rightmost subtree)
        root->right->right->right->right->left = create_node(19, BLACK);
        root->right->right->right->right->right = create_node(24, BLACK);

        traverse_level_order(root);
        remove_rbt(&root, -4);
        char *issue = malloc(100);
        is_rb_tree(root, &issue);

        tree_to_dot(root);
        free_tree(root);
        free(issue);
    }
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
