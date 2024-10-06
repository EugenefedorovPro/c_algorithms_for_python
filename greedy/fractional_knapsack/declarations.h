#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdlib.h>

typedef struct Item {
	int value;
	int weight;
	float ratio;
} Item;

float f_knapsack(int *value_weight, size_t n_rows, size_t n_cols, int capacity);

#endif
