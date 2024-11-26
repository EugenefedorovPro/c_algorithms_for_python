#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int main() {
    Node *root = NULL;
    // insert_rbt
    insert_rbt(&root, 1, "empty");
    insert_rbt(&root, 2, "empty");
    insert_rbt(&root, 3, "empty");
    insert_rbt(&root, 4, "empty");
    insert_rbt(&root, 5, "empty");

    // traverse_level_order
    traverse_level_order(root);


    // remove_rbt
    remove_rbt(&root, 2);
    remove_rbt(&root, 1);
    remove_rbt(&root, 5);

    traverse_level_order(root);

    // is_rb_tree
    char *issue = malloc(100);
    is_rb_tree(root, &issue);

    tree_to_dot(root);
    free_tree(root);
    free(issue);

    printf("\nsizeof int = %zu\n", sizeof(int) * 8);



    return 0;
}
