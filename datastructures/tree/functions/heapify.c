#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void min_to_top(Node *node) {
    if (node == NULL) return;

    Node *smallest = node;

    // check left
    if (node->left != NULL && node->left->key < smallest->key) {
        smallest = node->left;
    }
    // check right and swap if child < parent
    if (node->right != NULL && node->right->key < smallest->key) {
        smallest = node->right;
    }

    if (smallest != node) {
        int temp = node->key;
        node->key = smallest->key;
        smallest->key = temp;
        min_to_top(smallest);
    }
}

void heapify(Node *root) {
    if (root == NULL) {
        return;
    }

    heapify(root->left);
    heapify(root->right);

    min_to_top(root);
}
