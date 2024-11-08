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

    if (is_test_all) {
        // tree is empty
        int status = is_rb_tree(root);
        CU_ASSERT(status == 1);

        // root is RED
        root = create_node(1, RED);
        status = is_rb_tree(root);
        CU_ASSERT(status == 0);
        root = NULL;

        size_t number_nodes = 6;
        size_t number_trees = 1;
        int is_random = 0;

        int n_fails = check_inserts_in_multiple_trees(&root, number_nodes, number_trees, is_random);
        CU_ASSERT(n_fails == 0);

        // check root node
        // check number of blacks from root
        // same number of blacks
        status = is_rb_tree(root);
        CU_ASSERT(status == 1);

        // check number of blacks from root
        // different number of blacks
        root->right->color = RED;
        status = is_rb_tree(root);
        CU_ASSERT(status == 0);

        // check red-red condition
        // double read
        root->right->color = BLACK;
        root->left->color = RED;
        status = is_rb_tree(root);
        CU_ASSERT(status == 0);
        free_tree(root);

        // check all nodes
        // rb tree abides by the rules
        root = NULL;
        number_nodes = 10;
        number_trees = 1;
        is_random = 0;
        n_fails = check_inserts_in_multiple_trees(&root, number_nodes, number_trees, is_random);
        status = is_rb_tree(root);
        CU_ASSERT(status == 1);

        // check all nodes
        // rb tree violates rules: different number of black nodes
        root->left->right->right->color = BLACK;
        status = is_rb_tree(root);
        CU_ASSERT(status == 0);

        // check all nodes
        // rb tree violates rules: parent is red - child is red
        root->left->right->right->color = RED;
        root->right->color = RED;
        status = is_rb_tree(root);
        CU_ASSERT(status == 0);

        // check all nodes
        // rb tree violates rules: parent is red - child is red in two places
        root->left->right->right->color = RED;
        root->right->color = RED;
        root->left->left->color = RED;
        status = is_rb_tree(root);
        CU_ASSERT(status == 0);

        // bst violation
        // left child is greater than parent
        root->left->data = 10;
        status = is_rb_tree(root);
        CU_ASSERT(status == 0);

        // bst violation
        // right child is less than parent
        root->left->data = -2;
        root->right->data = -10;
        root->right->color = BLACK;
        root->left->left->color = BLACK;
        status = is_rb_tree(root);
        CU_ASSERT(status == 0);
        free_tree(root);
    }

    // random numbers are enabled
    root = NULL;
    size_t number_nodes = 20;
    size_t number_trees = 1000;
    int is_random = 1;
    int n_fails = check_inserts_in_multiple_trees(&root, number_nodes, number_trees, is_random);
    CU_ASSERT(n_fails == 0);
    printf("It created %zu trees with %zu nodes each, and failed %d times\n",
           number_trees,
           number_nodes,
           n_fails);

    tree_to_dot(root);

    free(root);
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
