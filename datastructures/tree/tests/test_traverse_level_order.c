#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_traverse_level_order() {
    size_t size = 15;
    int *arr = malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    /* // print arr */
    /* printf("\narr = "); */
    /* for (size_t i = 0; i < size; i++) { */
    /*     printf(" %d ", arr[i]); */
    /* } */
    /* printf("\n--------------------\n"); */

    /* // print initial arr */
    /* for (size_t i = 0; i < size; i++) { */
    /*     printf("\narr number = %d\n", arr[i]); */
    /* } */
    /* printf("\n--------------------\n"); */

    Node *root = create_binary_search_tree(arr, size);

    traverse_level_order(root);
    tree_to_dot(root);


    free(arr);
    free_tree(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of traverse_level_order()", test_traverse_level_order);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
