#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void insertAtPosition(Node **head, int newData, int position) {
    // case #1 - list is empty and position == 1 (insertion at beginning)
    if (!*head && position == 1) {
        insertAtBeginning(head, newData);
        return;
    }

    // Calculate length by traversing
    int length = get_length(*head);
    /* printf("length = %d\n", length); */

    // case #2 - check if position hits the allowed range
    if (position < 1 || position > length + 1) {
        printf(
            "You can't insert value to linked list if position (%d) < 1 and > "
            "length (%d)\n",
            position,
            length + 1);
        return;
    }

    // case #3 - position = length + 1 (insertion at the end)
    if (position == length + 1) {
        insertAtEnd(head, newData);
        return;
    }

    // case #4 - length >= 2 and position >=2 and position < length + 1
    // (insertion in middle)
    Node *current = *head;
    Node *previous;
    for (int i = 1; i <= position - 1; i++) {
        previous = current;
        current = current->next;
    }
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("No memory allocated for a new node in insertAtPosition - %d\n",
               position);
        return;
    }
    newNode->number = newData;
    newNode->next = current;

    previous->next = newNode;
}
