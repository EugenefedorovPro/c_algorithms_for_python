#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

CheckResult check_red_black_properties(Node *node, char **issue) {
    // set explanations of a problem in rbt
    char *double_red_violation = "\ndouble red violation: parent %d is red, and child %d is red\n";
    char *black_rule_violation =
        "\nblack rule violation: different number of black nodes from node %d to leaves";
    char *left_bst_violation =
        "\nleft child %d is greater than parent %d, which violates the principle of binary "
        "search tree\n";
    char *right_bst_violation =
        "\nright child %d is less than parent %d, which violates the principle of binary "
        "search tree\n";

    // initialize result with default values
    CheckResult result = {0, 1};

    // null nodes are black in rbt
    if (node == NULL) {
        result.n_black_nodes = 1;
        return result;
    }

    printf("\nnode = %d\n", node->data);

    CheckResult left_result = check_red_black_properties(node->left, issue);
    if (!left_result.is_valid) {
        return left_result;
    }

    CheckResult right_result = check_red_black_properties(node->right, issue);
    if (!right_result.is_valid) {
        return right_result;
    }

    // check double red
    if (node->color == RED) {
        if (node->left != NULL && node->left->color == RED) {
            printf(double_red_violation, node->data, node->left->data);
            snprintf(*issue, 100, double_red_violation, node->data, node->left->data);
            result.is_valid = 0;
        }
        if (node->right != NULL && node->right->color == RED) {
            printf(double_red_violation, node->data, node->right->data);
            snprintf(*issue, 100, double_red_violation, node->data, node->right->data);
            result.is_valid = 0;
        }
    }

    // black nodes
    result.n_black_nodes = left_result.n_black_nodes;

    if (node->color == BLACK) {
        result.n_black_nodes++;
    }

    if (left_result.n_black_nodes != right_result.n_black_nodes) {
        printf(black_rule_violation,
               node->data,
               left_result.n_black_nodes,
               right_result.n_black_nodes);
        snprintf(*issue, 100, black_rule_violation, node->data);
        result.is_valid = 0;
    }

    // check binary search tree key principle for the adjacent nodes only
    if (node->left != NULL && node->left->data > node->data) {
        printf(left_bst_violation, node->left->data, node->data);
        snprintf(*issue, 100, left_bst_violation, node->data, node->left->data);
        result.is_valid = 0;
    }

    if (node->right != NULL && node->right->data < node->data) {
        printf(right_bst_violation, node->right->data, node->data);
        snprintf(*issue, 100, right_bst_violation, node->data, node->left->data);

        result.is_valid = 0;
    }

    return result;
}

int is_rb_tree(Node *root, char **issue) {
    char *empty = "\nRed Black Tree is empty but valid\n";
    char *root_red = "\nThe tree is not a valid Red Black Tree, as the root node is not BLACK\n";

    if (root == NULL) {
        printf("%s", empty);
        *issue = empty;
        return 1;
    }

    if (root->color != BLACK) {
        printf("%s", root_red);
        *issue = root_red;
        return 0;
    }

    CheckResult result = check_red_black_properties(root, issue);
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

// the foo checks insert_rbt function
// by generating multiple trees with a certain number of nodes
// and returns the pointer to the root
// of the last failed tree (if any), which does not comply with red black tree rules
// or the last successful tree
TreeDebug *check_inserts_in_multiple_trees(TreeDebug **tree_debug,
                                           size_t number_nodes,
                                           size_t number_trees,
                                           int is_random) {
    // create root
    Node *root = NULL;

    // returns root of the last success tree
    // if there are trees with violations, returns the last fail tree
    Node *last_success_root = NULL;
    Node *last_fail_root = NULL;
    int *last_success_rand_numbers = NULL;
    int *last_fail_rand_numbers = NULL;

    // if is_random == 1 then random numbers generated
    // if is_random == 0 then every time the same numbers
    if (is_random) {
        srand(time(NULL));
        printf("\nrandom with seed is enabled\n");
    }

    int n_fails = 0;

    char *issue = malloc(100);
    if (!issue) return NULL;

    for (size_t i = 0; i < number_trees; i++) {
        int *arr_rand_numbers = rand_numbers(number_nodes);

        create_rand_rbt(&root, &arr_rand_numbers, number_nodes);

        int status = is_rb_tree(root, &issue);

        if (status == 0) {
            n_fails++;

            // save last tree, which was build incorrectly
            if (last_fail_root) {
                free_tree(last_fail_root);
            }
            last_fail_root = copy_tree(root);

            // save last array of random numbers of the fail tree
            if (last_fail_rand_numbers) {
                free(last_fail_rand_numbers);
                last_fail_rand_numbers = NULL;
            }
            last_fail_rand_numbers = copy_array_int(arr_rand_numbers, number_nodes);

            // free random numbers before next iteration
            free(arr_rand_numbers);
        }

        // save last tree, which adheres to rbr rules
        if (last_success_root) {
            free_tree(last_success_root);
            last_success_root = NULL;
        }
        last_success_root = copy_tree(root);

        // save last array of random numbers of the success tree
        if (last_success_rand_numbers) {
            free(last_success_rand_numbers);
            last_success_rand_numbers = NULL;
        }
        last_success_rand_numbers = copy_array_int(arr_rand_numbers, number_nodes);

        // free previous tree
        free_tree(root);

        // reinitiate root
        root = NULL;
    }

    // add tree_root to tree_debug structure
    if (last_fail_root) {
        root = last_fail_root;
        printf("\nThe tree violates Red Black Tree rules\n");
        traverse_level_order(root);
    } else {
        root = last_success_root;
    }
    (*tree_debug)->tree_root = root;
    (*tree_debug)->n_failed_rbt = n_fails;

    // add array of rand number to tree_debug structure
    if (last_fail_rand_numbers) {
        (*tree_debug)->arr_tree_data = last_fail_rand_numbers;
    } else {
        (*tree_debug)->arr_tree_data = last_success_rand_numbers;
    }

    // add last issue
    (*tree_debug)->issue = issue;

    return *tree_debug;
}
