#include "../declarations.h"
// basic foo
// args = low index (initially 0), high index (initially size - 1)
// set pivot as the last element
// set all less to the left and all greater than pivot to the right
// arr sorted in-line
// return position of the pivotal point

// recursion foo to split rangde into left (less than pivot) and right (greater
// than pivot) sort left, sort right base case low < hight

void swap(int *arr, size_t i, size_t j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

// set_pivotal_point
size_t find_pivotal_index(int *arr, size_t low, size_t high) {
  int pivot = arr[high];
  size_t pivotal_idx = low;

  for (size_t i = low; i < high; i++) {
    if (arr[i] < pivot) {
      // swap arr[i] with arr[pivotal_idx]
      swap(arr, i, pivotal_idx);
      // increment pivotal index to the next position
      pivotal_idx++;
    }
  }
  // swap arr[pivot] with arr[pivotal_idx]
  swap(arr, pivotal_idx, high);
  return pivotal_idx;
}

// recursively sort left and right halves
void quick_recurse(int *arr, size_t low, size_t high) {
  // exit condition
  if (low < high) {
    // recurse
    size_t pi = find_pivotal_index(arr, low, high);

    if (pi > low) {
      quick_recurse(arr, low, pi - 1);
    }
    if (pi < high) {
      quick_recurse(arr, pi + 1, high);
    }
  }
}

int *quick(int *arr, size_t size) {
  if (arr == NULL || size == 0) {
    return NULL;
  }
  quick_recurse(arr, 0, size - 1);
  return arr;
}
