#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_remove_rbt() {
    int is_test_all = 0;

    /* // NO TREE BALANCING */
    /* // case 1 - check remove node in the left subtree */
    /* // case 1.1 - node to rm has two sub */
    /* // case 1.1.1 - left child of node_to_rm has two children */

    Node *root = NULL;

    /* size_t number_nodes = 31; */
    /* size_t number_trees = 1; */
    /* size_t count = 0; */
    /* int *arr_rand_numbers = rand_numbers(number_nodes); */
    /* int n_fails = check_inserts_in_multiple_trees(&root, &arr_rand_numbers, number_nodes,
     * number_trees, &count); */
    /* CU_ASSERT(n_fails == 0); */

    /*  // ************************* RB TREE BALANCE *1/ **************************** */

    char *issue = NULL;
    if (is_test_all) {
        // red leaf node
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 2);
        insert_rbt(&root, 9);
        insert_rbt(&root, 30);
        insert_rbt(&root, 25);
        insert_rbt(&root, 40);
        insert_rbt(&root, 38);
        remove_rbt(&root, 38);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->right->data == 30);
        CU_ASSERT(root->right->right->data == 40);
        CU_ASSERT(root->right->left->data == 25);
        CU_ASSERT(root->left->left->data == 2);
        CU_ASSERT(root->left->right->data == 9);
        CU_ASSERT(root->right->right->left == NULL);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB sibling's black and  DB's sibling's children are black (or null)
        // remove left sibling
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        root->right->color = RED;
        root->right->right->color = BLACK;
        root->right->left->color = BLACK;
        remove_rbt(&root, 15);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 30);
        CU_ASSERT(root->right->right->color == RED);
        CU_ASSERT(root->right->left == NULL);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB sibling's black and  DB's sibling's children are black (or null) and parent is red
        // remove right sibling
        // node_to_rm has right child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        insert_rbt(&root, 31);
        root->right->color = RED;
        root->right->right->color = BLACK;
        root->right->left->color = BLACK;
        remove_rbt(&root, 30);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 15);
        CU_ASSERT(root->right->left->color == RED);
        CU_ASSERT(root->right->right->data == 31);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB sibling's black and  DB's sibling's children are black (or null) and parent is red
        // remove right sibling
        // node_to_rm has right child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        insert_rbt(&root, 29);
        root->right->color = RED;
        root->right->right->color = BLACK;
        root->right->left->color = BLACK;
        remove_rbt(&root, 30);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 15);
        CU_ASSERT(root->right->left->color == RED);
        CU_ASSERT(root->right->right->data == 29);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB sibling's black and  DB's sibling's children are black (or null) and parent is red
        // remove right sibling
        // node_to_rm has two child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        insert_rbt(&root, 29);
        insert_rbt(&root, 31);
        root->right->color = RED;
        root->right->right->color = BLACK;
        root->right->left->color = BLACK;
        remove_rbt(&root, 30);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == RED);
        CU_ASSERT(root->right->left->data == 15);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->right->right->data == 31);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->right->left->data == 29);
        CU_ASSERT(root->right->right->left->color == RED);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB sibling's black and  DB's sibling's children are black (or null)
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        root->right->right->color = BLACK;
        root->right->left->color = BLACK;
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        remove_rbt(&root, 15);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == RED);
        CU_ASSERT(root->left->left->data == 1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 7);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 30);
        CU_ASSERT(root->right->right->color == RED);
        CU_ASSERT(root->right->left == NULL);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB's sibling is red
        // rm left node of a parent
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        insert_rbt(&root, 25);
        insert_rbt(&root, 40);
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        root->right->color = BLACK;
        root->right->right->color = RED;
        root->right->right->right->color = BLACK;
        root->right->right->left->color = BLACK;
        remove_rbt(&root, 15);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->left->left->data == 1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 7);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 30);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 40);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 20);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->right->left->right->data == 25);
        CU_ASSERT(root->right->left->right->color == RED);
        CU_ASSERT(root->right->left->left == NULL);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB's sibling is red
        // rm left node of a parent
        // node_to_del has right child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        insert_rbt(&root, 25);
        insert_rbt(&root, 40);
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        root->right->color = BLACK;
        root->right->right->color = RED;
        root->right->right->right->color = BLACK;
        root->right->right->left->color = BLACK;
        insert_rbt(&root, 16);
        /* insert_rbt(&root, 14); */  // node_to_del has left sibling
        remove_rbt(&root, 15);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->left->left->data == 1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 7);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 30);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 40);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 20);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->right->left->right->data == 25);
        CU_ASSERT(root->right->left->right->color == RED);
        CU_ASSERT(root->right->left->left->data == 16);
        CU_ASSERT(root->right->left->left->color == RED);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB's sibling is red
        // rm left node of a parent
        // node_to_del has left child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        insert_rbt(&root, 25);
        insert_rbt(&root, 40);
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        root->right->color = BLACK;
        root->right->right->color = RED;
        root->right->right->right->color = BLACK;
        root->right->right->left->color = BLACK;
        insert_rbt(&root, 14);
        remove_rbt(&root, 15);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->left->left->data == 1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 7);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 30);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 40);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 20);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->right->left->right->data == 25);
        CU_ASSERT(root->right->left->right->color == RED);
        CU_ASSERT(root->right->left->left->data == 14);
        CU_ASSERT(root->right->left->left->color == RED);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB's sibling is red
        // rm left node of a parent
        // node_to_del has two children
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        insert_rbt(&root, 25);
        insert_rbt(&root, 40);
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        root->right->color = BLACK;
        root->right->right->color = RED;
        root->right->right->right->color = BLACK;
        root->right->right->left->color = BLACK;
        insert_rbt(&root, 14);
        insert_rbt(&root, 16);
        remove_rbt(&root, 15);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->left->left->data == 1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 7);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 30);
        CU_ASSERT(root->right->right->color == RED);
        CU_ASSERT(root->right->left->data == 14);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->right->left->right->data == 16);
        CU_ASSERT(root->right->left->right->color == RED);
        CU_ASSERT(root->right->right->left->data == 25);
        CU_ASSERT(root->right->right->left->color == BLACK);
        CU_ASSERT(root->right->right->right->data == 40);
        CU_ASSERT(root->right->right->right->color == BLACK);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB's sibling is red
        // rm right node of a parent
        // node_to_del has no children
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        root->right->color = BLACK;
        root->right->right->color = BLACK;
        root->right->color = BLACK;
        root->right->left->color = BLACK;
        insert_rbt(&root, 0);
        insert_rbt(&root, -1);
        root->left->left->color = RED;
        root->left->left->left->color = BLACK;
        root->left->left->right->color = BLACK;
        remove_rbt(&root, 7);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->left->data == 0);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->left->left->data == -1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 5);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 30);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 15);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->left->right->left->data == 1);
        CU_ASSERT(root->left->right->left->color == RED);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // node_to_del has right child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        root->right->color = BLACK;
        root->right->right->color = BLACK;
        root->right->color = BLACK;
        root->right->left->color = BLACK;
        insert_rbt(&root, 0);
        insert_rbt(&root, -1);
        root->left->left->color = RED;
        root->left->left->left->color = BLACK;
        root->left->left->right->color = BLACK;
        insert_rbt(&root, 8);
        remove_rbt(&root, 7);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->left->data == 0);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->left->left->data == -1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 5);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 30);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 15);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->left->right->left->data == 1);
        CU_ASSERT(root->left->right->left->color == RED);
        CU_ASSERT(root->left->right->right->data == 8);
        CU_ASSERT(root->left->right->right->color == RED);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB's sibling is red
        // rm right node of a parent
        // node_to_del has left child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 20);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 15);
        insert_rbt(&root, 30);
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        root->right->color = BLACK;
        root->right->right->color = BLACK;
        root->right->color = BLACK;
        root->right->left->color = BLACK;
        insert_rbt(&root, 0);
        insert_rbt(&root, -1);
        root->left->left->color = RED;
        root->left->left->left->color = BLACK;
        root->left->left->right->color = BLACK;
        insert_rbt(&root, 6);
        remove_rbt(&root, 7);
        CU_ASSERT(root->data == 10);
        CU_ASSERT(root->left->data == 0);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->left->left->data == -1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 5);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 20);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 30);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 15);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->left->right->left->data == 1);
        CU_ASSERT(root->left->right->left->color == RED);
        CU_ASSERT(root->left->right->right->data == 6);
        CU_ASSERT(root->left->right->right->color == RED);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB's sibling is red
        // rm right node of a parent
        // node_to_del has right child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 30);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 25);
        insert_rbt(&root, 40);
        insert_rbt(&root, 20);
        insert_rbt(&root, 28);
        root->left->left->color = BLACK;
        root->left->right->color = BLACK;
        root->right->color = BLACK;
        root->right->right->color = BLACK;
        root->right->left->color = RED;
        root->right->left->left->color = BLACK;
        root->right->left->right->color = BLACK;
        remove_rbt(&root, 1);
        CU_ASSERT(root->data == 25);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->left->data == 10);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->left->left->data == 5);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 20);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->data == 30);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->right->right->data == 40);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 28);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->left->left->right->data == 7);
        CU_ASSERT(root->left->left->right->color == RED);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // DB's sibling is red
        // rm right node of a parent
        // node_to_del has right child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        insert_rbt(&root, 30);
        insert_rbt(&root, 1);
        insert_rbt(&root, 7);
        insert_rbt(&root, 25);
        insert_rbt(&root, 40);
        insert_rbt(&root, 8);
        insert_rbt(&root, 6);
        root->left->color = BLACK;
        root->right->right->color = BLACK;
        root->right->left->color = BLACK;
        root->left->right->color = RED;
        root->left->right->left->color = BLACK;
        root->left->right->right->color = BLACK;
        /* insert_rbt(&root, 50); */
        /* insert_rbt(&root, 35); */
        remove_rbt(&root, 40);
        CU_ASSERT(root->data == 7);
        CU_ASSERT(root->color == BLACK);
        CU_ASSERT(root->right->data == 10);
        CU_ASSERT(root->right->color == BLACK);
        CU_ASSERT(root->left->data == 5);
        CU_ASSERT(root->left->color == BLACK);
        CU_ASSERT(root->right->right->data == 30);
        CU_ASSERT(root->right->right->color == BLACK);
        CU_ASSERT(root->right->left->data == 8);
        CU_ASSERT(root->right->left->color == BLACK);
        CU_ASSERT(root->left->left->data == 1);
        CU_ASSERT(root->left->left->color == BLACK);
        CU_ASSERT(root->left->right->data == 6);
        CU_ASSERT(root->left->right->color == BLACK);
        CU_ASSERT(root->right->right->left->data == 25);
        CU_ASSERT(root->right->right->left->color == RED);
        CU_ASSERT(is_rb_tree(root, &issue) == 1);
        free_tree(root);

        // remove root */
        // root has no children
        root = NULL;
        insert_rbt(&root, 10);
        remove_rbt(&root, 10);
        CU_ASSERT(root == NULL);
        free_tree(root);

        // remove root */
        // root has one left child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 5);
        remove_rbt(&root, 10);
        CU_ASSERT(root->data == 5);
        CU_ASSERT(root->color == BLACK);
        free_tree(root);

        // remove root */
        // root has one right child
        root = NULL;
        insert_rbt(&root, 10);
        insert_rbt(&root, 20);
        remove_rbt(&root, 10);
        CU_ASSERT(root->data == 20);
        CU_ASSERT(root->color == BLACK);
        /* free_tree(root); */
    }

    // remove root
    // root has two children
    root = NULL;
    insert_rbt(&root, 10);
    insert_rbt(&root, 5);
    insert_rbt(&root, 30);
    insert_rbt(&root, 1);
    insert_rbt(&root, 7);
    insert_rbt(&root, 25);
    insert_rbt(&root, 40);
    insert_rbt(&root, 8);
    insert_rbt(&root, 6);
    root->left->color = BLACK;
    root->right->right->color = BLACK;
    root->right->left->color = BLACK;
    root->left->right->color = RED;
    root->left->right->left->color = BLACK;
    root->left->right->right->color = BLACK;
    remove_rbt(&root, 10);
    CU_ASSERT(is_rb_tree(root, &issue) == 1);

    tree_to_dot(root);

    free_tree(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of remove_rbt()", test_remove_rbt);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
