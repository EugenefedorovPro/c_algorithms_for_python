#include <stdio.h>
#include <stdlib.h>

void swap(int *arr, size_t i, size_t j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

size_t find_pivot_idx(int *arr, size_t low, size_t high) {
    size_t pivot_idx = low;
    int pivot = arr[high];

    for (size_t i = low; i < high; i++) {
        if (arr[i] < pivot) {
            swap(arr, i, pivot_idx);
            pivot_idx++;
        }
    }
    swap(arr, pivot_idx, high);

    return pivot_idx;
}

void quick(int *arr, size_t low, size_t high) {
    if (low >= high) {
        return;
    }

    size_t pi = find_pivot_idx(arr, low, high);

    if (pi > low) {
        quick(arr, low, pi - 1);
    }

    if (pi < high) {
        quick(arr, pi + 1, high);
    }
}

int main() {
    size_t size = 7;
    int arr[7] = {
        3,
        4,
        2,
        0,
        5,
        2,
        -1

    };

    quick(arr, 0, size - 1);

    // print arr
    printf("\narr = ");
    for (size_t i = 0; i < size; i++) {
        printf(" %d ", arr[i]);
    }
    printf("\n--------------------\n");
    return 0;
}
