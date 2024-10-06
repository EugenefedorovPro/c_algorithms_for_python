#include "../declarations.h"
#include <stdio.h>

// 5, 1, 2, 1
int *insertion(int *arr, size_t size) {

  for (size_t i = 1; i < size; i++) {
    int key = arr[i];
    size_t j = i;

    while (j > 0 && arr[j - 1] > key) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = key;
  }
  return arr;
}
