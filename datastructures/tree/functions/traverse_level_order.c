#include "../declarations.h"

void traverse(NodesQueue *nodes_queue) {
    if (is_empty(nodes_queue)) {
        return;
    }

    Node *dequeued_node = dequeue(nodes_queue);
    size_t index = dequeued_node->index;
    int data = dequeued_node->data;
    printf("\nindex = %zu, data = %d\n", index, data);

    if (dequeued_node->left != NULL) {
        enqueue(nodes_queue, dequeued_node->left);
    }
    if (dequeued_node->right != NULL) {
        enqueue(nodes_queue, dequeued_node->right);
    }

    traverse(nodes_queue);

}

void traverse_level_order(Node *root) {
    NodesQueue *nodes_queue = initiate_queue();
    // add root to nodes_queue
    enqueue(nodes_queue, root);
    traverse(nodes_queue);
    free_queue(nodes_queue);
}
