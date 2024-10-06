#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

// initialize the hash table of empty key-value pairs of a certain size
HashTable *initialize_hash_table() {
    size_t startSize = 10;
    HashTable *table = malloc(sizeof(HashTable));
    if (table == NULL) {
        printf("No memory has been allocated to initialize_hash_table");
        return NULL;
    }
    keyValue *emptyPairs = malloc(startSize * sizeof(keyValue));
    if (emptyPairs == NULL) {
        printf("No memory has been allocated to pairs in initialize_hash_table");
        free(table);
        return NULL;
    }
    for (size_t i = 0; i < startSize; i++) {
        emptyPairs[i].key = NULL;
        emptyPairs[i].value = 0;
    }
    table->pairs = emptyPairs;
    table->size = 0;
    table->capacity = startSize;

    printf("\n--------------------\n");
    printf("\nEmpty hash table has been initiated with star size = %zu\n",
           startSize);
    printf("\n--------------------\n");

    return table;
}
