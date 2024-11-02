#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_remove_rbt() {
   
    
    // NO TREE BALANCING
    // case 1 - check remove node in the left subtree
    // case 1.1 - node to rm has two sub
    // case 1.1.1 - left child of node_to_rm has two children

    Node *root = NULL;
    insert_rbt(&root, 50);
    insert_rbt(&root, 30);
    insert_rbt(&root, 60);
    insert_rbt(&root, 20);
    insert_rbt(&root, 15);
    insert_rbt(&root, 10);
    insert_rbt(&root, 5);

    remove_rbt(&root, 20);
    CU_ASSERT(root->data == 50);
    CU_ASSERT(root->left->data == 15);
    CU_ASSERT(root->right->data == 60);
    CU_ASSERT(root->left->left->data == 10);
    CU_ASSERT(root->left->left->left->data == 5);
    CU_ASSERT(root->left->right->data == 30);
    free_tree(root);

    // case 1.1.2 - left child of node_to_rm has no right child and has left child
    root = NULL;
    insert_rbt(&root, 50);
    insert_rbt(&root, 30);
    insert_rbt(&root, 60);
    insert_rbt(&root, 20);
    insert_rbt(&root, 10);
    insert_rbt(&root, 5);

    remove_rbt(&root, 20);
    CU_ASSERT(root->data == 50);
    CU_ASSERT(root->right->data == 60);
    CU_ASSERT(root->left->data == 10);
    CU_ASSERT(root->left->left->data == 5);
    CU_ASSERT(root->left->right->data == 30);
    remove_rbt(&root, 20);
    free_tree(root);

    // case 1.1.3 - left child of node_to_rm has no children
    root = NULL;
    insert_rbt(&root, 50);
    insert_rbt(&root, 30);
    insert_rbt(&root, 60);
    insert_rbt(&root, 20);
    insert_rbt(&root, 10);

    remove_rbt(&root, 20);
    CU_ASSERT(root->data == 50);
    CU_ASSERT(root->right->data == 60);
    CU_ASSERT(root->left->data == 10);
    CU_ASSERT(root->left->right->data == 30);
    remove_rbt(&root, 20);
    free_tree(root);

    // case 1.2.1 - right child of node_to_rm has two children

    root = NULL;
    insert_rbt(&root, 50);
    insert_rbt(&root, 30);
    insert_rbt(&root, 60);
    insert_rbt(&root, 70);
    insert_rbt(&root, 65);
    insert_rbt(&root, 80);
    insert_rbt(&root, 63);
    insert_rbt(&root, 66);

    remove_rbt(&root, 65);
    CU_ASSERT(root->data == 50);
    CU_ASSERT(root->left->data == 30);
    CU_ASSERT(root->right->data == 66);
    CU_ASSERT(root->right->right->data == 70);
    CU_ASSERT(root->right->right->right->data == 80);
    CU_ASSERT(root->right->left->right->data == 63);
    CU_ASSERT(root->right->left->data == 60);
    free_tree(root);

    // case 1.1.1 - right child of node_to_rm has two children
    root = NULL;
    insert_rbt(&root, 50);
    insert_rbt(&root, 30);
    insert_rbt(&root, 60);
    insert_rbt(&root, 70);
    insert_rbt(&root, 65);
    insert_rbt(&root, 80);
    insert_rbt(&root, 63);
    insert_rbt(&root, 66);

    remove_rbt(&root, 65);
    CU_ASSERT(root->data == 50);
    CU_ASSERT(root->left->data == 30);
    CU_ASSERT(root->right->data == 66);
    CU_ASSERT(root->right->right->data == 70);
    CU_ASSERT(root->right->right->right->data == 80);
    CU_ASSERT(root->right->left->right->data == 63);
    CU_ASSERT(root->right->left->data == 60);
    free_tree(root);

    // case 1.2.2 - left child of node_to_rm has no left child and has right child
    root = NULL;
    insert_rbt(&root, 50);
    insert_rbt(&root, 30);
    insert_rbt(&root, 60);
    insert_rbt(&root, 70);
    insert_rbt(&root, 65);
    insert_rbt(&root, 80);
    insert_rbt(&root, 63);

    remove_rbt(&root, 65);
    CU_ASSERT(root->data == 50);
    CU_ASSERT(root->left->data == 30);
    CU_ASSERT(root->right->data == 70);
    CU_ASSERT(root->right->right->data == 80);
    CU_ASSERT(root->right->left->data == 60);
    CU_ASSERT(root->right->left->right->data == 63);
    free_tree(root);

    // case 1.1.3 - left child of node_to_rm has no children
    root = NULL;
    insert_rbt(&root, 50);
    insert_rbt(&root, 30);
    insert_rbt(&root, 60);
    insert_rbt(&root, 70);
    insert_rbt(&root, 65);
    insert_rbt(&root, 63);

    remove_rbt(&root, 65);
    CU_ASSERT(root->data == 50);
    CU_ASSERT(root->left->data == 30);
    CU_ASSERT(root->right->data == 70);
    CU_ASSERT(root->right->left->data == 60);
    CU_ASSERT(root->right->left->right->data == 63);
    free_tree(root);
    
    // RB TREE BALANCE
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


    traverse_level_order(root);

    tree_to_dot(root);

    free(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of insert_rbt()", test_remove_rbt);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
