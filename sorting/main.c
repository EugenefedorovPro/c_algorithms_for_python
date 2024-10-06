#include "declarations.h"

int main() {
  size_t size = 5;
  int arr[] = {5, 4, 3, 2, 1};
  char sorting_type[] = "bubble";
  int *sorted_arr = factory(sorting_type, arr, size);

  // print arr
  printf("\nsorted_arr = ");
  for (size_t i = 0; i < size; i++) {
    printf(" %d ", sorted_arr[i]);
  }
  printf("\n--------------------\n");

  return 0;
}
