#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_insert_bst() {
    size_t size = 7;
    int arr[7] = {
        70,
        60,
        50,
        40,
        30,
        20,
        10,
    };
    // print initial arr
    printf("\ninitial array: \n");
    for (size_t i = 0; i < size; i++) {
        printf("\narr number = %d\n", arr[i]);
    }
    printf("\n--------------------\n");

    printf("\ncreate_binary_search_tree \n");
    Node *root = create_binary_search_tree(arr, size);
    traverse_level_order(root);

    // case #0 - add to extreme right
    int key = 80;
    insert_bst(&root, key);
    CU_ASSERT(key == root->right->right->right->key);
    // case #1 - add to extreme left
    int data1 = -1;
    insert_bst(&root, data1);
    CU_ASSERT(data1 == root->left->left->left->key);
    // case #2 - add to the middle 
    int data2 = 35;
    insert_bst(&root, data2);
    CU_ASSERT(data2 == root->left->right->right->key);

    traverse_level_order(root);

    free_tree(root);

    // case #3 - empty root
    Node *root1 = NULL;
    insert_bst(&root1, 10);
    CU_ASSERT(root1->key == 10);


    traverse_level_order(root1);

    free_tree(root1);

}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of insert_bst()", test_insert_bst);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
