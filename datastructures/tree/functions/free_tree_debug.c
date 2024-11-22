#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

void free_tree_debug(TreeDebug *tree_debug) {
    if (tree_debug->arr_tree_data) {
        free(tree_debug->arr_tree_data);
        tree_debug->arr_tree_data = NULL;
    }

    if (tree_debug->tree_root) {
        free_tree(tree_debug->tree_root);
        tree_debug->tree_root = NULL;
    }

    if (tree_debug->issue) {
        free(tree_debug->issue);
        tree_debug->issue = NULL;
    }

    if (tree_debug->arr_of_removed_numbers) {
        free(tree_debug->arr_of_removed_numbers);
    }

    tree_debug->n_failed_rbt = 0;
    tree_debug->size_of_removed_numbers = 0;
}
