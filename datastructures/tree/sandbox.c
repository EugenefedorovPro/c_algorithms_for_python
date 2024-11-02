void right_left_rotation(Node **grandparent, Node **parent, Stack **stack) {
    printf("\nright_left_rotation, grandparent = %d, parent = %d\n",
           (*grandparent)->data,
           (*parent)->data);

    Node *temp_parent = malloc(sizeof(Node));
    if (temp_parent == NULL) {
        fprintf(stderr, "memory allocation failed for temp_parent");
        return;
    }

    // shift from left to right
    Node *new_parent = (*parent)->left; // 15
    Node *node_right_child = NULL; // 16
    if ((*parent)->left->right != NULL) {
        node_right_child = (*parent)->left->right;
    }
    new_parent->right = NULL;

    *temp_parent = **parent; // 18
    temp_parent->left = NULL;
    if (node_right_child != NULL) {
        temp_parent->left = node_right_child;
    }

    (*grandparent)->right = new_parent; // 10 - 15 
    new_parent->right = temp_parent; // 15 - 18

    // change grandparent (root) == right - right rotation with temp_parent as base
    right_right_rotation(grandparent, &new_parent);

}
