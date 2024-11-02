#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void right_left_rotation(Node **grandparent, Node **parent, Stack **stack) {
    printf("\nright_left_rotation, grandparent = %d, parent = %d\n",
           (*grandparent)->data,
           (*parent)->data);

    Node *temp_parent = malloc(sizeof(Node));
    if (temp_parent == NULL) {
        fprintf(stderr, "memory allocation failed for temp_parent");
        return;
    }

    // shift from left to right
    Node *new_parent = (*parent)->left;
    Node *node_right_child = NULL;
    if ((*parent)->left->right != NULL) {
        node_right_child = (*parent)->left->right;
    }
    new_parent->right = NULL;

    *temp_parent = **parent;
    temp_parent->left = NULL;
    if (node_right_child != NULL) {
        temp_parent->left = node_right_child;
    }

    (*grandparent)->right = new_parent;
    new_parent->right = temp_parent;

    free(*parent);

    right_right_rotation(grandparent, &new_parent);
}

void left_right_rotation(Node **grandparent, Node **parent, Stack **stack) {
    printf("\nleft_right_rotation, grandparent = %d, parent = %d\n",
           (*grandparent)->data,
           (*parent)->data);

    Node *temp_parent = malloc(sizeof(Node));
    if (temp_parent == NULL) {
        fprintf(stderr, "memory allocation failed for temp_parent");
        return;
    }

    // shift from left to right
    Node *new_parent = (*parent)->right;
    Node *node_left_child = NULL;
    if ((*parent)->right->left != NULL) {
        node_left_child = (*parent)->right->left;
    }
    new_parent->left = NULL;

    *temp_parent = **parent;
    temp_parent->right = NULL;
    if (node_left_child != NULL) {
        temp_parent->right = node_left_child;
    }

    (*grandparent)->left = new_parent;
    new_parent->left = temp_parent;

    free(*parent);

    left_left_rotation(grandparent, &new_parent);
}

void left_left_rotation(Node **grandparent, Node **parent) {
    printf("\nleft_left_rotation, grandparent = %d, parent = %d\n",
           (*grandparent)->data,
           (*parent)->data);

    Node *sibling = NULL;
    if ((*parent)->right != NULL) {
        sibling = (*parent)->right;
    }

    Node *temp = malloc(sizeof(Node));
    if (temp == NULL) {
        fprintf(stderr, "memory allocation failed for temp");
        return;
    }

    *temp = **grandparent;

    if (sibling != NULL) {
        temp->left = sibling;
    } else {
        temp->left = NULL;
    }

    if (temp->right != NULL) {
        (*parent)->right = NULL;
    }

    **grandparent = **parent;

    (*grandparent)->right = temp;

    (*grandparent)->right->color = RED;
    (*grandparent)->color = BLACK;
}

void right_right_rotation(Node **grandparent, Node **parent) {
    printf("\nright_right_rotation, grandparent = %d, parent = %d\n",
           (*grandparent)->data,
           (*parent)->data);

    Node *sibling = NULL;
    if ((*parent)->left != NULL) {
        sibling = (*parent)->left;
    }

    Node *temp = malloc(sizeof(Node));
    if (temp == NULL) {
        fprintf(stderr, "memory allocation failed for temp");
        return;
        }
        *temp = **grandparent;

    if (sibling != NULL) {
        temp->right = sibling;
    } else {
        temp->right = NULL;
    }

    if (temp->left != NULL) {
        (*parent)->left = NULL;
    }

    **grandparent = **parent;
    (*grandparent)->left = temp;

    (*grandparent)->left->color = RED;
    (*grandparent)->color = BLACK;
}

void check_above(Node **node, int data, Stack **stack) {
    if (*node == NULL) {
        return;
    }

    if (data < (*node)->data) {
        if ((*node)->left->data == data) {
            Node *base_node = (*node)->left;
            balance(stack, &base_node);
        } else {
            s_append(stack, (*node)->left);
            check_above(&((*node)->left), data, stack);
        }
    }
    if (data > (*node)->data) {
        if ((*node)->right->data == data) {
            Node *base_node = (*node)->right;
            balance(stack, &base_node);

        } else {
            s_append(stack, (*node)->right);
            check_above(&((*node)->right), data, stack);
        }
    }
}

void left_uncle_red(Node **parent, Node **grandparent, Node **uncle, Stack **stack) {
    printf(
        "\nleft_uncle_red, grandparent = %d, parent = %d\n", (*grandparent)->data, (*parent)->data);

    (*uncle)->color = BLACK;
    (*parent)->color = BLACK;

    // if grandparent is not root, color it red
    if (!is_stack_empty(stack)) {
        (*grandparent)->color = RED;
        if (is_stack_empty(stack)) {
            return;
        }
        Node *parent_of_grandparent = s_pop(stack);
        if (is_stack_empty(stack)) {
            return;
        }
        Node *grandparent_of_grandparent = s_pop(stack);

        // add grandparent_of_grandparent to stack
        s_append(stack, grandparent_of_grandparent);
        check_above(&grandparent_of_grandparent, (*grandparent)->data, stack);
    }
}

