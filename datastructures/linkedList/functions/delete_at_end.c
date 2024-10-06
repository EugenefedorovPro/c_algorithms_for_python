#include <stdlib.h>
#include "../declarations.h"


void deleteAtEnd(Node **head) {
    /* case if list is empty */
    if (!*head) {
        return;
    }

    /* traverst to get last and previous nodes; */
    Node *last = *head;
    Node *previous = NULL;
    while (last->next) {
        previous = last;
        last = last->next;
    }

    if (!previous) {
        free(last);
        *head = NULL;
    } else {
        free(last);
        previous->next = NULL;
    }
}
