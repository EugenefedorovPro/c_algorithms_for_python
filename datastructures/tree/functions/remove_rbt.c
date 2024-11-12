#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

Node *get_sibling(Node **node, Node **parent) {
    if ((*parent) == NULL) {
        // parent is NULL when node = root
        return NULL;
    }

    Node *sibling = NULL;
    if ((*parent)->left != NULL && (*parent)->left->data == (*node)->data) {
        if ((*parent)->right != NULL) {
            sibling = (*parent)->right;
        }
    }

    if ((*parent)->right != NULL && (*parent)->right->data == (*node)->data) {
        if ((*parent)->left != NULL) {
            sibling = (*parent)->left;
        }
    }

    if (sibling == NULL) return NULL;
    printf("\nsibling = %d", sibling->data);
    return sibling;
}

void propagate_and_recolor(Node **node, Stack **stack) {
    // DB sibling's black and  DB's sibling's children are black (or null)
    printf("\npropagate and recolor from node = %d of color = %d\n", (*node)->data, (*node)->color);
    // stack keeps all nodes above the node_to_delete

    // get parent without deleting it from stack to find sibling to find
    // if sibling right or left from parent
    Node *parent = s_peek(stack);
    // get sibling
    Node *sibling = get_sibling(node, &parent);

    if (sibling == NULL || sibling->color == BLACK) {
        Node *prev_node = *node;
        while (!is_stack_empty(stack)) {
            Node *parent = s_pop(stack);
            printf("\nparent = %d\n", parent->data);

            Color prev_node_color = parent->color;

            // when parent changed, so we need to redefine siblings
            sibling = get_sibling(&prev_node, &parent);

            // recolor
            recolor_sibling_black(&prev_node, &parent, &sibling, stack);
            prev_node = parent;

            // if parent color is RED, it is just recolored to BLACK (not DB) and no up
            // propagation of recoloring
            if (prev_node_color == RED) {
                break;
            }
        }
        return;
    }

    if (sibling != NULL && sibling->color == RED) {
        Node *parent = s_pop(stack);
        recolor_sibling_red(node, &parent, &sibling, stack);
        return;
    }
}

void right_siblings_far_child_is_black(Node **parent, Node **sibling) {
    // case 5
    // DB's sibling is black
    // DB's sibling's child, which is far from DB is black
    // DB's sibling's child, which near to DB is red

    // swap color of sibling and sibling's near (left) child
    Color temp_sibling_color = (*sibling)->color;
    (*sibling)->color = (*sibling)->left->color;
    (*sibling)->left->color = temp_sibling_color;

    // Rotate at sibling node in the direction opposite to the DB node.
    Node *temp_right_child_of_siblings_left_child = (*sibling)->left->right;
    (*sibling)->left->right = NULL;

    Node *temp_sibling = *sibling;
    (*parent)->right = temp_sibling->left;

    (*parent)->right->right = temp_sibling;

    temp_sibling->left = temp_right_child_of_siblings_left_child;
}

void left_siblings_far_child_is_black(Node **parent, Node **sibling) {
    // case 5
    // DB's sibling is black
    // DB's sibling's child, which is far from DB is black
    // DB's sibling's child, which near to DB is red

    // swap color of sibling and sibling's near (left) child
    Color temp_sibling_color = (*sibling)->color;
    (*sibling)->color = (*sibling)->right->color;
    (*sibling)->right->color = temp_sibling_color;

    // Rotate at sibling node in the direction opposite to the DB node.
    Node *temp_left_child_of_siblings_right_child = (*sibling)->right->left;
    (*sibling)->right->left = NULL;

    Node *temp_sibling = *sibling;
    (*parent)->left = temp_sibling->right;

    (*parent)->left->left = temp_sibling;

    temp_sibling->right = temp_left_child_of_siblings_right_child;
}

