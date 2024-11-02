#include <stdio.h>

void print_arr(int *arr, size_t size) {
    printf("\narr = ");
    for (size_t i = 0; i < size; i++) {
        printf(" %d ", arr[i]);
    }
    printf("\n--------------------\n");
}
