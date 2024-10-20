#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

Node *create_tree_recurse(int *arr, size_t low, size_t high) {
    if (low <= high) {
        if (low == high) {
            return create_node(arr[low], NO_COLOR);
        }
        // get the mid
        size_t mid = low + (high - low + 1) / 2;

        Node *node = create_node(arr[mid], NO_COLOR);

        // left
        if (low < mid) {
            node->left = create_tree_recurse(arr, low, mid - 1);
        }

        // right
        if (high > mid) {
            node->right = create_tree_recurse(arr, mid + 1, high);
        }
        return node;
    }
    return NULL;
}

Node *create_binary_search_tree(int *arr, size_t size) {
    // empty arr check 
    if (arr == NULL || size == 0) {
        fprintf(stderr, "ERROR: arr is empty or size = 0");
        exit(EXIT_FAILURE);
    }
    // sort arr
    quick(arr, size);
    return create_tree_recurse(arr, 0, size - 1);
}
