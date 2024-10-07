// divide all by half
// base case: create and return single-element array
// compare elements in left and right halves -> smaller elements add to new
// sorted_arr
#include "../declarations.h"
#include <stdlib.h>

int *compare(int *left, size_t size_left, int *right, size_t size_right) {
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;

  int *sorted_arr = malloc(sizeof(int) * (size_left + size_right));
  if (sorted_arr == NULL) {
    fprintf(stderr,
            "ERROR: memory allocation failed for sorted_arr in merge\n");
    return NULL;
  }

  while (i < size_left && j < size_right) {
    if (left[i] < right[j]) {
      sorted_arr[k++] = left[i++];
    } else {
      sorted_arr[k++] = right[j++];
    }
  }

  while (i < size_left) {
    sorted_arr[k++] = left[i++];
  }

  while (j < size_right) {
    sorted_arr[k++] = right[j++];
  }

  return sorted_arr;
}

int *merge(int *arr, size_t size) {
  if (size == 1) {
    return arr;
  }

  size_t mid = size / 2;

  int *left_half = malloc(sizeof(int) * mid);
  if (left_half == NULL) {
    fprintf(stderr, "ERROR: memory allocation failed for left in merge\n");
    return NULL;
  }

  int *right_half = malloc(sizeof(int) * size - mid);
  if (right_half == NULL) {
    fprintf(stderr, "ERROR: memory allocation failed for right in merge\n");
    return NULL;
  }

  for (size_t i = 0; i < size; i++) {
    if (i < mid) {
      left_half[i] = arr[i];
    } else {
      right_half[i - mid] = arr[i];
    }
  }

  int *left = merge(left_half, mid);
  int *right = merge(right_half, size - mid);

  int *sorted_arr = compare(left, mid, right, size - mid);
  free(left);
  free(right);

  return sorted_arr;
}
