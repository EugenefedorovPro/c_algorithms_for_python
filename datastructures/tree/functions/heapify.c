#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void min_to_top(Node *node) {
    if (node == NULL) return;

    Node *smallest = node;

    // check left
    if (node->left != NULL && node->left->data < smallest->data) {
        smallest = node->left;
    }
    // check right and swap if child < parent
    if (node->right != NULL && node->right->data < smallest->data) {
        smallest = node->right;
    }

    if (smallest != node) {
        int temp = node->data;
        node->data = smallest->data;
        smallest->data = temp;
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
