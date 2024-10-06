#include "../declarations.h"

int get_length(Node *head) {
    int count = 0;
    Node *current = head;
    while (current) {
        current = current->next;
        count++;
    }
    return count;
}
