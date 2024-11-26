#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_copy_tree() {
    Node *root = NULL;
    insert_rbt(&root, 10, "empty");
    insert_rbt(&root, 40, "empty");
    insert_rbt(&root, 60, "empty");
    insert_rbt(&root, 70, "empty");
    insert_rbt(&root, 35, "empty");
    traverse_level_order(root);

    Node *new_root = copy_tree(root);
    traverse_level_order(root);
    CU_ASSERT(root->key == new_root->key);
    CU_ASSERT(root->color == new_root->color);
    CU_ASSERT(root->left->key == new_root->left->key);
    CU_ASSERT(root->left->color == new_root->left->color);
    CU_ASSERT(root->right->key == new_root->right->key);
    CU_ASSERT(root->right->color == new_root->right->color);
    CU_ASSERT(root->right->right->key == new_root->right->right->key);
    CU_ASSERT(root->right->right->color == new_root->right->right->color);
    CU_ASSERT(root->left->right->key == new_root->left->right->key);
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
