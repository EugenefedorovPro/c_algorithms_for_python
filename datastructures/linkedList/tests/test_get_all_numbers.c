#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "../declarations.h"
#include "../functions/get_all_numbers.c"
#include "../functions/get_length.c"
#include "../functions/insert_at_beginning.c"

void test_get_all_numbers() {
    Node *head = NULL;
    insertAtBeginning(&head, 300);
    insertAtBeginning(&head, 200);
    insertAtBeginning(&head, 100);

    // get length of the list
    int length = get_length(head);
    printf("length = %d\n", length);

    // get the pointer to the array of number in the list
    int *arr = getAllNumbers(head);
    if (arr == NULL) {
        printf("pointer to the array of numbers in list is not assigned\n");
        return;
    }

    // check expected numbers over actual arr
    int expected[3] = {100, 200, 300};
    for (int i = 0; i < length; i++) {
        printf("number = %d\n", arr[i]);
        CU_ASSERT(arr[i] == expected[i]);
    }
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Linked List Suite", NULL, NULL);
    CU_add_test(suite, "test of get_all_numbers()", test_get_all_numbers);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
