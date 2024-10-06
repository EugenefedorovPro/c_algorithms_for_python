#include "../declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *factory(char *name_sort_alg, int *arr, size_t size) {
  size_t n_types = 5;
  SortingType sorting_types[] = {
      {"bubble", bubble},
      {"insertion", insertion},
      {"merge", merge},
      {"quick", quick},
      {"selection", selection},
  };

  for (size_t i = 0; i < n_types; i++) {
    if (strcmp(sorting_types[i].name_sort_alg, name_sort_alg) == 0) {
      sorting_types[i].sort_foo(arr, size);
    }
  }
  fprintf(stderr, "\nERROR: no alg with name '%s\n'", name_sort_alg);
  return NULL;
};
