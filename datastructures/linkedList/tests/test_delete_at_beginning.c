#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"
#include "../functions/delete_at_beginning.c"
#include "../functions/get_length.c"
#include "../functions/insert_at_beginning.c"
#include "../functions/insert_at_end.c"
#include "../functions/traverse.c"
#include "../functions/free_list.c"

void test_delete_at_beginning() {
    Node *head = NULL;
    // case #1 - list is empty
    deleteAtBeginning(&head);
    CU_ASSERT(get_length(head) == 0);
    

    // case #2 - list has one node
    insertAtBeginning(&head, 10);
    insertAtEnd(&head, 20);
    deleteAtBeginning(&head);
    CU_ASSERT(get_length(head) == 1);
    CU_ASSERT(head->number == 20);
    traverse(head);
    freeList(&head);

}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(
        suite, "test of delete_at_beginning()", test_delete_at_beginning);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
