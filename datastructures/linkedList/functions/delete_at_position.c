#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void deleteAtPosition(Node **head, int position) {
    // case #1 - list is empty
    if (!*head) {
        printf("You can't delete at position '%d', as the list is empty\n",
               position);
        return;
    }

    // get length
    int length = get_length(*head);

    // case #2 validate if the position within the allowed range
    if (position < 1 || position > length) {
        printf(
            "You can't delete node at the position '%d' if position < 1 or "
            "position greater then length of the list (%d)\n",
            position,
            length);
        return;
    }

    // case #3 - only one element in the list, delete the 1st position
    if (position == 1 && length == 1) {
        free(*head);
        *head = NULL;
        return;
    }
    // case #4 - list has more than 1 node, you delete the 1st position:
    // head to point to the following node
    if (position == 1) {
        deleteAtBeginning(head);
    }

    // case #5 - delete from the middle: previous and following nodes to be
    // changed
    if (position > 1 && position < length) {
        Node *current = *head;
        Node *previous = NULL;
        for (int i = 1; i < position; i++) {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
        free(current);
        return;
    }

    // case #6 - delete from the end: previous node should point to NULL
    if (position == length) {
        deleteAtEnd(head);
    }
}
