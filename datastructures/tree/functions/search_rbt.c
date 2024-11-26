#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

char *recurse_search_rbt(Node *node, int key) {
    if (!node) return NULL;

    if (node->key == key) {
        return node->value;
    }

    char *value = recurse_search_rbt(node->left, key);
    if (value) {
        return value;
    }
    return recurse_search_rbt(node->right, key);
}

char *search_rbt(Node *root, int key) {
    if (!root) {
        printf("\nThe tree is empty\n");
        return NULL;
    }

    char *value = recurse_search_rbt(root, key);
    if (!value) {
        printf("\nThe red black tree does not contain key = %d\n", key);
    }

    return value;
}
