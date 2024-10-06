/*

Index	0	1	2	3	4	5	6
Key	foo	bar	bazz	buzz	bob	jane	x
Value	10	42	36	7	11	100	200

*/

#include <stdio.h>
#include <string.h>

typedef struct Item {
  char *key;
  int value;
} Item;

int linearSearch(Item *items, const char *key, size_t size);

int main() {
  Item items[] = {
      {"foo", 10}, {"bar", 42}, {"bazz", 46}, {"bob", 100}, {"jane", 200}};

  size_t len = sizeof(items) / sizeof(items[0]);
  const char keyToFind[] = "bob";

  int result = linearSearch(items, keyToFind, len);
  if (result == 1) {
    printf("There is no key = %s in the array", keyToFind);
  }

  return 0;
}

int linearSearch(Item *items, const char *key, size_t size) {
  for (int i = 0; i < size; i++) {

    if (strcmp(items[i].key, key) == 0) {
      printf("%d\n", items[i].value);
      return 0;
    }
  }

  return 1;
}
