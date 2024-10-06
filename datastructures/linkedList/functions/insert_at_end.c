#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void insertAtEnd(Node **head, int newData) {
    // case #1 - list is empty (head = null)
    if (!*head) {
        insertAtBeginning(head, newData);
        return;
    }

    // case #2 - list has one node or more

    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("No memory allocated for a new node at the end\n");
        return;
    }

    newNode->number = newData;
    newNode->next = NULL;

    // Traverse to the last node
    Node *last = *head;
    while (last->next) {  // Traverse until last node
        last = last->next;
    }

    last->next = newNode;  // Link last node to new node
}
