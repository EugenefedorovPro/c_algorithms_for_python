#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"


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

