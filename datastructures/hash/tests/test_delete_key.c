#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"

void test_deleteKey() {
    // case #1 -  key-value pair exist
    deleteKey(NULL, NULL);

    // case #2 delete key, which exists
    HashTable *table = initialize_hash_table();
    if (!table) return;
    char keyToDelete[] = "c";
    add(keyToDelete, 10, &table);
    add("being", 20, &table);
    traverse(table);
    deleteKey(keyToDelete, &table);
    traverse(table);
    // check number of empty slots
    size_t count = 0;
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->pairs[i].key == NULL) {
            count++;
        }
    }
    CU_ASSERT(count == 9);
    // if key does not exist, nothing happens
    deleteKey("terra", &table);
    free(table->pairs);
    free(table);

    // case #3 if capacity > 10 && size <= (capacity - 10)  / 2
    table = initialize_hash_table();
    if (!table) return;

    int numLetters = 6;
    char strings[numLetters][2];
    for (int i = 0; i < numLetters; i++) {
        strings[i][0] = 'a' + i;
        strings[i][1] = '\0';
    }

    for (int i = 0; i < numLetters; i++) {
        add(strings[i], i, &table);
    }

    printf("\n--------------------\n");
    printf("new capacity = %li", table->capacity);
    printf("\n--------------------\n");

    printf("\n--------------------\n");
    printf("\ncase #3 if capacity > 10 && size <= (capacity - 10)  / 2\n");
    printf("\n--------------------\n");
    CU_ASSERT(table->capacity == 20);
    traverse(table);
    deleteKey("a", &table);
    deleteKey("b", &table);
    CU_ASSERT(table->capacity == 10);
    traverse(table);
    free(table);

    // case #4 - collision after rehashing
    table = initialize_hash_table();
    if (!table) return;

    numLetters = 4;
    for (int i = 0; i < numLetters; i++) {
        strings[i][0] = 'a' + i;
        strings[i][1] = '\0';
    }

    for (int i = 0; i < numLetters; i++) {
        add(strings[i], i, &table);
    }

    printf("\n--------------------\n");
    printf("\n+++++++++ case #4 collision after rehashing ++++++++++\n");
    printf("\n--------------------\n");
    CU_ASSERT(table->capacity == 10);
    add("time", 100, &table);
    add("mite", 100, &table);
    traverse(table);
    deleteKey("a", &table);
    CU_ASSERT(table->capacity == 10);
    traverse(table);
    free(table);



}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Hash table Suite", NULL, NULL);
    CU_add_test(suite, "test of deleteKey()\n", test_deleteKey);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
