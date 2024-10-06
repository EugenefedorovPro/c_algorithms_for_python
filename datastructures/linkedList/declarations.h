#ifndef DECLARATIONS_H
#define DECLARATIONS_H

typedef struct Node {
    int number;
    struct Node *next;
} Node;

int get_length(Node *head);
void insertAtBeginning(Node **head, int newData);
void traverse(Node *head);
int *getAllNumbers(Node *head);
void insertAtEnd(Node **head, int newData);
void insertAtPosition(Node **head, int NewData, int position);
void freeList(Node **head);
void deleteAtBeginning(Node **head);
void deleteAtEnd(Node **head);
void deleteAtPosition(Node **head, int position);
#endif