void right_uncle_red(Node **parent, Node **grandparent, Stack **stack) {
    printf("\nright_uncle_red, grandparent = %d, parent = %d\n",
           (*grandparent)->data,
           (*parent)->data);
    Node *uncle = (*grandparent)->left;

    uncle->color = BLACK;
    (*parent)->color = BLACK;

    // if grandparent is not root, color it red
    if (!is_stack_empty(stack)) {
        (*grandparent)->color = RED;
        if (is_stack_empty(stack)) {
            return;
        }
        Node *parent_of_grandparent = s_pop(stack);
        if (is_stack_empty(stack)) {
            return;
        }
        Node *grandparent_of_grandparent = s_pop(stack);

        // add grandparent_of_grandparent to stack
        s_append(stack, grandparent_of_grandparent);
        check_above(&grandparent_of_grandparent, (*grandparent)->data, stack);
    }
}

void right_uncle_black(Node **parent, Node **grandparent, Stack **stack) {
    if ((*grandparent)->right != NULL && (*grandparent)->right->data == (*parent)->data) {
        right_right_rotation(grandparent, parent);
        return;
    }

    if ((*grandparent)->left != NULL && (*grandparent)->left->data == (*parent)->data) {
        left_right_rotation(grandparent, parent, stack);
        return;
    }
}

void left_uncle_black(Node **parent, Node **grandparent, Stack **stack) {
    if ((*grandparent)->left != NULL && (*grandparent)->left->data == (*parent)->data) {
        left_left_rotation(grandparent, parent);
        return;
    }
    if ((*grandparent)->right != NULL && (*grandparent)->right->data == (*parent)->data) {
        right_left_rotation(grandparent, parent, stack);
        return;
    }
}

void balance(Stack **stack, Node **node) {
    if (is_stack_empty(stack)) {
        return;
    }

    Node *parent = s_pop(stack);

    if (parent->color == RED) {
        if (is_stack_empty(stack)) {
            return;
        }

        Node *grandparent = s_pop(stack);

        Node *uncle = NULL;

        // define uncle for node in the right subtree
        if (parent->right != NULL && parent->right->data == (*node)->data) {
            if (grandparent->left != NULL && grandparent->left->data != parent->data) {
                uncle = grandparent->left;
            } else {
                if (grandparent->right != NULL && grandparent->right->data != parent->data) {
                    uncle = grandparent->right;
                }
            }
        }

        // define uncle for node in the left subtree
        if (parent->left != NULL && parent->left->data == (*node)->data) {
            if (grandparent->right != NULL && grandparent->right->data != parent->data) {
                uncle = grandparent->right;
            } else {
                if (grandparent->left != NULL && grandparent->left->data != parent->data) {
                    uncle = grandparent->left;
                }
            }
        }

        // case parent = red, uncle = red on the left subtree
        if (grandparent->right != NULL && uncle != NULL && uncle->color == RED) {
            left_uncle_red(&parent, &grandparent, &uncle, stack);
            return;
        }

        // case parent = red, uncle = red on the right subtree
        if (grandparent->left != NULL && uncle != NULL && uncle->color == RED) {
            right_uncle_red(&parent, &grandparent, stack);
            return;
        }

        // uncle is black or null on the left subtree
        if (uncle == NULL || uncle->color == BLACK) {
            // right - right
            if (parent->left != NULL && parent->left->data == (*node)->data) {
                left_uncle_black(&parent, &grandparent, stack);
                return;
            }
        }

        // uncle is black or null on the right subtree
        if (uncle == NULL || uncle->color == BLACK) {
            // right - right
            if (parent->right != NULL && parent->right->data == (*node)->data) {
                right_uncle_black(&parent, &grandparent, stack);
                return;
            }
        }
    }
}

void insert_recurse(Node **node, int data, Stack **stack) {
    if (*node == NULL) {
        *node = create_node(data, BLACK);
        return;
    }

    if (data < (*node)->data) {
        if ((*node)->left == NULL) {
            (*node)->left = create_node(data, RED);
            Node *new_node = (*node)->left;
            balance(stack, &new_node);
            return;

        } else {
            s_append(stack, (*node)->left);
            insert_recurse(&((*node)->left), data, stack);
        }
    }

    if (data > (*node)->data) {
        if ((*node)->right == NULL) {
            (*node)->right = create_node(data, RED);
            Node *new_node = (*node)->right;
            balance(stack, &new_node);
            return;

        } else {
            s_append(stack, (*node)->right);
            insert_recurse(&((*node)->right), data, stack);
        }
    }
}

void insert_rbt(Node **root, int data) {
    Stack *stack = NULL;
    // root is added to stack only it it's not single node in a tree
    if (*root != NULL) {
        s_append(&stack, *root);
    }
    insert_recurse(root, data, &stack);
}
