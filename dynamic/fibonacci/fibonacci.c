#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

int find(int number, KeyValue *dict) {
  if (number <= 2) {
    return 1;
  }

  // check if fib value is available in cache
  if (dict[number].num != -1) {
    int fib = dict[number].fib;
    printf("\nreturned '%d' from cache\n", fib);
    return fib;
  }

  int fib1 = find(number - 2, dict);
  int fib2 = find(number - 1, dict);

  /* printf("\nnumber = %d\n", number); */
  dict[number].num = number;
  dict[number].fib = fib1 + fib2;

  return fib1 + fib2;
}

int fibonacci(int number) {
  KeyValue *dict = malloc(sizeof(KeyValue) * (number + 1));

  // initialize dict
  for (int i = 0; i <= number; i++) {
    dict[i].num = -1;
    dict[i].fib = -1;
  }
  // initiate base cases
  dict[0].num = 0;
  dict[0].fib = 0;
  dict[1].num = 1;
  dict[1].fib = 1;
  dict[2].num = 2;
  dict[2].fib = 1;

  int fib = find(number, dict);

  printf("\nmemoization: \n");
  for (int i = 0; i < number; i++) {
    printf("\ni = %d, num = %d, fib = %d\n", i, dict[i].num, dict[i].fib);
  }
  free(dict);

  return fib;
}
