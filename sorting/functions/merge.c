// divide all by half
// base case: create and return single-element array
// compare elements in left and right halves -> smaller elements add to new
// sorted_arr
#include "../declarations.h"
#include <stdlib.h>

int *compare(int *left, int *right, size_t size_left, size_t size_right) {
  int *sorted_arr = malloc(sizeof(int) * (size_left + size_right));
  if (sorted_arr == NULL) {
    fprintf(stderr,
            "ERROR: memory allocation failed for sorted_arr in compare\n");
    return NULL;
  }

  // initiate i, j, k indexes
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;

  // compare and merge
  while (i < size_left && j < size_right) {
    if (left[i] < right[j]) {
      sorted_arr[k++] = left[i++];
    } else {
      sorted_arr[k++] = right[j++];
    }
  }
  // add left remnants
  while (i < size_left) {
    sorted_arr[k++] = left[i++];
  }
  // add right remnants
  while (j < size_right) {
    sorted_arr[k++] = right[j++];
  }
  return sorted_arr;
}

int *merge(int *arr, size_t size) {
  // base case - return single element array
  if (size == 0) {
    return NULL;
  }

  if (size == 1) {
    int *single_element_arr = malloc(sizeof(int));
    if (single_element_arr == NULL) {
      fprintf(
          stderr,
          "ERROR: memory allocation failed for single_element_arr in merge\n");
      return NULL;
    }
    single_element_arr[0] = arr[0];
    return single_element_arr;
  }

  // find mid
  size_t mid = size / 2;

  // allocate memory for left_half
  int *left_half = malloc(sizeof(int) * mid);
  // allocate memory for right half
  int *right_half = malloc(sizeof(int) * (size - mid));
  if (left_half == NULL || right_half == 0) {
    fprintf(stderr, "ERROR: memory allocation failed for left_half of "
                    "right_half in merge()\n");
    return NULL;
  }

  // create left half
  for (size_t i = 0; i < mid; i++) {
    left_half[i] = arr[i];
  }

  // create right half
  for (size_t i = 0; i < size - mid; i++) {
    right_half[i] = arr[i + mid];
  }

  // recurse left half
  int *left = merge(left_half, mid);
  // recurse right half
  int *right = merge(right_half, size - mid);

  // free mem
  free(right_half);
  free(left_half);

  // compare and get sorted
  int *sorted_arr = compare(left, right, mid, size - mid);
  // free mem
  free(left);
  free(right);

  return sorted_arr;
}
