#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"


Node *create_node(int key, char *value, Color color) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "memory allocation failed for node\n");
        return NULL;
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->color = color;

    if (value == NULL) {
        free(node);
        fprintf(stderr, "invalid input: value is NULL\n");
        return NULL;
    }

    node->value = strdup(value);
    if (node->value == NULL) {
        free(node);
        fprintf(stderr, "memory allocation failed for node->value\n");
        return NULL;
    }

    return node;
}
