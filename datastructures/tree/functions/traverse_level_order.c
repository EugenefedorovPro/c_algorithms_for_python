#include "../declarations.h"

size_t level_left;
size_t level_right;
Position position;

void traverse(NodesQueue *nodes_queue, size_t *idx) {
    while (!is_empty(nodes_queue)) {
        Q_node *dequeued_node = dequeue(nodes_queue);
        int key = dequeued_node->node->key;
        int color = dequeued_node->node->color;
        position = dequeued_node->position;
        size_t node_level_left = dequeued_node->level_left;
        size_t node_level_right = dequeued_node->level_right;

        size_t parent_node_level = (position == LEFT) ? node_level_left : node_level_right;
        char *value = dequeued_node->node->value;

        switch (position) {
            case ROOT:
                printf("level = %d, ids = %zu, color = %d, key = %d, value = %s\n", 0, *idx, color, key, value);
                break;
            case LEFT:
                printf("level = %zu, ids = %zu, color = %d, key = %d, value = %s\n",
                       node_level_left,
                       *idx,
                       color,
                       key,
                       value);
                break;
            case RIGHT:
                printf("level = %zu, ids = %zu, color = %d, key = %d, value = %s\n",
                       node_level_right,
                       *idx,
                       color,
                       key,
                       value);
                break;
            case IGNORE:
                printf("\nposition is ignored\n");
                break;
        }

        (*idx)++;

        if (dequeued_node->node->left != NULL) {
            level_left = parent_node_level + 1;
            position = LEFT;
            enqueue(nodes_queue, dequeued_node->node->left, level_left, level_right, &position);
        }
        if (dequeued_node->node->right != NULL) {
            level_right = parent_node_level + 1;
            position = RIGHT;
            enqueue(nodes_queue, dequeued_node->node->right, level_left, level_right, &position);
        }
    }
}

void traverse_level_order(Node *root) {
    printf("\nTraverse level order: \n");
    if (root == NULL) {
        printf("\nTree is empty, root = NULL\n");
        return;
    }
    level_left = 0;
    level_right = 0;
    size_t idx = 0;
    position = ROOT;
    NodesQueue *nodes_queue = initiate_queue();
    // add root to nodes_queue
    enqueue(nodes_queue, root, level_left, level_right, &position);
    traverse(nodes_queue, &idx);
    free_queue(nodes_queue);
    printf("\nnumber of nodes by traverse level order = %zu \n", idx);
}
