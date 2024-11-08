#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

CheckResult check_red_black_properties(Node *node) {
    CheckResult result = {0, 1};

    if (node == NULL) {
        result.n_black_nodes = 1;
        return result;
    }

    printf("\nnode = %d\n", node->data);

    CheckResult left_result = check_red_black_properties(node->left);
    if (!left_result.is_valid) {
        return left_result;
    }

    CheckResult right_result = check_red_black_properties(node->right);
    if (!right_result.is_valid) {
        return right_result;
    }

    // check double red
    if (node->color == RED) {
        if (node->left != NULL && node->left->color == RED) {
            printf("\ndouble red violation: parent %d is red, and child %d is red\n",
                   node->data,
                   node->left->data);
            result.is_valid = 0;
        }
        if (node->right != NULL && node->right->color == RED) {
            printf("\ndouble red violation: parent %d is red, and child %d is red\n",
                   node->data,
                   node->right->data);
            result.is_valid = 0;
        }
    }

    // black nodes
    result.n_black_nodes = left_result.n_black_nodes;

    if (node->color == BLACK) {
        result.n_black_nodes++;
    }

    if (left_result.n_black_nodes != right_result.n_black_nodes) {
        printf(
            "\nblack rule violation: different number of black nodes from node %d to leaves: left "
            "= %d, right = %d\n",
            node->data,
            left_result.n_black_nodes,
            right_result.n_black_nodes);
        result.is_valid = 0;
    }

    // check binary search tree key principle for the adjacent nodes only
    if (node->left != NULL && node->left->data > node->data) {
        printf(
            "\nleft child %d is greater than parent %d, which violates the principle of binary "
            "search "
            "tree\n",
            node->left->data,
            node->data);

        result.is_valid = 0;
    }

    if (node->right != NULL && node->right->data < node->data) {
        printf(
            "\nright child %d is less than parent %d, which violates the principle of binary "
            "search "
            "tree\n",
            node->right->data,
            node->data);

        result.is_valid = 0;
    }

    return result;
}

int is_rb_tree(Node *root) {
    if (root == NULL) {
        printf("\nRed Black Tree is empty but valid \n");
        return 1;
    }

    if (root->color != BLACK) {
        printf("\nThe tree is not a valid Red Black Tree, as the root node is not BLACK\n");
        return 0;
    }

    CheckResult result = check_red_black_properties(root);
    if (result.is_valid) {
        printf("\nRed Black Tree is valid with %d black nodes\n", result.n_black_nodes);
        return 1;
    } else {
        printf("\nThe tree is not a valid Red Black Tree\n");
        return 0;
    }
}

int *rand_numbers(size_t number) {
    int *arr = malloc(sizeof(int) * number);
    if (arr == NULL) {
        fprintf(stderr, "memory allocation failed for arr");
        return NULL;
    }

    for (size_t i = 0; i < number; i++) {
        arr[i] = (number / 2) - (rand() % (number + 1));
        printf("\nrand number = %d\n", arr[i]);
    }
    return arr;
}

void create_rand_rbt(Node **root, int **arr_rand_numbers, size_t number) {
    for (size_t i = 0; i < number; i++) {
        insert_rbt(root, (*arr_rand_numbers)[i]);
    }
}

int check_inserts_in_multiple_trees(Node **root,
                                    size_t number_nodes,
                                    size_t number_trees,
                                    int is_random) {
    // returns root of the last success tree
    // if there are trees with violations, returns the last fail tree
    Node *last_success_root = NULL;
    Node *last_fail_root = NULL;

    // if is_random == 1 then random numbers generated
    // if is_random == 0 then every time the same numbers
    if (is_random) {
        srand(time(NULL));
        printf("\nrandom with seed is enabled\n");
    }
    int n_fails = 0;
    for (size_t i = 0; i < number_trees; i++) {
        int *arr_rand_numbers = rand_numbers(number_nodes);

        create_rand_rbt(root, &arr_rand_numbers, number_nodes);
        int status = is_rb_tree(*root);

        if (status == 0) {
            n_fails++;
            last_fail_root = *root;
        }
        free(arr_rand_numbers);
        last_success_root = *root;
        free_tree(*root);
        *root = NULL;
    }

    if (last_fail_root) {
        *root = last_fail_root;
        printf("\nThe tree violates Red Black Tree rules\n");
        traverse_level_order(*root);
    } else {
        *root = last_success_root;
    }

    return n_fails;
}

// is not completed yet
/* int check_removes_in_multiple_trees( */
/*     Node **root, size_t number_nodes, size_t number_trees, size_t *count) { */
/*     int n_fails = 0; */
/*     for (size_t i = 0; i < number_trees; i++) { */
/*         create_rand_rbt(root, arr_rand_numbers, number_nodes); */
/*         // get number of nodes to remove */

/*         (*count)++; */
/*         int status = is_rb_tree(*root); */
/*         if (status == 0) { */
/*             printf("\nThe tree violates Red Black Tree rules\n"); */
/*             traverse_level_order(*root); */
/*             n_fails++; */
/*         } */
/*     } */
/*     return n_fails; */
/* } */
