#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void rm_min_in_right_subtree(Node *node, Node *parent, int min_data) {
    if (node == NULL) return;

    // if top node of subtree does not have left child
    if (node->left == NULL) {
        if (node->right != NULL) {
            Node *temp = node->right;
            free(node);
            if (parent != NULL) {
                parent->right = temp;
            }
            return;
        } else {
            free(node);
            if (parent != NULL) {
                parent->right = NULL;
            }
            return;
        }
    }

    // if top node of subtree has left child
    if (node->left->data == min_data) {
        free(node->left);
        node->left = NULL;
    } else {
        rm_min_in_right_subtree(node->left, parent, min_data);
    }
}

void rm_min_in_left_subtree(Node *node, Node *parent, int min_data) {
    if (node == NULL) return;
    // if top node of subtree does not have right child
    if (node->right == NULL) {
        if (node->left != NULL) {
            Node *temp = node->left;
            free(node);
            if (parent != NULL) {
                parent->left = temp;
            }
            return;
        } else {
            free(node);
            if (parent != NULL) {
                parent->left = NULL;
            }
            return;
        }
    }

    // if top node of subtree has right child
    if (node->right->data == min_data) {
        free(node->right);
        node->right = NULL;
    } else {
        rm_min_in_left_subtree(node->right, parent, min_data);
    }
}

// node = top node of the right subtree
int find_min_in_right_subtree(Node *node) {
    if (node->left == NULL) {
        return node->data;
    } else {
        return find_min_in_right_subtree(node->left);
    }
}

// node = top node of the right subtree
int find_min_in_left_subtree(Node *node) {
    if (node->right == NULL) {
        return node->data;
    } else {
        return find_min_in_left_subtree(node->right);
    }
}

void simple_remove(Node **node, Stack **stack) {
    printf("\nnode to be deleted = %d\n", (*node)->data);

    // node has no children
    if ((*node)->left == NULL && (*node)->right == NULL) {
        printf("\nnode has no children\n");
        // *** if red leaf node just delete it
        if ((*node)->color == RED) {
            free(*node);
            *node = NULL;
        }
        return;
    }

    // node has one right child
    if ((*node)->right != NULL && (*node)->left == NULL) {
        Node *temp = (*node)->right;
        free(*node);
        *node = temp;
        return;
    }

    // node has one left child
    if ((*node)->left != NULL && (*node)->right == NULL) {
        Node *temp = (*node)->left;
        free(*node);
        *node = temp;
        return;
    }

    // node has two children
    if ((*node)->left != NULL && (*node)->right != NULL) {
        // get parent of the node
        if (is_stack_empty(stack)) {
            return;
        }

        Node *parent = s_pop(stack);

        // node is a right node of the parent
        if (parent->right->data == (*node)->data) {
            printf("\nparent->right->data\n");
            int min_data = find_min_in_right_subtree(((*node)->right));
            (*node)->data = min_data;
            rm_min_in_right_subtree((*node)->right, *node, min_data);
            return;
        }

        // node is a left node of the parent
        if (parent->left->data == (*node)->data) {
            printf("\nparent->left->data\n");
            int min_data = find_min_in_left_subtree(((*node)->left));
            printf("\nmin_data = %d\n", min_data);
            (*node)->data = min_data;
            rm_min_in_left_subtree((*node)->left, *node, min_data);
            return;
        }
    }
}

void find_node(Node **node, int data, Stack **stack) {
    if ((*node) == NULL) {
        printf("\nTree does not contain %d\n", data);
        return;
    }
    if (data == (*node)->data) {
        simple_remove(node, stack);
        return;
    }

    if (data > (*node)->data) {
        s_append(stack, *node);
        find_node(&((*node)->right), data, stack);
    }

    if (data < (*node)->data) {
        s_append(stack, *node);
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
