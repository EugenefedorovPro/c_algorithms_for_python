#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int main() {
    size_t size = 6;
    int arr[6] = {3, 9, 2, 1, 4, 5};
    Node *root = create_binary_tree(arr, size);
    traverse_preorder(root);
    free_tree(root);
    /* printf("\ndata = %p\n", root->right->right); */

    return 0;
}
