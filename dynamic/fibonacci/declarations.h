#ifndef DECLARATIONS_H
#define DECLARATIONS_H

typedef struct KeyValue {
  int num;
  int fib;
} KeyValue;

int find(int number, KeyValue *dict);
int fibonacci(int number);
#endif
