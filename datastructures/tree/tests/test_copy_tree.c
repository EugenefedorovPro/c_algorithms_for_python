#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_copy_tree() {
    Node *root = NULL;
    insert_rbt(&root, 10);
    insert_rbt(&root, 40);
    insert_rbt(&root, 60);
    insert_rbt(&root, 70);
    insert_rbt(&root, 35);
    traverse_level_order(root);

    Node *new_root = copy_tree(root);
    traverse_level_order(root);
    CU_ASSERT(root->data == new_root->data);
    CU_ASSERT(root->color == new_root->color);
    CU_ASSERT(root->left->data == new_root->left->data);
    CU_ASSERT(root->left->color == new_root->left->color);
    CU_ASSERT(root->right->data == new_root->right->data);
    CU_ASSERT(root->right->color == new_root->right->color);
    CU_ASSERT(root->right->right->data == new_root->right->right->data);
    CU_ASSERT(root->right->right->color == new_root->right->right->color);
    CU_ASSERT(root->left->right->data == new_root->left->right->data);
    CU_ASSERT(root->left->right->color == new_root->left->right->color);


    tree_to_dot(new_root);
    free_tree(root);
    free_tree(new_root);



}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of copy_tree()", test_copy_tree);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
