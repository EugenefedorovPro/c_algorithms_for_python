#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include <stdio.h>

float f_knapsack(int *value_weight, size_t n_rows, size_t n_cols,
                 int capacity) {

  // allocate Item struct for internal usage
  Item *items = malloc(sizeof(Item) * n_rows);
  if (items == NULL) {
    fprintf(stderr, "ERROR: memory allocation failed for items\n");
    return 0;
  };

  // calculate ratio of value_weight pairs
  size_t i = 0;
  size_t j = 0;
  while (i < (n_rows * n_cols)) {
    int value = value_weight[i];
    int weight = value_weight[i + 1];

    items[j].value = value;
    items[j].weight = weight;
    items[j].ratio = (float)value / (float)weight;

    j++;
    i = i + 2;
  }

  // sort items by ratio in descending order
  for (size_t r1 = 0; r1 < n_rows; r1++) {
    for (size_t r2 = 0; r2 < n_rows - 1;
         r2++) { // Ensure we don't go out of bounds
      if (items[r2].ratio < items[r2 + 1].ratio) {
        Item temp = items[r2];
        items[r2] = items[r2 + 1];
        items[r2 + 1] = temp;
      }
    }
  }

  // load a knapsack
  int loaded = 0;
  float valued = 0.0f;
  for (int i = 0; i < n_rows; i++) {
    // find corresponding item, get weight and value
    if (loaded + items[i].weight <= capacity) {
      // increment loaded
      loaded += items[i].weight;
      valued += items[i].value;
    }
  }

  // case #2 - no fractions
  if (loaded == capacity) {
    return valued;
  }

  // case #1 - with fractions
  // fraction the last element
  int left_capacity = capacity - loaded;
  // get the weight of the last item
  int weight_of_last_item = items[n_rows - 1].weight;
  int value_of_last_item = items[n_rows - 1].value;
  float fraction = (float)left_capacity / weight_of_last_item;
  valued += value_of_last_item * fraction;

  free(items);

  return valued;
}
