#include <stdio.h>
#include <stdlib.h>
#include "../declarations.h"

void insertAtBeginning(Node **head, int newData) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("No memory allocated for a new node at beginning\n");
        return;
    }
    newNode->number = newData;
    newNode->next = *head;
    *head = newNode;
}
