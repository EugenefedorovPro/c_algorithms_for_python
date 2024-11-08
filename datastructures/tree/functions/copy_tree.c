#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void copy_subtree(Node *old_node, Node **new_node) {
    if (old_node == NULL) return;

    *new_node = create_node(old_node->data, old_node->color);

    if (old_node->left) {
        copy_subtree(old_node->left, &((*new_node)->left));
    }
    
    if (old_node->right) {
        copy_subtree(old_node->right, &((*new_node)->right));
    }
}

// makes deep copy of tree with new memory allocation for every node
Node *copy_tree(Node *root) {
    Node *new_root = NULL;
    if (root) {
        new_root = create_node(root->data, root->color);
    } else {
        return NULL;
    }

    copy_subtree(root, &new_root);

    return new_root;
}
