#include <stdlib.h>

#include "declarations.h"

int *merge(int *left, size_t leftSize, int *right, size_t rightSize) {
  // allocate memory for a sortedArray
  int *sortedArray = malloc(sizeof(int) * (leftSize + rightSize));
  if (sortedArray == NULL) {
    fprintf(stderr,
            "Error: Memory allocation failed for sortedArray in merge\n");
    return NULL;
  }

  // sort and merge by comparing numbers from two halves
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;

  while (i < leftSize && j < rightSize) {
    if (left[i] > right[j]) {
      sortedArray[k++] = left[i++];
    } else {
      sortedArray[k++] = right[j++];
    }
  }

  while (i < leftSize) {
    sortedArray[k++] = left[i++];
  }

  while (j < rightSize) {
    sortedArray[k++] = right[j++];
  }

  return sortedArray;
}

int *merge_sort(int *coins, size_t size) {
  if (size <= 1) {
    return coins;
  }

  size_t mid = size / 2;

  // create left and right halves
  int *left = malloc(mid * sizeof(int));
  int *right = malloc((size - mid) * sizeof(int));

  if (left == NULL || right == NULL) {
    free(left);
    free(right);
    fprintf(
        stderr,
        "Error: Memory allocation failed for left of right in merge_sort\n");
    return NULL;
  }

  for (size_t i = 0; i < size; i++) {
    if (i < mid) {
      left[i] = coins[i];
    } else {
      right[i - mid] = coins[i];
    }
  }

  int *left_half = merge_sort(left, mid);
  int *right_half = merge_sort(right, size - mid);

  int *sortedArray = merge(left_half, mid, right_half, size - mid);

  free(left);
  free(right);

  return sortedArray;
}
