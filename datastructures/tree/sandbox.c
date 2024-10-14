#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int is_empty(NodesQueue *nodes_queue) {
    if (nodes_queue->first == NULL && nodes_queue->rear == NULL) {
        return 1;
    };
    return 0;
};

Node *dequeue(NodesQueue *nodes_queue) {
    // check if queue is_empty
    if (is_empty(nodes_queue)) {
        printf("You cannot dequeue from empty queue");
        return NULL;
    }
    // get link of the first q_node pointing to the next node
    Q_node *temp_link = nodes_queue->first->link;
    // get node to return
    Node *first_node = nodes_queue->first->node;
    // remove the first q_node
    free(nodes_queue->first);
    // assign extracted link to first
    nodes_queue->first = temp_link;

    // if the queue is now empty set rear to NULL
    if (nodes_queue->first == NULL) {
        nodes_queue->rear = NULL;
    }

    // decrease count
    nodes_queue->count--;
    return first_node;
};

void enqueue(NodesQueue *nodes_queue, Node *node) {
    // create new q_node
    Q_node *q_node = malloc(sizeof(Q_node));
    if (q_node == NULL) {
        fprintf(stderr, "memory allocation failed for q_node");
        exit(EXIT_FAILURE);
    }
    q_node->node = node;
    q_node->link = NULL;

    // if queue is empty make new q_node the first and the last element
    if (is_empty(nodes_queue)) {
        nodes_queue->first = q_node;
        nodes_queue->rear = q_node;

    } else {
        // nodes_queue has two elements first and rear
        // add link to rear to new q_node
        nodes_queue->rear->link = q_node;
        nodes_queue->rear = q_node;
    }
    // add 1 to the size of nodes_queue
    nodes_queue->count++;
}

void free_queue(NodesQueue *nodes_queue) {
    while (!is_empty(nodes_queue)) {
        dequeue(nodes_queue);
    }
}

NodesQueue *initiate_queue() {
    NodesQueue *nodes_queue = malloc(sizeof(NodesQueue));
    nodes_queue->first = NULL;
    nodes_queue->rear = NULL;
    nodes_queue->count = 0;
    return nodes_queue;
}

int main() {
    size_t size = 6;
    int arr[6] = {3, 9, 2, 1, 4, 5};
    Node *root = create_binary_tree(arr, size);

    NodesQueue *nodes_queue = initiate_queue();

    enqueue(nodes_queue, root);
    enqueue(nodes_queue, root->left);
    enqueue(nodes_queue, root->right);
    enqueue(nodes_queue, root->left->left);
    enqueue(nodes_queue, root->left->right);

    printf("\nfirst = %d\n", nodes_queue->first->node->data);
    printf("\nsecond = %d\n", nodes_queue->first->link->node->data);
    printf("\nthird = %d\n", nodes_queue->first->link->link->node->data);
    printf("\nfourth = %d\n", nodes_queue->first->link->link->link->node->data);
    printf("\nfifth = %d\n", nodes_queue->first->link->link->link->link->node->data);

    printf("\n--------------------\n");
    printf("\ncount = %zu\n", nodes_queue->count);

    size_t number_elements = nodes_queue->count;
    for (size_t i = 0; i < number_elements; i++) {
        printf("\ndequeued data = %d\n", dequeue(nodes_queue)->data);
    }

    /* traverse_preorder(root); */
    free_queue(nodes_queue);
    free_tree(root);

    return 0;
}