void right_siblings_far_child_is_red(Node **parent, Node **sibling) {
    // case 6
    // DB's sibling is black
    // DB's sibling's far child is red

    // redefine sibling according to new tree structure
    printf("\ncase #6: sibling is black, sibling's far child is red");

    // swap colors of DB's parent with DB's sibling's color
    Color temp_parent_color = (*parent)->color;
    (*parent)->color = (*sibling)->color;
    (*sibling)->color = temp_parent_color;

    // Perform rotation of DB's parent in direction of DB
    Node *temp_sibling_left_child = (*sibling)->left;
    (*sibling)->left = NULL;

    Node *temp_parent = malloc(sizeof(Node));
    if (temp_parent == NULL) {
        fprintf(stderr, "memory allocation failed for temp_parent");
        return;
    }

    *temp_parent = **parent;

    **parent = **sibling;

    (*parent)->left = temp_parent;

    (*parent)->left->right = temp_sibling_left_child;

    // Change color of DB's sibling's far red child to black
    (*parent)->right->color = BLACK;
}

void left_siblings_far_child_is_red(Node **parent, Node **sibling) {
    // case 6
    // DB's sibling is black
    // DB's sibling's far child is red

    // redefine sibling according to new tree structure
    printf("\ncase #6: left sibling is black, sibling's far child is red");

    // swap colors of DB's parent with DB's sibling's color
    Color temp_parent_color = (*parent)->color;
    (*parent)->color = (*sibling)->color;
    (*sibling)->color = temp_parent_color;

    // Perform rotation of DB's parent in direction of DB
    Node *temp_sibling_left_child = (*sibling)->right;
    (*sibling)->right = NULL;

    Node *temp_parent = malloc(sizeof(Node));
    if (temp_parent == NULL) {
        fprintf(stderr, "memory allocation failed for temp_parent");
        return;
    }

    *temp_parent = **parent;

    **parent = **sibling;

    (*parent)->right = temp_parent;

    (*parent)->right->left = temp_sibling_left_child;

    // Change color of DB's sibling's far red child to black
    (*parent)->left->color = BLACK;
}

void recolor_sibling_black(Node **node, Node **parent, Node **sibling, Stack **stack) {
    printf("\nrecolor_sibling_black: node = %d, parent = %d, sibling = %d\n",
           (*node)->data,
           (*parent)->data,
           (*sibling)->data);

    // case 3
    // node_to_delete's sibling is black
    // and its children are black, then recolor
    if (((*sibling)->left == NULL || (*sibling)->left->color == BLACK) &&
        ((*sibling)->right == NULL || (*sibling)->right->color == BLACK)) {
        (*parent)->color = BLACK;
        (*sibling)->color = RED;
        return;
    }

    // case 5
    // DB's sibling is black
    // DB's sibling's child, which is far from DB is black
    // DB's sibling's child, which near to DB is red
    if ((*sibling)->color == BLACK && (*sibling)->left != NULL && (*sibling)->right != NULL &&
        (*sibling)->right->color == BLACK && (*sibling)->left->color == RED) {
        printf(
            "\ncase #5: right sibling is black, sibling's far child is black, siblings near child "
            "is "
            "red\n");

        right_siblings_far_child_is_black(parent, sibling);

        // case 6
        // DB's sibling is black
        // DB's sibling's far child is red
        // redefine sibling according to new tree structure
        sibling = &((*parent)->right);
        if ((*sibling)->color == BLACK && (*sibling)->right != NULL &&
            (*sibling)->right->color == RED) {
            right_siblings_far_child_is_red(parent, sibling);
        }
        return;
    }

    if ((*sibling)->color == BLACK && (*sibling)->left != NULL && (*sibling)->right != NULL &&
        (*sibling)->left->color == BLACK && (*sibling)->right->color == RED) {
        printf(
            "\ncase #5: left sibling is black, sibling's far child is black, siblings near child "
            "is "
            "red\n");

        left_siblings_far_child_is_black(parent, sibling);

        // case 6
        // DB's sibling is black
        // DB's sibling's far child is red
        // redefine sibling according to new tree structure
        sibling = &((*parent)->left);
        if ((*sibling)->color == BLACK && (*sibling)->left != NULL &&
            (*sibling)->left->color == RED) {
            left_siblings_far_child_is_red(parent, sibling);
        }
        return;
    }
}

