#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"

void test_simple_hash() {
    char key[] = "being";
    HashTable *table = initialize_hash_table();
    if (table == NULL) return;

    int result = simpleHash(key, table);

    printf("hash of '%s' = %d\n", key, result);
    CU_ASSERT(result == 7);

    free(table->pairs);
    free(table);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Hash table Suite", NULL, NULL);
    CU_add_test(suite, "test of simpleHash()", test_simple_hash);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
