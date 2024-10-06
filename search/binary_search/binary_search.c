/* File: binary_search.c */
#include "binary_search.h"
#include <string.h>

int binarySearch(char *keyToFind, Item items[], size_t numElements) {
  int leftIndex = 0;
  int rightIndex = numElements - 1;

  while (leftIndex <= rightIndex) {
    int middle = (leftIndex + rightIndex) / 2;
    int cmpResult = strcmp(items[middle].key, keyToFind);
    if (cmpResult == 0) {
      return items[middle].value; // Key found
    } else if (cmpResult < 0) {
      leftIndex = middle + 1; // Search in the right half
    } else {
      rightIndex = middle - 1; // Search in the left half
    }
  }

  return -1; // Indicate that the key was not found
}
