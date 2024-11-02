#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void right_left_rotation(Node **grandparent, Node **parent, Stack **stack) {
    printf("\nright_left_rotation, grandparent = %d, parent = %d\n",
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

    // shift from left to right
    Node *new_parent = (*parent)->left;

    *temp = **parent;
    temp->left = NULL;

    (*grandparent)->right = new_parent;

    if (new_parent->right == NULL) {
        new_parent->right = temp;
    } else if (new_parent->right->right == NULL) {
        new_parent->right->right = temp;
    } else if (new_parent->right->right->right == NULL) {
        new_parent->right->right->right = temp;
    }

    // change grandparent (root)

    Node *temp_old_grandp = malloc(sizeof(Node));
    if (temp_old_grandp == NULL) {
        fprintf(stderr, "memory allocation failed for temp");
        return;
    }

    *temp_old_grandp = **grandparent;
    temp_old_grandp->right = NULL;

    **grandparent = *new_parent;
    (*grandparent)->color = BLACK;

    if ((*grandparent)->left == NULL) {
        (*grandparent)->left = temp_old_grandp;
        (*grandparent)->left->color = RED;
    } else if ((*grandparent)->left->left == NULL) {
        (*grandparent)->left->left = temp_old_grandp;
        (*grandparent)->left->left->color = RED;

    } else if ((*grandparent)->left->left->left == NULL) {
        (*grandparent)->left->left->left = temp_old_grandp;
        (*grandparent)->left->left->left->color = RED;
    }

    // new in right - left
    /* if (((*grandparent)->right->right != NULL && (*grandparent)->right->right->color == BLACK) ||
     */
    /*     ((*grandparent)->right->left != NULL && (*grandparent)->right->left->color == BLACK)) {
     */
    /*     if ((*grandparent)->left != NULL) { */
    /*         (*grandparent)->left->color = BLACK; */
    /*     } */
    /* } */

    /* // right - left rotation */
    /* printf("\ngrandparent = %d\n", (*grandparent)->data); */
    /* if ((*grandparent)->right->right != NULL && (*grandparent)->right->right->right != NULL && */
    /*     (*grandparent)->right->right->right->color == BLACK) { */
    /*     if ((*grandparent)->right->left != NULL) { */
    /*         (*grandparent)->right->left->color = BLACK; */
    /*     } */
    /* } */

    /* if ((*grandparent)->left->left != NULL && (*grandparent)->left->left->left != NULL && */
    /*     (*grandparent)->left->left->left->color == BLACK) { */
    /*     if ((*grandparent)->left->right != NULL) { */
    /*         (*grandparent)->left->right->color = BLACK; */
    /*     } */
    /* } */

    s_append(stack, *grandparent);  // ???
    check_above(grandparent, temp_old_grandp->data, stack);
}

