#include <stdio.h>

int main() {
  int arr[] = {5, 4, 3};
  arr[0] = arr[1];


  printf("\n arr = ");
  for (size_t i = 0; i < 3; i++) {
    printf(" %d ", arr[i]);
  }
  return 0;
};
