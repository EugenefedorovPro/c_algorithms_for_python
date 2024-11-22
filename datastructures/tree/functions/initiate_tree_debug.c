#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

TreeDebug *initiate_tree_debug() {
    TreeDebug *tree_debug = malloc(sizeof(TreeDebug));
    if (tree_debug == NULL) {
        fprintf(stderr, "\nmemory allocation failed for tree_debug\n");
        return NULL;
    }
    tree_debug->tree_root = NULL;
    tree_debug->arr_tree_data = NULL;
    tree_debug->arr_of_removed_numbers = NULL;
    tree_debug->size_of_removed_numbers = 0;
    tree_debug->issue = NULL;
    tree_debug->n_failed_rbt = 0;
    return tree_debug;
}



