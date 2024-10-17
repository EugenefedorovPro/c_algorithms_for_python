#include "../declarations.h"

void traverse(NodesQueue *nodes_queue, size_t *idx) {
    while (!is_empty(nodes_queue)) {
        Node *dequeued_node = dequeue(nodes_queue);
        int data = dequeued_node->data;

        printf("\nindex = %zu, data = %d\n", (*idx)++, data);

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
