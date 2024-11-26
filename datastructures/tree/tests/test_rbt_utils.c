#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_rbt_utils() {
    int is_test_all = 0;

    Node *root = NULL;
    char *issue = NULL;

    if (is_test_all) {
        // tree is empty
        int status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 1);

        // root is RED
        root = create_node(1, RED);
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 0);
        root = NULL;

        size_t number_nodes = 6;
        size_t number_trees = 1;
        int is_random = 0;

        TreeDebug *tree_debug = initiate_tree_debug();
        tree_debug =
            check_inserts_in_multiple_trees(&tree_debug, number_nodes, number_trees, is_random);
        CU_ASSERT(tree_debug->n_failed_rbt == 0);
        

        // check root node
        // check number of blacks from root
        // same number of blacks
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 1);

        // check number of blacks from root
        // different number of blacks
        root->right->color = RED;
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 0);

        // check red-red condition
        // double read
        root->right->color = BLACK;
        root->left->color = RED;
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 0);
        free_tree(root);

        // check all nodes
        // rb tree abides by the rules
        root = NULL;
        number_nodes = 10;
        number_trees = 1;
        is_random = 0;
        free(tree_debug);
        tree_debug =
            check_inserts_in_multiple_trees(&tree_debug, number_nodes, number_trees, is_random);
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 1);

        // check all nodes
        // rb tree violates rules: different number of black nodes
        root->left->right->right->color = BLACK;
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 0);

        // check all nodes
        // rb tree violates rules: parent is red - child is red
        root->left->right->right->color = RED;
        root->right->color = RED;
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 0);

        // check all nodes
        // rb tree violates rules: parent is red - child is red in two places
        root->left->right->right->color = RED;
        root->right->color = RED;
        root->left->left->color = RED;
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 0);

        // bst violation
        // left child is greater than parent
        root->left->key = 10;
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 0);

        // bst violation
        // right child is less than parent
        root->left->key = -2;
        root->right->key = -10;
        root->right->color = BLACK;
        root->left->left->color = BLACK;
        status = is_rb_tree(root, &issue);
        CU_ASSERT(status == 0);
        free_tree(root);
        free_tree_debug(tree_debug);
    }

    // random numbers are enabled
    size_t number_nodes = 30;
    size_t number_trees = 100;
    int is_random = 1;
    TreeDebug *tree_debug = initiate_tree_debug();
    tree_debug =
        check_inserts_in_multiple_trees(&tree_debug, number_nodes, number_trees, is_random);

    // create last tree from tree_debug array of random numbers
    root = NULL;
    for (size_t i = 0; i < number_nodes; i++) {
        insert_rbt(&root, tree_debug->arr_tree_data[i]);
    }

    CU_ASSERT(tree_debug->n_failed_rbt == 0);

    printf("\nIt created %zu trees with %zu nodes each, and failed %d times\n",
           number_trees,
           number_nodes,
           tree_debug->n_failed_rbt);

    printf("\nlast array of random numbers\n");
    for (size_t i = 0; i < number_nodes; i++) {
        printf("%d ", tree_debug->arr_tree_data[i]);
    }
    printf("\n");

    printf("%s", tree_debug->issue);

    tree_to_dot(tree_debug->tree_root);

    free_tree(root);
    free_tree_debug(tree_debug);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of test_rbt_utils()", test_rbt_utils);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
