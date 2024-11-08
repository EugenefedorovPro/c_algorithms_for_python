#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void free_tree(Node *root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

