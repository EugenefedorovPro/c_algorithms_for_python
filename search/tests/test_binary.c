#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_binary() {
    // case #0 - regular
    printf("\ncase #0 - regular\n");
    size_t size = 5;
    int arr[5] = {10, 20, 30, 40, 50};
    int number_to_find = 20;
    int idx = binary(arr, size, number_to_find);

    printf("\nnumber to find n = %d has index = %d ", number_to_find, idx);
    printf("\n--------------------\n");
    CU_ASSERT(idx == 1);
    
    // case #1 - dupes
    printf("\ncase #1 - dupes\n");
    size_t size1 = 5;
    int arr1[5] = {10, 20, 30, 30, 50};
    int number_to_find1 = 30;
    int idx1 = binary(arr1, size1, number_to_find1);

    printf("\nnumber to find n = %d has index = %d ", number_to_find1, idx1);
    printf("\n--------------------\n");
    CU_ASSERT(idx1 == 2);
    
    // case #2 - unsorted array
    printf("\ncase #2 - unsorted array\n");
    size_t size2 = 5;
    int arr2[5] = {10, 20, 40, 30, 50};
    int number_to_find2 = 30;
    int idx2 = binary(arr2, size2, number_to_find2);

    printf("\nnumber to find n = %d has index = %d ", number_to_find2, idx2);
    printf("\n--------------------\n");
    CU_ASSERT(idx2 == -1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Search Suite", NULL, NULL);
    CU_add_test(suite, "test of binary()", test_binary);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
