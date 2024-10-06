#include "../declarations.h"
#include <stdio.h>

// nested loops, find index of min value while iteration, swap
int *selection(int *arr, size_t size) {

  size_t i = 0;
  size_t j = 0;
  for (i = 0; i < size; i++) {
    size_t idx_min_value = i;
    for (j = i + 1; j < size; j++) {
      // save index of the min value in arr
      if (arr[idx_min_value] > arr[j]) {
        idx_min_value = j;
      }
    }
    // swap values in arr
    if (idx_min_value != i) {
      int temp = arr[i];
      arr[i] = arr[idx_min_value];
      arr[idx_min_value] = temp;
    }
  }

  return arr;
}
