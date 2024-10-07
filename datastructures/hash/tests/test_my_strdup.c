#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"

void test_my_strdub() {
    // case #1 - str exists
    char *str = "time";
    char *result = my_strdup(str);
    CU_ASSERT(strcmp(result, str) == 0);
    printf("\ncopy = %s\n", result);
    free(result);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(suite, "test of test_my_strdub()", test_my_strdub);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
