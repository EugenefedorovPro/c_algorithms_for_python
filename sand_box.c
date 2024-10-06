#include <stdio.h>

// 3, 2, 1
void insert_sort(int *arr, size_t size) {
  for (size_t i = 1; i < size; i++) {
    int key = arr[i];
    size_t j = i; 

    while (j > 0 && arr[j - 1] > key) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = key;
  }
}

int main() {
  int arr[] = {3, 4, 0, -2, 1};
  size_t size = 5;
  insert_sort(arr, size);

  // print arr
  printf("\narr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", arr[i]);
  }
  printf("\n--------------------\n");


  return 0;
}