void recolor_sibling_red(Node **node, Node **parent, Node **sibling, Stack **stack) {
    printf("\nrecolor_sibling_red: node = %d, parent = %d\n, sibling = %d\n",
           (*node)->data,
           (*parent)->data,
           (*sibling)->data);

    // node is right of the parent
    if ((*parent)->left->data == (*node)->data) {
        printf("node is left child of parent and sibling is red\n");
        // Swap DB’s parent’s color with DB’s sibling’s color
        Color temp_parent_color = (*parent)->color;
        (*parent)->color = (*sibling)->color;
        (*sibling)->color = temp_parent_color;

        // get grandparent
        if (is_stack_empty(stack)) {
            return;
        }

        Node *grandparent = s_pop(stack);
        printf("\ngrandparent = %d\n", grandparent->data);

        // Perform rotation at parent node in direction of DB
        Node *temp_parent = *parent;
        Node *temp_left_node_of_sibling = NULL;
        if ((*sibling)->left != NULL) {
            temp_left_node_of_sibling = (*sibling)->left;
        }

        grandparent->right = *sibling;
        (*sibling)->left = temp_parent;
        (*parent)->right = temp_left_node_of_sibling;

        printf("parent = %d", (*parent)->data);

        // add parent and grandparent to stack
        s_append(stack, *parent);
        s_append(stack, *sibling);

        recolor_sibling_black(&((*parent)->left), parent, &((*parent)->right), stack);
        return;
    }

    if ((*parent)->right->data == (*node)->data) {
        // Swap DB’s parent’s color with DB’s sibling’s color
        Color temp_parent_color = (*parent)->color;
        (*parent)->color = (*sibling)->color;
        (*sibling)->color = temp_parent_color;

        // get grandparent
        if (is_stack_empty(stack)) {
            return;
        }

        Node *grandparent = s_pop(stack);
        printf("\ngrandparent = %d\n", grandparent->data);

        // Perform rotation at parent node in direction of DB
        Node *temp_parent = *parent;
        Node *temp_left_node_of_sibling = NULL;
        if ((*sibling)->right != NULL) {
            temp_left_node_of_sibling = (*sibling)->right;
        }

        grandparent->left = *sibling;
        (*sibling)->right = temp_parent;
        (*parent)->left = temp_left_node_of_sibling;

        printf("parent = %d", (*parent)->data);

        // add parent and grandparent to stack
        s_append(stack, *parent);
        s_append(stack, *sibling);

        recolor_sibling_black(&((*parent)->right), parent, &((*parent)->left), stack);
        return;
    }
}

