#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdio.h>

typedef int *(*SortingFunction)(int *, size_t);

typedef struct SortingType {
  char *name_sort_alg;
  SortingFunction sort_foo;
} SortingType;

int *bubble(int *arr, size_t size);
int *insertion(int *arr, size_t size);
int *merge(int *arr, size_t size);
int *merge_inplace(int *arr, size_t size);
int *quick(int *arr, size_t size);
int *selection(int *arr, size_t size);

int *factory(char *name_sort_alg, int *arr, size_t size);
#endif
