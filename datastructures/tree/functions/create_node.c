#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"


Node *create_node(int key, char *value, Color color) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "memory allocation failed for node");
        return NULL;
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->color = color;

    size_t value_size = strlen(value);
    node->value = malloc(sizeof(char) * (value_size +1));
    if (node->value == NULL) {
        free(node);
        fprintf(stderr, "memory allocation failed for node->value");
        return NULL;
    }

    strcpy(node->value, value);
    
    return node;
}
