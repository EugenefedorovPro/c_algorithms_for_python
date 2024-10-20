#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void print_relatives_right(Node **node, int data, Node *grand) {
    printf("\n*** print relatives right ***\n");
    // node
    printf("\nnode d = %d, c = %d\n", (*node)->right->data, (*node)->right->color);
    // parent
    printf("\nparent d = %d, c = %d\n", (*node)->data, (*node)->color);
    if (grand != NULL) {
        // grand
        printf("\ngrand d = %d, c = %d\n", grand->data, grand->color);
        // uncle
        printf("\nuncle d = %d, c = %d\n", grand->left->data, grand->left->color);
    }
    printf("\n--------------------\n");
}

void print_relatives_left(Node **node, int data, Node *grand) {
    printf("\n*** print relatives left ***\n");
    // node
    printf("\nnode d = %d, c = %d\n", (*node)->left->data, (*node)->left->color);
    // parent
    printf("\nparent d = %d, c = %d\n", (*node)->data, (*node)->color);
    if (grand != NULL) {
        // grand
        printf("\ngrand d = %d, c = %d\n", grand->data, grand->color);
        // uncle
        printf("\nuncle d = %d, c = %d\n", grand->right->data, grand->right->color);
    }
    printf("\n--------------------\n");
}

void insert_recurse(Node **node, int data, Node *grand) {
    if (*node == NULL) {
        *node = create_node(data, BLACK);
        return;
    }

    if (data > (*node)->data) {
        if ((*node)->right == NULL) {
            (*node)->right = create_node(data, RED);
            /* print_relatives_right(node, data, grand); */
            
            // if parent and uncle are red recolor them to black
            if (grand != NULL && grand->left != NULL && grand->left->color == RED && (*node)->color == RED) {
                grand->left->color = BLACK;
                (*node)->color = BLACK;
            }

        } else {
            insert_recurse(&((*node)->right), data, *node);
        }
    }

    if (data < (*node)->data) {
        if ((*node)->left == NULL) {
            (*node)->left = create_node(data, RED);
            /* print_relatives_left(node, data, grand); */
            
            // if parent and uncle are red recolor them to black
            if (grand != NULL && grand->right->color == RED && (*node)->color == RED) {
                grand->right->color = BLACK;
                (*node)->color = BLACK;
            }

        } else {
            insert_recurse(&((*node)->left), data, *node);
        }
    }
}

void insert_rbt(Node **node, int data) {
    Node *grand = NULL;
    insert_recurse(node, data, grand);
}
