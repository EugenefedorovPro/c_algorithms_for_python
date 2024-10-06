#include <stdio.h>
#include "../declarations.h"

// prints number values in all nodes 
void traverse(Node *head) {
    Node *current = head;
    printf("\n\nResult of the whole linked list traversal: \n");
    while (current) {
        printf("number = %d\n", current->number);
        current = current->next;
    }
    printf("The last node reached\n\n");
}
