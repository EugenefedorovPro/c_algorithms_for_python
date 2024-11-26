void left_right_rotation(Node **grandparent, Node **parent, Stack **stack) {
    printf("\nleft_right_rotation, grandparent = %d, parent = %d\n",
           (*grandparent)->key,
           (*parent)->key);

    Node *temp_parent = malloc(sizeof(Node));
    if (temp == NULL) {
        fprintf(stderr, "memory allocation failed for temp");
        return;
    }

    // shift from left to right
    Node *new_parent = (*parent)->right;
    Node *node_left_child = NULL; // 16
    if ((*parent)->right->left != NULL) {
        node_left_child= (*parent)->right->left;
    }
    new_parent->left == NULL;

    *temp_parent = **parent;
    temp_parent->right = NULL;
    if (node_left_child != NULL) {
        temp_parent->right = node_left_child;
    }

    (*grandparent)->left = new_parent;
    new_parent->left = temp_parent;

    left_left_rotation(grandparent, &new_parent);

}

