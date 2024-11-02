#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../declarations.h"

int *rand_numbers(size_t number) {
    int *arr = malloc(sizeof(int) * number);
    if (arr == NULL) {
        fprintf(stderr, "memory allocation failed for arr");
        return NULL;
    }

    for (size_t i = 0; i < number; i++) {
        arr[i] = (number / 2) - (rand() % (number + 1));
        printf("\nrand number = %d\n", arr[i]);
    }
    return arr;
}

void create_rand_rbt(Node **root, int **arr_rand_numbers, size_t number) {
    for (size_t i = 0; i < number; i++) {
        insert_rbt(root, (*arr_rand_numbers)[i]);
    }
}

void create_multiple_trees(
    Node **root, int **arr_rand_numbers, size_t number_nodes, size_t number_trees, size_t *count) {
    for (size_t i = 0; i < number_trees; i++) {
        create_rand_rbt(root, arr_rand_numbers, number_nodes);
        (*count)++;
    }
}

void test_insert_rbt() {
    // creates multiple trees with random nodes and print the last tree for visual control
    srand(time(NULL));
    Node *root = NULL;

    /* insert_rbt(&root, 50); */
    /* insert_rbt(&root, -30); */
    /* /1* insert_rbt(&root, -40); *1/ */

    size_t number_nodes = 31;
    size_t number_trees = 1;
    size_t count = 0;
    int *arr_rand_numbers = rand_numbers(number_nodes);
    create_multiple_trees(&root, &arr_rand_numbers, number_nodes, number_trees, &count);

    traverse_level_order(root);
    printf("\nNumber of created trees = %zu\n", count);

    tree_to_dot(root);
    free(root);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tree Suite", NULL, NULL);
    CU_add_test(suite, "test of insert_rbt()", test_insert_rbt);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
