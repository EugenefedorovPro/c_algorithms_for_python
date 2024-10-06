#include "../declarations.h"
// basic foo
// args = low index (initially 0), high index (initially size - 1)
// set pivot as the last element
// set all less to the left and all greater than pivot to the right
// arr sorted in-line
// return position of the pivotal point

// recursion foo to split rangde into left (less than pivot) and right (greater
// than pivot) sort left, sort right base case low < hight

// 5, 1, 3, 0, 4, 2

void swap(int *arr, size_t i, size_t j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

size_t find_pivot_idx(int *arr, size_t low, size_t high) {

  int pivot = arr[high];
  size_t pivot_idx = low;

  for (size_t i = low; i < high; i++) {
    if (arr[i] < pivot) {
      swap(arr, i, pivot_idx);
      pivot_idx++;
    }
  }
  swap(arr, pivot_idx, high);

  return pivot_idx;
}

void quick_recurse(int *arr, size_t low, size_t high) {

  if (low < high) {
    size_t pi = find_pivot_idx(arr, low, high);

    if (pi > low + 1) {
      quick_recurse(arr, low, pi - 1);
    }
    if (pi < high - 1) {
      quick_recurse(arr, pi + 1, high);
    }
  }
}

int *quick(int *arr, size_t size) {
  if (size == 0) {
    return arr;
  }
  quick_recurse(arr, 0, size - 1);

  return arr;
}
