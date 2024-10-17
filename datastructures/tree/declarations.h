#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdio.h>

typedef enum {
    NO_COLOR = -1,
    BLACK = 0,
    RED = 1,
} Color;

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    Color color;
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

// imported from other blocks of code
// quick sort algorithm
int *quick(int *arr, size_t size);

// binary tree
Node *create_node(int data);
Node *create_binary_tree(int *arr, size_t size);
Node *create_binary_search_tree(int *arr, size_t size);

void free_tree(Node *root);
void traverse_preorder(Node *root);
void traverse_level_order(Node *root);

void insert_bst(Node **node, int data);

// queue
NodesQueue *initiate_queue();
int is_empty(NodesQueue *nodes_queue);
Node *dequeue(NodesQueue *nodes_queue);
void enqueue(NodesQueue *nodes_queue, Node *node);
void free_queue(NodesQueue *nodes_queue);

// heapify
void heapify(Node *root);

#endif
