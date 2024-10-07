#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"

void test_add() {
    HashTable *table = initialize_hash_table();

    // case #1 - no hash collision
    char key[] = "time";
    int value = 15;
    printf("\n--------------------\n");
    printf("case #1 - no hash collision");
    add(key, value, &table);
    traverse(table);
    CU_ASSERT(table->size == 1);
    free(table->pairs);
    free(table);

    // case #2 - hash collision
    table = initialize_hash_table();
    printf("case #2 - hash collision");
    add("time", 10, &table);
    add("mite", 20, &table);
    CU_ASSERT(table->pairs[1].value = 10);
    CU_ASSERT(table->pairs[2].value = 20);
    traverse(table);
    free(table->pairs);
    free(table);

    // case #3 - enhance capacity from 10 to 20
    table = initialize_hash_table();
    int numLetters = 16;
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

    CU_ASSERT(table->capacity == 40);
    traverse(table);
    free(table);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(suite, "test of test_add()", test_add);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
