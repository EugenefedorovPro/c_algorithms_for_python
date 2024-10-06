#include "declarations.h"
#include <stdio.h>

int main() {
  int number = 10;
  int result = fibonacci(number);
  printf("\nfibonacci result of number '%d'= %d\n\n", number, result);

  return 0;
}
