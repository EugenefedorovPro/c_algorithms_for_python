#include <stdio.h>
#include "declarations.h"

int main() {
    Node *head = NULL; 
    insertAtBeginning(&head, 10);
    insertAtEnd(&head, 20);
    insertAtPosition(&head, 15, 2);
    traverse(head);
    
    return 0;
}
