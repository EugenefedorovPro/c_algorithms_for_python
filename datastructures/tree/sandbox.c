#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int main() {
    // create array
    size_t size = 3;
    int *arr = malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    // print arr
    printf("\narr = ");
    for (size_t i = 0; i < size; i++) {
        printf(" %d ", arr[i]);
    }
    printf("\n--------------------\n");

    // transform arr into a balanced tree
    Node *root = create_binary_search_tree(arr, size);
    traverse_level_order(root);

    return 0;
}
