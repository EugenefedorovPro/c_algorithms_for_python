#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"

void test_search() {
    // case #1 - searched key-value pair exist
    HashTable *table = initialize_hash_table();
    if (!table) return;

    char key[] = "Valera";
    int value = 61;
    add(key, value, &table);

    int result = search(key, table);
    printf("\ncase #1 - searched key-value pair exists: key = %s, value = %d\n",
           key,
           result);
    CU_ASSERT(61 == result);
    traverse(table);
    free(table->pairs);
    free(table);

    // case #2 - searched key-value pair does not exist
    table = initialize_hash_table();
    char key1[] = "Termi";
    result = search(key1, table);
    printf(
        "\ncase #2 - searched key-value pair does not exist: key = %s, value = "
        "%d\n",
        key1,
        result);
    CU_ASSERT(-1 == result);
    free(table->pairs);
    free(table);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Has table Suite", NULL, NULL);
    CU_add_test(suite, "test of search()", test_search);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