void left_right_rotation(Node **grandparent, Node **parent, Stack **stack) {
    printf("\nleft_right_rotation, grandparent = %d, parent = %d\n",
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

    // shift from left to right
    Node *new_parent = (*parent)->right;

    *temp = **parent;
    temp->right = NULL;

    (*grandparent)->left = new_parent;

    if (new_parent->left == NULL) {
        new_parent->left = temp;
    } else if (new_parent->left->left == NULL) {
        new_parent->left->left = temp;
    } else if (new_parent->left->left->left == NULL) {
        new_parent->left->left->left = temp;
    }

    // change grandparent (root)

    Node *temp_old_grandp = malloc(sizeof(Node));
    if (temp_old_grandp == NULL) {
        fprintf(stderr, "memory allocation failed for temp");
        return;
    }

    *temp_old_grandp = **grandparent;
    temp_old_grandp->left = NULL;

    **grandparent = *new_parent;
    (*grandparent)->color = BLACK;

    if ((*grandparent)->right == NULL) {
        (*grandparent)->right = temp_old_grandp;
        (*grandparent)->right->color = RED;
    } else if ((*grandparent)->right->right == NULL) {
        (*grandparent)->right->right = temp_old_grandp;
        (*grandparent)->right->right->color = RED;

    } else if ((*grandparent)->right->right->right == NULL) {
        (*grandparent)->right->right->right = temp_old_grandp;
        (*grandparent)->right->right->right->color = RED;
    }

    /* // new in left - left */
    /* if (((*grandparent)->left->left != NULL && (*grandparent)->left->left->color == BLACK) || */
    /*     ((*grandparent)->left->right != NULL && (*grandparent)->left->right->color == BLACK)) {
     */
    /*     if ((*grandparent)->right != NULL) { */
    /*         (*grandparent)->right->color = BLACK; */
    /*     } */
    /* } */

    /* if ((*grandparent)->left->left != NULL && (*grandparent)->left->left->left != NULL && */
    /*     (*grandparent)->left->left->left->color == BLACK) { */
    /*     if ((*grandparent)->left->right != NULL) { */
    /*         (*grandparent)->left->right->color = BLACK; */
    /*     } */
    /* } */

    /* if ((*grandparent)->right->right != NULL && (*grandparent)->right->right->right != NULL && */
    /*     (*grandparent)->right->right->right->color == BLACK) { */
    /*     if ((*grandparent)->right->left != NULL) { */
    /*         (*grandparent)->right->left->color = BLACK; */
    /*     } */
    /* } */

    s_append(stack, (*grandparent));  // ???
    check_above(grandparent, temp_old_grandp->data, stack);
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

    /* if ((*grandparent)->left->left != NULL && */
    /*     (*grandparent)->left->left->color == BLACK) {  // ????????????????????????? */
    /*     (*grandparent)->right->color = BLACK; */
    /* } */
    (*grandparent)->right->color = RED;

    /* /1* printf("\ngrandparent in left_left = %d\n", (*grandparent)->data); *1/ */
    /* if (((*grandparent)->left->left != NULL && (*grandparent)->left->left->color == BLACK) || */
    /*     (((*grandparent)->left->right != NULL) && (*grandparent)->left->right->color == BLACK)) {
     */
    /*     if ((*grandparent)->right != NULL) { */
    /*         (*grandparent)->right->color = BLACK;  // ????? */
    /*     } */
    /* } else { */
    /*     if ((*grandparent)->right != NULL) { */
    /*         (*grandparent)->right->color = RED;  // ????? */
    /*         /1* } *1/ */
    /*     } */
    /* } */

    /* free(*parent); */
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

    /* printf("\nright_uncle_black right - right rotation\n"); */
    (*grandparent)->left->color = RED;
    (*grandparent)->color = BLACK;

    /* if ((*grandparent)->right->right != NULL && */
    /*     (*grandparent)->right->right->color == BLACK) {  // ????????????????????????? */
    /*     (*grandparent)->left->color = BLACK; */
    /* } */
    (*grandparent)->left->color = RED;

    /* if (((*grandparent)->right->right != NULL && (*grandparent)->right->right->color == BLACK) ||
     */
    /*     (((*grandparent)->right->left != NULL) && (*grandparent)->right->left->color == BLACK)) {
     */
    /*     if ((*grandparent)->left != NULL) { */
    /*         (*grandparent)->left->color = BLACK;  // ????? */
    /*     } */
    /* } else { */
    /*     if ((*grandparent)->left != NULL) { */
    /*         (*grandparent)->left->color = RED;  // ????? */
    /*         /1* } *1/ */
    /*     } */
    /* } */

    /* free(*parent); */
}

void check_above(Node **node, int data, Stack **stack) {
    if (*node == NULL) {
        return;
    }

    if (data < (*node)->data) {
        if ((*node)->left->data == data) {
            Node *base_node = (*node)->left;
            /* printf("\n base_node = %d\n", base_node->data); */
            balance(stack, &base_node);
        } else {
            /* s_append(stack, *node); */
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

