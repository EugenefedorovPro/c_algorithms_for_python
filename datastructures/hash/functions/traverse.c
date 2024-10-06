#include <stdio.h>

#include "../declarations.h"

void traverse(HashTable *dict) {
    printf("\n--------------------\n");
    printf("\nstart traversal of capacity - %zu\n", dict->capacity);
    for (size_t i = 0; i < dict->capacity; i++) {
        printf("\n %zu - key = %s, value = %d\n", i, dict->pairs[i].key, dict->pairs[i].value);
    }
    printf("\nend traversal of capacity - %zu\n", dict->capacity);
    printf("\n--------------------\n");
}
