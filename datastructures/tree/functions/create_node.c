#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"


Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "memory allocation failed for node");
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
