#include <stdlib.h>
#include "../declarations.h"

void deleteAtBeginning(Node **head) {
    if (!*head) {
        return;
    };
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}
