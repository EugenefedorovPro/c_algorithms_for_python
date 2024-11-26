#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void insert_bst(Node **node, int key) {
    if (*node == NULL) {
        *node = create_node(key, "empty", NO_COLOR);
        return;
        
    }
    // case #1 key == node key
    if ((*node)->key == key) {
        printf("\nThe key is already present in the tree\n");
        return;
    }

    if (key < (*node)->key) {
        if ((*node)->left == NULL) {
            (*node)->left = create_node(key, "empty", NO_COLOR);
            return;
        }
        insert_bst(&(*node)->left, key);
    }

    if (key > (*node)->key) {
        if ((*node)->right == NULL) {
            (*node)->right = create_node(key, "empty", NO_COLOR);
            return;
        }
        insert_bst(&(*node)->right, key);
    }
}
