#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"


int main() {

    Node *root = NULL;
    // insert_rbt
    char *text_1 = "text_1";
    char *text_2 = "text_2";
    char *text_3 = "text_3";
    char *text_4 = "text_4";
    char *text_5 = "text_5";

    insert_rbt(&root, 2, text_2);
    insert_rbt(&root, 1, text_1);
    insert_rbt(&root, 3, text_3);
    insert_rbt(&root, 4, text_4);
    insert_rbt(&root, 5, text_5);

    // traverse_level_order
    traverse_level_order(root);

    // remove_rbt
    remove_rbt(&root, 2);
    remove_rbt(&root, 1);
    remove_rbt(&root, 3);
    remove_rbt(&root, 5);

    /* // search_rbt */
    int key = 4;
    char *value = search_rbt(root, 4);
    printf("\nkey = %d, value = %s\n", key, value);

    tree_to_dot(root);
    free_tree(root);

    return 0;
}