void rm_min_in_right_subtree(Node *node, Node *parent, int min_data) {
    printf("\nremove minimal node = %d in the right subtree\n", node->data);

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

void rm_min_in_left_subtree(Node **node, Stack **stack) {
    printf("\nremove node with minimal data = %d in left subtree\n", (*node)->data);
    /* // node = root in this case */
    /* find_node(node, min_data, stack); */

    remove_recolor(node, stack);

    // add stack in the foo
    // add remove_recolor

    /* // if top node of subtree does not have right child */
    /* if (node->right == NULL) { */
    /*     if (node->left != NULL) { */
    /*         Node *temp = node->left; */
    /*         free(node); */
    /*         if (parent != NULL) { */
    /*             parent->left = temp; */
    /*         } */
    /*         return; */
    /*     } else { */
    /*         free(node); */
    /*         if (parent != NULL) { */
    /*             parent->left = NULL; */
    /*         } */
    /*         return; */
    /*     } */
    /* } */

    /* // if top node of subtree has right child */
    /* if (node->right->data == min_data) { */
    /*     free(node->right); */
    /*     node->right = NULL; */
    /* } else { */
    /*     rm_min_in_left_subtree(node->right, parent, min_data); */
    /* } */
}

// node = top node of the right subtree
int find_min_in_right_subtree(Node *node) {
    if (node->right == NULL) {
        return node->data;
    } else {
        return find_min_in_right_subtree(node->right);
    }
}

// node = top node of the right subtree
Node *find_min_in_left_subtree(Node **node, Stack **stack) {
    if ((*node)->left == NULL) {
        return *node;
    } else {
        s_append(stack, *node);
        return find_min_in_left_subtree(&((*node)->left), stack);
    }
}

void remove_root_node(Node **node, Stack **stack) {
    // root has no children
    if ((*node)->left == NULL && (*node)->right == NULL) {
        free(*node);
        *node = NULL;
        return;
    }

    // root has one left child
    if ((*node)->left != NULL && (*node)->right == NULL) {
        printf("\nroot to remove has only left child\n");
        Node *temp = (*node)->left;
        free(*node);
        *node = temp;
        (*node)->color = BLACK;
        return;
    }

    // root has one right child
    if ((*node)->right != NULL && (*node)->left == NULL) {
        printf("\nroot to remove has only right child\n");
        Node *temp = (*node)->right;
        free(*node);
        *node = temp;
        (*node)->color = BLACK;
        return;
    }

    // root has two children
    if ((*node)->right != NULL && (*node)->left != NULL) {
        printf("\nroot to remove has two children\n");
        // get min in left or max in right

        free_stack(stack);

        Node *min_data_left = find_min_in_left_subtree(node, stack);
        /* int min_data_right = find_min_in_right_subtree(*node); */
        printf("\nmin_data_left = %d", min_data_left->data);
        /* printf("\nmin_data_right = %d", min_data_right); */

        printf("\nnew root data = %d\n", (*node)->data);
        print_all_stack(stack);

        // node = next node after the new root in a left subtree
        rm_min_in_left_subtree(node, stack);
        (*node)->data = min_data_left->data;

        return;
    }

    return;
}

void remove_recolor(Node **node, Stack **stack) {
    printf("\nnode to be deleted = %d\n", (*node)->data);
    print_all_stack(stack);

    if (is_stack_empty(stack)) {
        printf("\nnode to remove is a root node\n");
        remove_root_node(node, stack);
        return;
    }

    // node has no children
    if ((*node)->left == NULL && (*node)->right == NULL) {
        printf("\nleft node with no children\n");
        // *** if red leaf node just delete it
        if ((*node)->color == RED) {
            free(*node);
            *node = NULL;

            // get parent
            Node *parent = s_pop(stack);
            // set NULL link from parent to removed node
            parent->left = NULL;

            return;
        }

        /* // other cases */
        /* propagate_and_recolor(node, stack); */

        /* // delete node_to_delete */
        /* free(*node); */
        /* *node = NULL; */

        /* return; */
    }

    // node has one right child
    if ((*node)->right != NULL && (*node)->left == NULL) {
        propagate_and_recolor(node, stack);

        // delete node
        Node *temp = (*node)->right;
        free(*node);
        *node = temp;
        return;
    }

    // node has one left child
    if ((*node)->left != NULL && (*node)->right == NULL) {
        propagate_and_recolor(node, stack);

        Node *temp = (*node)->left;
        free(*node);
        *node = temp;
        return;
    }

    // node has two children
    if ((*node)->left != NULL && (*node)->right != NULL) {
        // get parent of the node

        /* Node *parent = s_peek(stack); */

        /* // no propagate and recolor as node_to_del is a red leaf node */

        /* // node is a right node of the parent */
        /* if (parent->right->data == (*node)->data) { */
        /*     printf("\nparent->right->data\n"); */
        /*     int min_data = find_min_in_right_subtree(((*node)->right)); */
        /*     (*node)->data = min_data; */
        /*     rm_min_in_right_subtree((*node)->right, *node, min_data); */
        /*     return; */
        /* } */

        // node is a left node of the parent
        /* if (parent->left->data == (*node)->data) { */
        printf("\nparent->left->data\n");

        /* free_stack(stack); */

        Node *min_data_node = find_min_in_left_subtree(node, stack);
        int min_data = min_data_node->data;
        printf("\nmin_data = %d\n", min_data_node->data);


        remove_recolor(&min_data_node, stack);
        // change node data for min data of the left subtree
        (*node)->data = min_data;
        return;
        /* } */
    }
}

void find_node(Node **node, int data, Stack **stack) {
    if ((*node) == NULL) {
        printf("\nTree does not contain %d\n", data);
        return;
    }
    if (data == (*node)->data) {
        remove_recolor(node, stack);
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

    if (*root == NULL) {
        printf("\nTree is empty\n");
    }

    find_node(root, data, &stack);
}
