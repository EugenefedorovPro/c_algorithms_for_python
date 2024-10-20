#include <math.h>

#include "../declarations.h"

// calculated level of any node used only as a part of level order traversal
size_t get_level(size_t idx) {
    if (idx == 1) {
        return 0;
    }
    if (idx == 2 || idx == 3) {
        return 1;
    }
    return ceil((log(idx + 1) / log(2)) - 1);
}

int current_level = -1;

void traverse(NodesQueue *nodes_queue, size_t *idx) {
    while (!is_empty(nodes_queue)) {
        Node *dequeued_node = dequeue(nodes_queue);
        int data = dequeued_node->data;

        printf("level = %zu, ids = %zu, data = %d\n", get_level(*idx + 1), *idx, data);

        (*idx)++;

        if (dequeued_node->left != NULL) {
            enqueue(nodes_queue, dequeued_node->left);
        }
        if (dequeued_node->right != NULL) {
            enqueue(nodes_queue, dequeued_node->right);
        }
    }
}

void traverse_level_order(Node *root) {
    printf("\nTraverse level order: \n");
    size_t idx = 0;
    NodesQueue *nodes_queue = initiate_queue();
    // add root to nodes_queue
    enqueue(nodes_queue, root);
    traverse(nodes_queue, &idx);
    free_queue(nodes_queue);
    printf("\nnumber of nodes by traverse level order = %zu \n", idx);
}
