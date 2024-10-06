/* File: binary_search.h */
#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
#include <stdlib.h>

typedef struct item {
  char *key;
  int value;
} Item;

int binarySearch(char *keyToFind, Item items[], size_t numElements);

#endif /* BINARY_SEARCH_H */
