#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdio.h>

// custom types
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

typedef struct Stack {
    Node *node;
    struct Stack *next;
} Stack;

// utils
void print_arr(int *arr, size_t size);
void tree_to_dot(Node *root);

// imported from other blocks of code
// quick sort algorithm
int *quick(int *arr, size_t size);

// binary tree
Node *create_node(int data, Color color);
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

// stack
Stack *create_stack_item(Node *node);
void s_append(Stack **stack, Node *node);
Node *s_pop(Stack **stack);
int is_stack_empty(Stack **stack);
void print_all_stack(Stack **stack);
size_t get_stack_size(Stack **stack);
Node *s_peek(Stack **stack);

// red black tree
// insert
void balance(Stack **stack, Node **node);
void insert_rbt(Node **node, int data);
void insert_recurse(Node **node, int data, Stack **stack);
void check_above(Node **node, int data, Stack **stack);
void right_right_rotation(Node **grandparent, Node **parent);
void left_left_rotation(Node **grandparent, Node **parent);
void right_uncle_red(Node **parent, Node **grandparent, Stack **stack);
void right_uncle_black(Node **parent, Node **grandparent, Stack **stack);
//
// delete
void remove_rbt(Node **root, int data);
void find_node(Node **node, int data, Stack **stack);
void simple_remove(Node **node, Stack **stack);

#endif
