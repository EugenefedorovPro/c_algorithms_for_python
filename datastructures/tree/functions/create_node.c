#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"


Node *create_node(int key, Color color) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "memory allocation failed for node");
        return NULL;
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->color = color;
    return node;
}
