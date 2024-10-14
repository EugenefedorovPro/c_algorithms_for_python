#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_queue() {
    size_t size = 6;
    int arr[6] = {3, 9, 2, 1, 4, 5};
    Node *root = create_binary_tree(arr, size);

    // case #1 - initiate queue
    printf("\ncase #1 - initiate queue\n");
    NodesQueue *nodes_queue = initiate_queue();
    CU_ASSERT(nodes_queue->count == 0);
    CU_ASSERT(nodes_queue->first == NULL);
    CU_ASSERT(nodes_queue->rear == NULL);
    

    // case #2 - enqueue
    printf("\ncase #2 - enqueue\n");
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

    CU_ASSERT(3 == nodes_queue->first->node->data);
    CU_ASSERT(9 == nodes_queue->first->link->node->data);
    CU_ASSERT(2 == nodes_queue->first->link->link->node->data);
    CU_ASSERT(1 == nodes_queue->first->link->link->link->node->data);
    CU_ASSERT(4 == nodes_queue->first->link->link->link->link->node->data);

    // case #3 count
    printf("\n--------------------\n");
    printf("\ncase #3 count\n");
    printf("\ncount = %zu\n", nodes_queue->count);
    CU_ASSERT(5 == nodes_queue->count);

    // case #4 - dequeue 
    printf("\n--------------------\n");
    printf("\ncase #4 - dequeue\n");
    int expected_deque[5] = {3, 9, 2, 1, 4};

    size_t number_elements = nodes_queue->count;
    for (size_t i = 0; i < number_elements; i++) {
        int dequeued_element = dequeue(nodes_queue)->data;
        printf("\ndequeued data = %d\n", dequeued_element);
        CU_ASSERT(expected_deque[i] == dequeued_element);
    }

    /* queue(root); */
    free_queue(nodes_queue);
    free_tree(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of queue()", test_queue);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
