#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include "../declarations.h"
#include "../functions/get_length.c"
#include "../functions/insert_at_beginning.c"

void test_length() {
    Node *head = NULL;
    // case #1 - list is empty 
    CU_ASSERT(get_length(head) == 0);
    free(head);
    head = NULL;
    
    // case #2 - list has one node
    insertAtBeginning(&head, 10);
    CU_ASSERT(get_length(head) == 1);

}


int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(suite, "test of length()", test_length);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
