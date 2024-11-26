#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

int double_black;

/* enum NodePositionToParent { */
/*     RIGHT = 1, */
/*     LEFT = 0, */
/* }; */

void null_link_from_parent_of_removed_node(int node_position_to_parent, Node *parent) {
    if (node_position_to_parent == LEFT) {
        parent->left = NULL;
    } else {
        parent->right = NULL;
    }
}

int get_node_position_to_parent(Node *node, Node *parent) {
    int node_position_to_parent = -1;
    if (parent->left && parent->left == node) {
        node_position_to_parent = LEFT;
    }
    if (parent->right && parent->right == node) {
        node_position_to_parent = RIGHT;
    }
    printf("\nnode = %d, position = %d to parent = %d\n",
           node->key,
           node_position_to_parent,
           parent->key);
    return node_position_to_parent;
}

Node *get_sibling(Node **node, Node **parent) {
    if ((*parent) == NULL) {
        // parent is NULL when node = root
        return NULL;
    }

    Node *sibling = NULL;
    if ((*parent)->left != NULL && (*parent)->left->key == (*node)->key) {
        if ((*parent)->right != NULL) {
            sibling = (*parent)->right;
        }
    }

    if ((*parent)->right != NULL && (*parent)->right->key == (*node)->key) {
        if ((*parent)->left != NULL) {
            sibling = (*parent)->left;
        }
    }

    if (sibling == NULL) return NULL;
    printf("\nsibling = %d\n", sibling->key);
    return sibling;
}

void propagate_and_recolor(Node **parent,
                           Node **sibling,
                           Stack **stack,
                           int node_position_to_parent) {
    // DB sibling's black and  DB's sibling's children are black (or null)
    printf(
        "\npropagate and recolor from parent = %d of color = %d and sibling = %d of color = %d\n",
        (*parent)->key,
        (*parent)->color,
        (*sibling)->key,
        (*sibling)->color);

    // stack keeps all nodes above the parent of the node_to_delete

    if ((*sibling) == NULL || (*sibling)->color == BLACK) {
        printf("\nsibling color is black\n");

        Node *prev_node = *parent;  // save parent

        Color prev_parent_color = (*parent)->color;

        // recolor
        recolor_sibling_black(parent, sibling, stack, node_position_to_parent);

        // if double_black = 0, stop propagation and exit program as the tree is balanced
        if (double_black == 0) {
            return;
        }

        // if no upward propagation, break while
        if (is_stack_empty(stack)) {
            return;
        }

        // if parent color is RED, it is just recolored to BLACK (not DB) and no up
        // propagation of recoloring
        if (prev_parent_color == RED) {
            return;
        }

        *parent = s_pop(stack);
        printf("\nparent = %d\n", (*parent)->key);

        // when parent changed, so we need to redefine siblings
        *sibling = get_sibling(&prev_node, parent);
        node_position_to_parent = get_node_position_to_parent(prev_node, *parent);

        // renew prev_node with new parent
        prev_node = *parent;

        // it does the same as inside while even if condition in while is false - ?????
        /* recolor_sibling_black(parent, sibling, stack, node_position_to_parent); */
        propagate_and_recolor(parent, sibling, stack, node_position_to_parent);
        return;
    }

    if ((*sibling) != NULL && (*sibling)->color == RED) {
        printf("\nsibling color is red\n");
        recolor_sibling_red(parent, sibling, stack, node_position_to_parent);
        return;
    }
}

void right_siblings_far_child_is_black(Node **parent, Node **sibling) {
    // case 5
    // DB's sibling is black
    // DB's sibling's child, which is far from DB is black
    // DB's sibling's child, which near to DB is red

    printf("\nright_siblings_far_child_is_black: parent = %d, sibling = %d\n",
           (*parent)->key,
           (*sibling)->key);

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

    // if double_black = 0, stop propagation and exit program as the tree is balanced
    double_black = 0;
}

void left_siblings_far_child_is_black(Node **parent, Node **sibling) {
    // case 5
    // DB's sibling is black
    // DB's sibling's child, which is far from DB is black
    // DB's sibling's child, which near to DB is red
    printf("\nleft_siblings_far_child_is_black: parent = %d, sibling = %d\n",
           (*parent)->key,
           (*sibling)->key);

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

    // if double_black = 0, stop propagation and exit program as the tree is balanced
    double_black = 0;
}

