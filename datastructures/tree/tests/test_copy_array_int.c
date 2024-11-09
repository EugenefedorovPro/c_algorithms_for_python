#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_copy_array_int() {
    size_t size = 10;
    int *original_arr = malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++) {
        original_arr[i] = rand() % size;
    }

    printf("\noriginal array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", original_arr[i]);
    }

    int *copy_arr = copy_array_int(original_arr, size);
    printf("\ncopy array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", copy_arr[i]);
    }

    for (size_t i = 0; i < size; i++) {
        CU_ASSERT(original_arr[i] == copy_arr[i]);
    }



}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of copy_array_int()", test_copy_array_int);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
