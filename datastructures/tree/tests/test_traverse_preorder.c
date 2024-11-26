#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_traverse_preorder() {
    size_t size = 17;
    int arr[6] = {3, 9, 2, 1, 4, 5};
    // print initial arr
    for (size_t i = 0; i < size; i++) {
        printf("\narr number = %d\n", arr[i]);
    }
    printf("\n--------------------\n");

    Node *root = create_binary_tree(arr, size);

    traverse_preorder(root);

    // check root
    CU_ASSERT(root->key == 3);
    // check left subtree
    CU_ASSERT(root->left->key == 9);
    CU_ASSERT(root->left->left->key == 1);
    CU_ASSERT(root->left->right->key == 4);
    // check right subtree
    CU_ASSERT(root->right->key == 2);
    CU_ASSERT(root->right->left->key == 5);
    free_tree(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of traverse_preorder()", test_traverse_preorder);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
