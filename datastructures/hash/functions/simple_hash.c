#include <stdio.h>

#include "../declarations.h"

// returns index for key to be set in hash table
int simpleHash(char *key, HashTable *table) {
    printf("\n--------------------\n");
    printf("\n start of hash calculation for the key = '%s'\n", key);

    if (!key || !table) {
        fprintf(stderr, "Error: key or table is NULL\n");
        return -1;
    }

    if (table->capacity <= 0) {
        fprintf(stderr, "Error: hash table capacity is 0\n");
        return -1;
    }

    int sumChar = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        printf("Character key %c ASCII value = %d\n", key[i], key[i]);
        sumChar += key[i];
    }
    int hash = sumChar % table->capacity;
    printf("\n end of hash calculation for the key = '%s' with the hash = %d\n",
           key,
           hash);

    printf("\n--------------------\n");
    return hash;
}
