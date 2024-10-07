#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"
#include "../functions/free_list.c"
#include "../functions/get_all_numbers.c"
#include "../functions/get_length.c"
#include "../functions/insert_at_beginning.c"
#include "../functions/insert_at_end.c"
#include "../functions/insert_at_position.c"
#include "../functions/traverse.c"

void test_insert_at_position() {
    Node *head = NULL;
    // case #1 - list is empty and position == 1 (insertion at beginning)
    insertAtPosition(&head, 10, 1);
    printf(
        "case #1 - list is empty and position == 1.\n Expected = %d, actual = "
        "%d\n",
        10,
        head->number);
    CU_ASSERT(10 == head->number);
    freeList(&head);

    // case #2 - check if position hits the allowed range
    printf("case #2 - check if position hits the allowed range");
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    insertAtPosition(&head, 10, 4);
    traverse(head);
    freeList(&head);

    // case #3 - position = length + 1 (insertion at the end)
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    insertAtPosition(&head, 300, 3);
    int expected[] = {10, 20, 300};
    Node *current = head;
    for (int i = 0; i < 3; i++) {
        printf("case #3 - position = length + 1: actual = %d, expected = %d\n",
               current->number,
               expected[i]);
        CU_ASSERT(current->number == expected[i]);
        current = current->next;
    }

    traverse(head);

    free(current);
    freeList(&head);

    // case #4 - length >= 2 and position >=2 and position < length + 1
    insertAtBeginning(&head, 30);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    insertAtPosition(&head, 100, 2);
    insertAtPosition(&head, 200, 2);
    int expected2[] = {10, 200, 100, 20, 30};
    current = head;
    for (int i = 0; i < 5; i++) {
        printf(
            "case #4 - length >= 2 and position >=2 and position < length + 1: "
            "actual = %d, expected = %d\n",
            current->number,
            expected2[i]);
        CU_ASSERT(current->number == expected2[i]);
        current = current->next;
    }

    /* traverse(head); */

    /* free(current); */
    /* freeList(&head); */
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(
        suite, "test of insert_at_position()\n", test_insert_at_position);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
