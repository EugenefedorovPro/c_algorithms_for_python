#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

Node *create_node(int *arr, size_t idx) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "memory allocation failed for node");
        return NULL;
    }
    node->data = arr[idx];
    node->left = NULL;
    node->right = NULL;
    node->index = idx;
    return node;
}

Node *create_tree(int *arr, size_t idx, size_t size) {
    if (idx >= size) {
        return NULL;
    }
    Node *root = create_node(arr, idx);
    root->left = create_tree(arr, 2 * idx + 1, size);
    root->right = create_tree(arr, 2 * idx + 2, size);
    return root;
};

Node *create_binary_tree(int *arr, size_t size) {
    return create_tree(arr, 0, size);
}
