#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_heapify() {
    size_t size = 8;
    int arr[8] = {10, 5, 9, 2, 4, 1, 0, -1};

    // print initial arr
    printf("\ninitial array \n");
    for (size_t i = 0; i < size; i++) {
        printf("\narr number = %d\n", arr[i]);
    }
    printf("\n--------------------\n");

    Node *root = create_binary_tree(arr, size);

    printf("\ncomplete binary tree\n");
    traverse_level_order(root);
    printf("\n--------------------\n");

    heapify(root);

    traverse_level_order(root);
    printf("\n--------------------\n");

    int expected_heapified[] = {-1, 2, 0, 5, 4, 1, 9, 10};

    CU_ASSERT(root->data == expected_heapified[0]);
    CU_ASSERT(root->left->data == expected_heapified[1]);
    CU_ASSERT(root->right->data == expected_heapified[2]);
    CU_ASSERT(root->left->left->data == expected_heapified[3]);
    CU_ASSERT(root->left->right->data == expected_heapified[4]);
    CU_ASSERT(root->right->left->data == expected_heapified[5]);
    CU_ASSERT(root->right->right->data == expected_heapified[6]);
    CU_ASSERT(root->left->left->left->data == expected_heapified[7]);

    free_tree(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of heapify()", test_heapify);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
