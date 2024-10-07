#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include "../declarations.h"
#include "../functions/insert_at_beginning.c"
#include "../functions/free_list.c"

void test_free_list() {
    Node *head = NULL;
    insertAtBeginning(&head, 10);
    freeList(&head);
    CU_ASSERT(head == NULL);

}


int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(suite, "test of free_list()\n", test_free_list);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
