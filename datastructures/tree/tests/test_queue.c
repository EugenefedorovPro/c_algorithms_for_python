#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void test_queue() {
    // when level is not used, it takes 0 level
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
    size_t level_right = 0;
    size_t level_left = 0;
    Position position = IGNORE;
    printf("\ncase #2 - enqueue\n");
    enqueue(nodes_queue, root, level_left, level_right, &position);
    enqueue(nodes_queue, root->left, level_left, level_right, &position);
    enqueue(nodes_queue, root->right, level_left, level_right, &position);
    enqueue(nodes_queue, root->left->left, level_left, level_right, &position);
    enqueue(nodes_queue, root->left->right, level_left, level_right, &position);

    printf("\nfirst = %d\n", nodes_queue->first->node->key);
    printf("\nsecond = %d\n", nodes_queue->first->link->node->key);
    printf("\nthird = %d\n", nodes_queue->first->link->link->node->key);
    printf("\nfourth = %d\n", nodes_queue->first->link->link->link->node->key);
    printf("\nfifth = %d\n", nodes_queue->first->link->link->link->link->node->key);

    CU_ASSERT(3 == nodes_queue->first->node->key);
    CU_ASSERT(9 == nodes_queue->first->link->node->key);
    CU_ASSERT(2 == nodes_queue->first->link->link->node->key);
    CU_ASSERT(1 == nodes_queue->first->link->link->link->node->key);
    CU_ASSERT(4 == nodes_queue->first->link->link->link->link->node->key);

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
        int dequeued_element = dequeue(nodes_queue)->node->key;
        printf("\ndequeued key = %d\n", dequeued_element);
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
