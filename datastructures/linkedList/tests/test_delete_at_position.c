#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"
#include "../functions/delete_at_beginning.c"
#include "../functions/delete_at_end.c"
#include "../functions/delete_at_position.c"
#include "../functions/free_list.c"
#include "../functions/get_length.c"
#include "../functions/insert_at_beginning.c"
#include "../functions/insert_at_end.c"
#include "../functions/traverse.c"

void test_delete_at_position() {
    Node *head = NULL;
    // case #1 - list is empty
    printf("\ncase #1 - list is empty\n");
    deleteAtPosition(&head, 10);
    CU_ASSERT(get_length(head) == 0);
    freeList(&head);

    // case #2 validate if the position within the allowed range
    printf("\ncase #2 validate if the position within the allowed range\n");
    insertAtBeginning(&head, 10);
    deleteAtPosition(&head, 2);
    CU_ASSERT(get_length(head) == 1);
    freeList(&head);

    // case #3 - only one element in the list, delete the 1st position
    printf("\ncase #3 - only one element in the list, delete the 1st position\n");
    insertAtBeginning(&head, 10);
    deleteAtPosition(&head, 1);
    CU_ASSERT(get_length(head) == 0);
    freeList(&head);

    // case #5 - delete from the middle: previous and following nodes' pointers
    printf("\ncase #5 - delete from the middle\n");
    insertAtBeginning(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    deleteAtPosition(&head, 2);
    CU_ASSERT(get_length(head) == 2);
    int expected[] = {10, 30};
    Node *current = head;
    for (int i = 0; i < 2; i++) {
        printf("actual = %d, expected = %d\n", current->number, expected[i]);
        CU_ASSERT(current->number == expected[i]);
        current = current->next;

    }
    traverse(head);
    /* freeList(&head); */
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(
        suite, "test of delete_at_position()\n", test_delete_at_position);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
