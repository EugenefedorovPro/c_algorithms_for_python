#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    size_t index;
} Node;

typedef struct Q_node {
    Node *node;
    struct Q_node *link;
} Q_node;

typedef struct NodesQueue {
    Q_node *first;
    Q_node *rear;
    size_t count;
} NodesQueue;

// binary tree
Node *create_binary_tree(int *arr, size_t size);
void free_tree(Node *root);
void traverse_preorder(Node *root);
void traverse_level_order(Node *root);

// queue
NodesQueue *initiate_queue();
int is_empty(NodesQueue *nodes_queue);
Node *dequeue(NodesQueue *nodes_queue);
void enqueue(NodesQueue *nodes_queue, Node *node);
void free_queue(NodesQueue *nodes_queue);

// heapify
void heapify(Node *root);

#endif
