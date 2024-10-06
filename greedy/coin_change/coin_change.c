#include <stdlib.h>
#include <string.h>

#include "declarations.h"

int *coin_change(int *coins, size_t size, int amount) {
  int *sorted_coins = merge_sort(coins, size);

  // allocate memory for change array
  int *change = malloc(sizeof(int) * size);
  if (change == NULL) {
    fprintf(stderr,
            "ERROR: memory allocation failed for change in coin_change");
    return NULL;
  }

  int sum_change = 0;
  int k = 0;

  for (int i = 0; i < size; i++) {
    while (sum_change + sorted_coins[i] <= amount) {
      sum_change += sorted_coins[i];
      change[k++] = sorted_coins[i];
    }

    if (sum_change == amount) {
      for (int i = 0; i < k; i++) {
        change[k] = 0;
      }
      // set sentinel
      change[k] = 0;
      return change;
    }
  }

  /* printf("\nfinal sum_change = %d\n", sum_change); */

  free(change);
  return NULL;
}
