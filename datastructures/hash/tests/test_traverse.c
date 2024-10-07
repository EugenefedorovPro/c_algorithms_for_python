#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"

void test_traverse() {
    HashTable *table = initialize_hash_table();
    traverse(table);
    CU_ASSERT(table->size == 0);
    for (size_t i = 0; i < table->capacity; i++) {
        CU_ASSERT(table->pairs[i].value == 0);
        CU_ASSERT(table->pairs[i].key == NULL);
    }
    free(table->pairs);
    free(table);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Hash Suite", NULL, NULL);
    CU_add_test(suite, "test of traverse()", test_traverse);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
