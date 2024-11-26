
#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void do_traverse_preorder(Node *root, size_t *idx) {
    if (root == NULL) return;

    printf("\nidx = %zu - key = %d\n", *idx, root->key);

    if (root->left != NULL) {
        (*idx)++;
        do_traverse_preorder(root->left, idx);
    }
    if (root->right != NULL) {
        do_traverse_preorder(root->right, idx);
    }
}

void traverse_preorder(Node *root) {
    size_t idx = 0;
    printf("\nTraverse preorder:\n");
    do_traverse_preorder(root, &idx);
}
