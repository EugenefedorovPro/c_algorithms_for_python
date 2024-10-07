#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"
#include "../functions/delete_at_end.c"
#include "../functions/get_length.c"
#include "../functions/insert_at_beginning.c"
#include "../functions/insert_at_end.c"
#include "../functions/traverse.c"

void test_delete_at_end() {
    Node *head = NULL;
    // case #1 - list is empty
    deleteAtEnd(&head);
    CU_ASSERT(get_length(head) == 0);
    

    // case #2 - list has one node
    insertAtBeginning(&head, 10);
    insertAtEnd(&head, 20);
    deleteAtEnd(&head);
    CU_ASSERT(get_length(head) == 1);
    CU_ASSERT(head->number == 10);
    traverse(head);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(
        suite, "test of delete_at_end()\n", test_delete_at_end);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
