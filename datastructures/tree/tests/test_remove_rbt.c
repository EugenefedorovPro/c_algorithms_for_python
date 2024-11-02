#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"


void test_remove_rbt() {
    Node *root = NULL;
    insert_rbt(&root, 50);
    insert_rbt(&root, 30);
    insert_rbt(&root, 60);
    insert_rbt(&root, 65);
    
    int data = 90;
    remove_rbt(&root, data);


    traverse_level_order(root);

    tree_to_dot(root);
    free(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of insert_rbt()", test_remove_rbt);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
