#include "../declarations.h"
#include <stdio.h>

// 64, 25, 12 ,22, 11
// 25, 64, 12 ,22, 11
// 25, 64, 64, 22, 11
// 25, 25, 64, 22, 11
int *insertion(int *arr, size_t size) {
  for (size_t i = 1; i < size; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
  return arr;
};
