#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  size_t n_rows = 3;
  size_t n_cols = 2;
  int *value_weight = malloc(sizeof(int) * n_rows * n_cols);
  if (value_weight == NULL) {
    fprintf(stderr, "ERROR: memory allocation failed for value_weight\n");
    return 0;
  };

  value_weight[0 * n_cols + 0] = 120; // 0
  value_weight[0 * n_cols + 1] = 30; // 1
  value_weight[1 * n_cols + 0] = 100; // 2
  value_weight[1 * n_cols + 1] = 20; // 3
  value_weight[2 * n_cols + 0] = 60; // 4
  value_weight[2 * n_cols + 1] = 10; // 5

  int CAPACITY = 50;

  float result = f_knapsack(value_weight, n_rows, n_cols, CAPACITY);
  printf("\nmax total profit = %f\n", result);

  return 0;
}
