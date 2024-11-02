#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void simple_remove(Node **node, int data) {
    printf("\nnode to be deleted = %d\n", (*node)->data);

    // node has no children
    if ((*node)->left == NULL && (*node)->right == NULL) {
        free(*node);
        *node = NULL;
    }

    // node has one right child
    if ((*node)->right != NULL && (*node)->left == NULL) {
        Node *temp = (*node)->right;
        free(*node);
        *node = temp;
    }

    // node has one left child
    if ((*node)->left != NULL && (*node)->right == NULL) {
        Node *temp = (*node)->left;
        free(*node);
        *node = temp;
    }
    
    // node has two children
    if ((*node)->left != NULL && (*node)->right == NULL) {
        Node *temp = (*node)->left;
        free(*node);
        *node = temp;
    }
}

void find_node(Node **node, int data, Stack **stack) {
    if ((*node) == NULL) {
        printf("\nTree does not contain %d\n", data);
        return;
    }
    if (data == (*node)->data) {
        simple_remove(node, data);
        return;
    }

    if (data > (*node)->data) {
        find_node(&((*node)->right), data, stack);
    }

    if (data < (*node)->data) {
        find_node(&((*node)->left), data, stack);
    }
}

void remove_rbt(Node **root, int data) {
    Stack *stack = NULL;

    // root is added to stack only it it's not single node in a tree
    if (*root == NULL) {
        printf("\nTree is empty\n");
    } else {
        s_append(&stack, *root);
    }

    find_node(root, data, &stack);
}
