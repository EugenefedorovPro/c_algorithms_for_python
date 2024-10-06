#include <stdlib.h>

#include "../declarations.h"

void freeList(Node **head) {
    Node *current = *head;
    Node *next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
    return;
}
