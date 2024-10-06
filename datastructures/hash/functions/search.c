#include <stdio.h>
/* #include <stdlib.h> */
#include <string.h>

#include "../declarations.h"

// linear search of value by key

int search(char *key, HashTable *table) {
    printf("\n--------------------\n");
    printf("\nsearch() starts looking for a value to the key = '%s'\n", key);

    if (!key || !table) {
        fprintf(stderr, "Error: key or table is NULL\n");
        return -1;
    }

    keyValue *pairs = table->pairs;
    for (size_t i = 0; i < table->capacity; i++) {
        if (pairs[i].key && strcmp(pairs[i].key, key) == 0) {
            int value = pairs[i].value;
            printf("\n search() has found the value '%d' to the key '%s'\n",
                   value,
                   key);
            printf("\n--------------------\n");
            return value;
        }
    }
    printf("\n search() has not found a value to the key '%s'\n", key);
    return -1;
}
