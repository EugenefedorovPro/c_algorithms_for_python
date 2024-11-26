#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

void test_search_rbt() {

    Node *root = NULL;
    char text_1[] = "text 1";
    char text_2[] = "text 2";
    char text_3[] = "text 3";

    insert_rbt(&root, 10, text_1);
    insert_rbt(&root, 20, text_2);
    insert_rbt(&root, 30, text_3);

    traverse_level_order(root);

    // key is available
    int key = 30;
    char *value = search_rbt(root, key);
    printf("\nkey = %d, value = %s\n", key, value);
    CU_ASSERT(strcmp(value, text_3) == 0);


    // key is unavailable
    value = search_rbt(root, 100);
    CU_ASSERT(value == NULL);

    // tree is empty
    root = NULL;
    value = search_rbt(root, 10);
    CU_ASSERT(value == NULL);


    tree_to_dot(root);

    free_tree(root);
    /* free(value); */
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of search_rbt()", test_search_rbt);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
