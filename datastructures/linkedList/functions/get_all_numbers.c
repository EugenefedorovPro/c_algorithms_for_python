#include <stdio.h>
#include "../declarations.h"
#include <stdlib.h>

int *getAllNumbers(Node *head) {
    // get length of the list
    int length = get_length(head);
    // allocate memory for Array of numbers
    int *arr = malloc(length * sizeof(int));
    if (arr == NULL) {
        /* printf("No memory allocated for getAllNumbers function"); */
        return NULL;
    }

    // accumulate numbers in Array while traversing
    Node *current = head;
    for (int i = 0; i < length; i++) {
        arr[i] = current->number;
        printf("%d\n", current->number);
        current = current->next;
    }
    return arr;
}