void right_siblings_far_child_is_red(Node **parent, Node **sibling) {
    // case 6
    // DB's sibling is black
    // DB's sibling's far child is red

    // redefine sibling according to new tree structure
    printf("\ncase #6: right sibling is black, sibling's = %d far child is red", (*sibling)->key);

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
    printf("\nparent = %d, sibling = %d\n", (*parent)->key, (*sibling)->key);

    // swap colors of DB's parent with DB's sibling's color
    Color temp_parent_color = (*parent)->color;
    (*parent)->color = (*sibling)->color;
    (*sibling)->color = temp_parent_color;

    // Perform rotation of DB's parent in direction of DB
    Node *temp_sibling_right_child = (*sibling)->right;
    (*sibling)->right = NULL;

    Node *temp_parent = malloc(sizeof(Node));
    if (temp_parent == NULL) {
        fprintf(stderr, "memory allocation failed for temp_parent");
        return;
    }

    *temp_parent = **parent;

    **parent = **sibling;

    (*parent)->right = temp_parent;
    (*parent)->right->left = temp_sibling_right_child;
    // Change color of DB's sibling's far red child to black
    (*parent)->left->color = BLACK;
}

void recolor_sibling_black(Node **parent,
                           Node **sibling,
                           Stack **stack,
                           int node_position_to_parent) {
    printf("\nrecolor_sibling_black: parent = %d, sibling = %d, node_position_to_parent = %d\n",
           (*parent)->key,
           (*sibling)->key,
           node_position_to_parent);

    // case 3
    // node_to_delete's sibling is black
    // and its children are black, then recolor
    if (((*sibling)->left == NULL || (*sibling)->left->color == BLACK) &&
        ((*sibling)->right == NULL || (*sibling)->right->color == BLACK)) {
        printf("\ncase #3: node_to_delete's sibling is black or NULL and its children are black\n");
        (*parent)->color = BLACK;
        (*sibling)->color = RED;
        return;
    }

    // case 5
    // DB's sibling is black
    // DB's sibling's child, which is far from DB is black
    // DB's sibling's child, which near to DB is red

    if (node_position_to_parent == LEFT &&
        ((*sibling)->right == NULL || (*sibling)->right->color == BLACK) && (*sibling)->left &&
        (*sibling)->left->color == RED) {
        printf(
            "\ncase #5: right sibling is black, sibling's far child is black, siblings near child "
            "is red\n");

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

    if (node_position_to_parent == RIGHT &&
        ((*sibling)->left == NULL || (*sibling)->left->color == BLACK) && (*sibling)->right &&
        (*sibling)->right->color == RED) {
        printf(
            "\ncase #5: left sibling is black, sibling's far child is black, siblings near child "
            "is red\n");

        left_siblings_far_child_is_black(parent, sibling);

        // case 6
        // DB's sibling is black
        // DB's sibling's far child is red
        // redefine sibling according to new tree structure
        sibling = &((*parent)->left);
        left_siblings_far_child_is_red(parent, sibling);
        return;
    }

    if ((node_position_to_parent = RIGHT && (*sibling)->left && (*sibling)->left->color == RED) ||
        (node_position_to_parent == LEFT && (*sibling)->right && (*sibling)->right->color == RED)) {
        // case 6
        // DB's sibling is black
        // DB's sibling's far child is red

        // redefine sibling according to new tree structure
        if ((*parent)->right && (*parent)->right->key == (*sibling)->key) {
            right_siblings_far_child_is_red(parent, sibling);
        } else {
            left_siblings_far_child_is_red(parent, sibling);
        }

        // if double_black = 0, stop propagation and exit program as the tree is balanced
        double_black = 0;

        return;
    }
}

void recolor_sibling_red(Node **parent,
                         Node **sibling,
                         Stack **stack,
                         int node_position_to_parent) {
    printf("\nrecolor_sibling_red: parent = %d color = %d, sibling = %d, color = %d\n",
           (*parent)->key,
           (*parent)->color,
           (*sibling)->key,
           (*sibling)->color);

    // removed node is right of the parent
    if (node_position_to_parent == LEFT) {
        // TASK: separate two flows: with grandparent - without grandparent
        printf("left node is left child of parent and sibling is red\n");
        // Swap DB’s parent’s color with DB’s sibling’s color
        Color temp_parent_color = (*parent)->color;
        (*parent)->color = (*sibling)->color;
        (*sibling)->color = temp_parent_color;

        // get grandparent
        Node *grandparent = NULL;
        if (!is_stack_empty(stack)) {
            grandparent = s_pop(stack);
            printf("\ngrandparent = %d\n", grandparent->key);
        } else {
            printf("\nno grandparent\n");
        }

        // Perform rotation at parent node in direction of DB
        // create shallow copy of sibling's left node
        Node *temp_left_node_of_sibling = NULL;
        if ((*sibling)->left != NULL) {
            temp_left_node_of_sibling = (*sibling)->left;
            (*sibling)->left = NULL;
        }

        // create deep copy of temp_parent
        Node *temp_parent = malloc(sizeof(Node));
        if (!temp_parent) return;
        temp_parent->key = (*parent)->key;
        temp_parent->color = (*parent)->color;
        temp_parent->left = (*parent)->left;
        temp_parent->right = temp_left_node_of_sibling;

        if (grandparent && grandparent->left->key == (*parent)->key) {
            grandparent->left = *sibling;
            (*sibling)->left = temp_parent;
        }
        if (grandparent && grandparent->right->key == (*parent)->key) {
            grandparent->right = *sibling;
            (*sibling)->left = temp_parent;
        }

        if (!grandparent) {
            **parent = **sibling;
            (*parent)->left = temp_parent;
            (*parent)->left->right = temp_left_node_of_sibling;
        }

        // free parent
        if (grandparent) {
            free((*parent)->value);
            free(*parent);
            *parent = NULL;
        }

        // add parent and grandparent to stack
        s_append(stack, temp_parent);
        s_append(stack, grandparent);

        recolor_sibling_black(&temp_parent, &(temp_parent->right), stack, node_position_to_parent);
        return;
    }

    if (node_position_to_parent == RIGHT) {
        printf("right node is right child of parent and sibling is red\n");
        // Swap DB’s parent’s color with DB’s sibling’s color
        Color temp_parent_color = (*parent)->color;
        (*parent)->color = (*sibling)->color;
        (*sibling)->color = temp_parent_color;

        // get grandparent
        Node *grandparent = NULL;
        if (!is_stack_empty(stack)) {
            grandparent = s_pop(stack);
            printf("\ngrandparent = %d\n", grandparent->key);
        } else {
            printf("\nno grandparent\n");
        }

        // Perform rotation at parent node in direction of DB
        // create shallow copy of sibling's left node
        Node *temp_right_node_of_sibling = NULL;
        if ((*sibling)->right != NULL) {
            temp_right_node_of_sibling = (*sibling)->right;
            (*sibling)->right = NULL;
        }

        // create deep copy of temp_parent
        Node *temp_parent = malloc(sizeof(Node));
        if (!temp_parent) return;
        temp_parent->key = (*parent)->key;
        temp_parent->color = (*parent)->color;
        temp_parent->right = (*parent)->right;
        temp_parent->left = temp_right_node_of_sibling;

        if (grandparent && grandparent->left->key == (*parent)->key) {
            grandparent->left = *sibling;
            (*sibling)->right = temp_parent;
        }
        if (grandparent && grandparent->right->key == (*parent)->key) {
            grandparent->right = *sibling;
            (*sibling)->right = temp_parent;
        }

        if (!grandparent) {
            **parent = **sibling;
            (*parent)->right = temp_parent;
            (*parent)->right->left = temp_right_node_of_sibling;
        }

        // free parent
        if (grandparent) {
            free((*parent)->value);
            free(*parent);
            *parent = NULL;
        }

        // add parent and grandparent to stack
        s_append(stack, temp_parent);
        s_append(stack, grandparent);

        recolor_sibling_black(&temp_parent, &(temp_parent->left), stack, node_position_to_parent);
        return;
    }
}

void rm_min_in_right_subtree(Node *node, Node *parent, int min_data) {
    printf("\nremove minimal node = %d in the right subtree\n", node->key);

    if (node == NULL) return;

    // if top node of subtree does not have left child
    if (node->left == NULL) {
        if (node->right != NULL) {
            Node *temp = node->right;

            free(node->value);
            free(node);
            if (parent != NULL) {
                parent->right = temp;
            }
            return;
        } else {
            free(node->value);
            free(node);
            if (parent != NULL) {
                parent->right = NULL;
            }
            return;
        }
    }

    // if top node of subtree has left child
    if (node->left->key == min_data) {
        free(node->left->value);
        free(node->left);
        node->left = NULL;
    } else {
        rm_min_in_right_subtree(node->left, parent, min_data);
    }
}

// node = top node of the left subtree
Node *find_max_in_left_subtree(Node **node, Stack **stack) {
    if ((*node)->right == NULL) {
        return *node;
    } else {
        s_append(stack, *node);
        return find_max_in_left_subtree(&((*node)->right), stack);
    }
}

// node = top node of the right subtree
Node *find_min_in_right_subtree(Node **node, Stack **stack) {
    if ((*node)->left == NULL) {
        return *node;
    } else {
        s_append(stack, *node);
        return find_max_in_left_subtree(&((*node)->left), stack);
    }
}

void remove_root_node(Node **node, Stack **stack) {
    // root has no children
    if ((*node)->left == NULL && (*node)->right == NULL) {
        free((*node)->value);
        free(*node);
        *node = NULL;
        return;
    }

    // root has one left child
    if ((*node)->left != NULL && (*node)->right == NULL) {
        printf("\nroot to remove has only left child\n");
        Node *temp = (*node)->left;
        free((*node)->value);
        free(*node);
        *node = temp;
        (*node)->color = BLACK;
        return;
    }

    // root has one right child
    if ((*node)->right != NULL && (*node)->left == NULL) {
        printf("\nroot to remove has only right child\n");
        Node *temp = (*node)->right;
        free((*node)->value);
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
        // add parent of node_to_del to the stack
        s_append(stack, *node);

        Node *max_data_left = find_max_in_left_subtree(&((*node)->left), stack);
        int max_data = max_data_left->key;
        (*node)->key = max_data;
        printf("\nmax_data_left = %d", max_data_left->key);

        // node = next node after the new root in a left subtree
        remove_recolor(&max_data_left, stack);

        return;
    }

    return;
}

void remove_recolor(Node **node, Stack **stack) {
    printf("\nremove_recolor node to be deleted = %d\n", (*node)->key);

    if (is_stack_empty(stack)) {
        printf("\nnode to remove is a root node\n");
        remove_root_node(node, stack);
        return;
    }

    // node has no children
    if ((*node)->left == NULL && (*node)->right == NULL) {
        printf("\nnode with no children\n");

        // if red leaf node just delete it
        if ((*node)->color == RED) {
            printf("\nnode color is red\n");

            // get parent
            Node *parent = s_pop(stack);

            int node_position_to_parent = get_node_position_to_parent(*node, parent);
            free((*node)->value);
            free(*node);
            *node = NULL;

            null_link_from_parent_of_removed_node(node_position_to_parent, parent);

        } else {
            // node color is black
            printf("\nnode color is black\n");

            Node *parent = s_pop(stack);
            Node *sibling = get_sibling(node, &parent);
            int node_position_to_parent = get_node_position_to_parent(*node, parent);

            // delete node_to_delete
            free((*node)->value);
            free(*node);
            *node = NULL;

            null_link_from_parent_of_removed_node(node_position_to_parent, parent);
            propagate_and_recolor(&parent, &sibling, stack, node_position_to_parent);
        }
        return;
    }

    // node has one right child
    if ((*node)->right != NULL && (*node)->left == NULL) {
        printf("\nnode has one right child\n");

        s_append(stack, *node);
        Node *min_node = find_min_in_right_subtree(&((*node)->right), stack);
        printf("\nmin_node = %d\n", min_node->key);
        (*node)->key = min_node->key;

        remove_recolor(&min_node, stack);

        return;
    }

    // node has one left child
    if ((*node)->left != NULL && (*node)->right == NULL) {
        printf("\nnode has one left child\n");

        s_append(stack, *node);
        Node *max_node = find_max_in_left_subtree(&((*node)->left), stack);
        printf("\nmax_node = %d\n", max_node->key);
        (*node)->key = max_node->key;

        remove_recolor(&max_node, stack);

        return;
    }

    // node has two children
    if ((*node)->left != NULL && (*node)->right != NULL) {
        printf("\nnode has two child\n");

        // add parent to the stack
        s_append(stack, *node);
        Node *max_node = find_max_in_left_subtree(&(*node)->left, stack);
        printf("\nmax_node = %d\n", max_node->key);
        // change node key for min key of the left subtree
        (*node)->key = max_node->key;

        /* propagate_and_recolor(&max_node, stack); */
        remove_recolor(&max_node, stack);
        return;
    }
}

void find_node(Node **node, int key, Stack **stack) {
    if ((*node) == NULL) {
        printf("\nTree does not contain %d\n", key);
        return;
    }
    if (key == (*node)->key) {
        remove_recolor(node, stack);
        return;
    }

    if (key > (*node)->key) {
        s_append(stack, *node);
        find_node(&((*node)->right), key, stack);
        return;
    }

    if (key < (*node)->key) {
        s_append(stack, *node);
        find_node(&((*node)->left), key, stack);
        return;
    }
}

void remove_rbt(Node **root, int key) {
    printf("\n***** remove_rbt *****\n");

    double_black = 1;

    Stack *stack = NULL;

    if (*root == NULL) {
        printf("\nTree is empty\n");
    }

    find_node(root, key, &stack);
}
