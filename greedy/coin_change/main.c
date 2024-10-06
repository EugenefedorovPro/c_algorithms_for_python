#include "declarations.h"

int main() {
  int coins[] = {2, 1, 5};
  int amount = 18;
  size_t size = 3;

  int *result = coin_change(coins, size, amount);
  if (result == NULL) {
    printf("\nNo change for the whole sum available\n");
  }

  printf("\nresult = ");
  for (int i = 0; i < size * 2; i++) {
    // break when sentinel
    if (result[i] == 0) {
      break;
    }
    printf("%d ", result[i]);
  }
  printf("\n");

  return 0;
}
