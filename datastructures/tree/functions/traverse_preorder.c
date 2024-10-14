
#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void traverse_preorder(Node *root) {
    if (root == NULL) return;

    printf("\nindex = %zu, data = %d \n", root->index, root->data);

    if (root->left != NULL) {
        traverse_preorder(root->left);
    }
    if (root->right != NULL) {
        traverse_preorder(root->right);
    }
}

