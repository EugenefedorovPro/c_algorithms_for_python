#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"

void test_initiate_hash_table() {
    HashTable *table = initialize_hash_table();
    traverse(table);
    CU_ASSERT(table->capacity == 10);
    free(table->pairs);
    free(table);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Hash Suite", NULL, NULL);
    CU_add_test(
        suite, "test of initialize_hash_table()", test_initiate_hash_table);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
