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
Node *copy_tree(Node *root);
int *copy_array_int(int *original_arr, size_t size);

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

// remove
void remove_rbt(Node **root, int data);
void find_node(Node **node, int data, Stack **stack);
void propagate_and_recolor(Node **node, Stack **stack);
void find_node(Node **node, int data, Stack **stack);
Node *get_sibling(Node **node, Node **parent);
void recolor_sibling_black(Node **node, Node **parent, Node **sibling, Stack **stack);
void recolor_sibling_red(Node **node, Node **parent, Node **sibling, Stack **stack);
void right_siblings_far_child_is_black(Node **parent, Node **sibling);
void right_siblings_far_child_is_red(Node **parent, Node **sibling);
void left_siblings_far_child_is_red(Node **parent, Node **sibling);

// rb tree utils
typedef struct CheckResult {
    int n_black_nodes;
    int is_valid;
} CheckResult;
typedef struct TreeDebug {
    Node *tree_root;
    int *arr_tree_data;
    char *issue;
    int n_failed_rbt;

} TreeDebug;
TreeDebug *initiate_tree_debug();
int *rand_numbers(size_t number);
void create_rand_rbt(Node **root, int **arr_rand_numbers, size_t number);
TreeDebug *check_inserts_in_multiple_trees(
    TreeDebug **tree_debug,  size_t number_nodes, size_t number_trees, int is_random);
int is_rb_tree(Node *root, char **issue);
CheckResult check_red_black_properties(Node *node, char **issue);
void free_tree_debug(TreeDebug *tree_debug);

#endif
