#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_create_binary_search_tree() {
    // case #1 - even number of elements
    size_t size = 6;
    int arr[6] = {6, 5, 4, 3, 2, 1};
    // print initial arr
    for (size_t i = 0; i < size; i++) {
        printf("\narr number = %d\n", arr[i]);
    }
    printf("\n--------------------\n");

    Node *root = create_binary_search_tree(arr, size);

    traverse_level_order(root);

    printf("\ndata = %d\n", root->key);
    printf("\ndata = %d\n", root->left->key);
    printf("\ndata = %d\n", root->right->key);
    printf("\ndata = %d\n", root->left->left->key);
    printf("\ndata = %d\n", root->left->right->key);
    printf("\ndata = %d\n", root->right->left->key);

    CU_ASSERT(root->key == 4);
    CU_ASSERT(root->left->key == 2);
    CU_ASSERT(root->right->key == 6);

    // left
    CU_ASSERT(root->left->left->key == 1);
    CU_ASSERT(root->left->right->key == 3);

    // right
    CU_ASSERT(root->right->left->key == 5);
    free_tree(root);

    // case #1 - uneven number of elements
    size_t size1 = 7;
    int arr1[7] = {7, 6, 5, 4, 3, 2, 1};
    // print initial arr
    for (size_t i = 0; i < size; i++) {
        printf("\narr number = %d\n", arr1[i]);
    }
    printf("\n--------------------\n");

    Node *root1 = create_binary_search_tree(arr1, size1);

    /* // check root */
    CU_ASSERT(root1->key == 4);
    CU_ASSERT(root1->left->key == 2);
    CU_ASSERT(root1->right->key == 6);

    // left
    CU_ASSERT(root1->left->left->key == 1);
    CU_ASSERT(root1->left->right->key == 3);

    // right
    CU_ASSERT(root1->right->left->key == 5);
    CU_ASSERT(root1->right->right->key == 7);

    traverse_preorder(root1);



    free_tree(root1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of create_binary_search_tree()", test_create_binary_search_tree);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
