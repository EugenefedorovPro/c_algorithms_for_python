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
    CU_ASSERT(root->data == 3);
    // check left subtree
    CU_ASSERT(root->left->data == 9);
    CU_ASSERT(root->left->left->data == 1);
    CU_ASSERT(root->left->right->data == 4);
    // check right subtree
    CU_ASSERT(root->right->data == 2);
    CU_ASSERT(root->right->left->data == 5);
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
