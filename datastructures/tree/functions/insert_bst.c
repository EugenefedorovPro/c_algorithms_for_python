#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void insert_bst(Node **node, int data) {
    if (*node == NULL) {
        *node = create_node(data);
        return;
        
    }
    // case #1 data == node data
    if ((*node)->data == data) {
        printf("\nThe data is already present in the tree\n");
        return;
    }

    if (data < (*node)->data) {
        if ((*node)->left == NULL) {
            (*node)->left = create_node(data);
            return;
        }
        insert_bst(&(*node)->left, data);
    }

    if (data > (*node)->data) {
        if ((*node)->right == NULL) {
            (*node)->right = create_node(data);
            return;
        }
        insert_bst(&(*node)->right, data);
    }
}
