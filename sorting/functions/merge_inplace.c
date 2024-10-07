#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

int count = 0;

void compare_inplace(int *arr, size_t low, size_t mid, size_t high) {
    count ++;
    // set size of the left half
    size_t size_left = mid - low + 1;
    // set size of the right half
    size_t size_right = high - mid;
    // create left arr
    int left[size_left];
    for (size_t i = 0; i < size_left; i++) {
        left[i] = arr[low + i];
    }
    // create right arr
    int right[size_right];
    for (size_t j = 0; j < size_right; j++) {
        right[j] = arr[mid + 1 + j];
    }

    // compare element by element in left and right -> merge in original arr
    size_t i = 0;
    size_t j = 0;
    size_t k = low;
    while (i < size_left && j < size_right) {
        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // add remnants to left
    while (i < size_left) {
        arr[k++] = left[i++];
    }

    // add remnants to right
    while (j < size_right) {
        arr[k++] = right[j++];
    }
}

void recurse_inplace(int *arr, size_t low, size_t high) {
    if (low < high) {
        // set mid
        size_t mid = low + (high - low) / 2;
        recurse_inplace(arr, low, mid);
        recurse_inplace(arr, mid + 1, high);

        // call compare_inplace
        compare_inplace(arr, low, mid, high);
    }
}

int *merge_inplace(int *arr, size_t size) {
    recurse_inplace(arr, 0, size - 1);
    return arr;
}
