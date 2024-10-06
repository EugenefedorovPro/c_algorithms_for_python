#include "../declarations.h"
#include <stdio.h>

int *bubble(int *arr, size_t size) {
  int swapped;
  do {
    swapped = 0;
    for (size_t i = 0; i < size - 1; i++) {
      if (arr[i] > arr[i + 1]) {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
        swapped = 1;
      }
    }
    size--;
  } while (swapped);

  return arr;
}
