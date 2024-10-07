#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"
#include "../functions/get_all_numbers.c"
#include "../functions/get_length.c"
#include "../functions/insert_at_beginning.c"
#include "../functions/insert_at_end.c"

void test_insert_at_end() {
    Node *head = NULL;

    // case #1 - list is empty
    insertAtEnd(&head, 100);
    int length = get_length(head);

    for (int i = 1; i < length; i++) {
        printf("number = %d\n", head->number);
        CU_ASSERT(head->number == 100);
    }

    free(head);

    // case #2 - list has 1 node
    head = NULL;
    insertAtBeginning(&head, 10);
    insertAtEnd(&head, 100);
    int expected[] = {10, 100};
    length = get_length(head);
    Node *current = head;
    for (int i = 0; i < length; i++) {
        printf("number = %d\n", current->number);
        CU_ASSERT(current->number == expected[i]);
        current = current->next;
    }
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(suite, "test of insert_at_end()\n", test_insert_at_end);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
