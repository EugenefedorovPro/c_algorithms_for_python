#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_refresh_arr_of_removed_numbers() {

    int *arr_of_removed_numbers = NULL;
    size_t size = 0;

    refresh_arr_of_removed_numbers(&arr_of_removed_numbers, &size, 10);
    refresh_arr_of_removed_numbers(&arr_of_removed_numbers, &size, 20);
    refresh_arr_of_removed_numbers(&arr_of_removed_numbers, &size, 30);
    refresh_arr_of_removed_numbers(&arr_of_removed_numbers, &size, 40);

    int expected[] = {10, 20, 30, 40};
    printf("\nsize = %zu\n", size);
    printf("\nrefresh_arr_of_removed_numbers: \n");
    for (size_t i = 0; i < size; i++) {
        printf("\n%d\n", arr_of_removed_numbers[i]);
        CU_ASSERT(expected[i]);
    }

    free(arr_of_removed_numbers);

}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite,
                "test of test_refresh_arr_of_removed_numbers()",
                test_refresh_arr_of_removed_numbers);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
