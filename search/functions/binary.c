#include <stdio.h>

#include "../declarations.h"

int search(int *arr, size_t low, size_t high, int n) {
    if (low <= high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == n) {
            return (int)mid;
        }
        // search in left
        if (n < arr[mid]) {
            return search(arr, low, mid - 1, n);
        } else {
            // search in right
            return search(arr, mid + 1, high, n);
        }
    }
    return -1;
}

int binary(int *arr, size_t size, int n) {
    // check is array is sorted
    for (size_t i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("This binary search can work only with arrays sorted in ascending order");
            return -1;
        }
    }

    int idx = search(arr, 0, size - 1, n);
    if (idx == -1) {
        printf("\nno number %d n in array\n", n);
        return -1;
    }
    return idx;
}
