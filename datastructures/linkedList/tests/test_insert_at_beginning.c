#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"
#include "../functions/get_all_numbers.c"
#include "../functions/get_length.c"
#include "../functions/insert_at_beginning.c"

void test_insert_at_beginning() {
    Node *head = NULL;
    insertAtBeginning(&head, 300);
    insertAtBeginning(&head, 200);
    insertAtBeginning(&head, 100);

    // check expected numbers over actual arr
    int expected[3] = {100, 200, 300};
    Node *actual = head;
    for (int i = 0; i < 3; i++) {
        printf("number = %d\n", actual->number);
        CU_ASSERT(actual->number == expected[i]);
        actual = actual->next;
    }
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(
        suite, "test of insert_at_beginning()", test_insert_at_beginning);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
