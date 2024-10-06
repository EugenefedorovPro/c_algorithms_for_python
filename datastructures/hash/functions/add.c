#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void add(char *key, int value, HashTable **dict) {
    // check args not null
    if (key == NULL || dict == NULL) {
        fprintf(stderr, "Error: key, value or table = NULL\n");
        return;
    }

    HashTable *table = *dict;

    // Enhance capacity if necessary
    if (table->size >= table->capacity / 2) {
        printf("\n--------------------\n");
        printf("\nCapacity is to be enlarged from %zu to %zu \n",
               table->capacity,
               table->capacity + 10);
        printf("\n--------------------\n");

        // Create a new hash table with double capacity
        HashTable *newTable = malloc(
            sizeof(HashTable) + (sizeof(keyValue) * (table->capacity + 10)));
        if (newTable == NULL) {
            free(newTable);
            fprintf(stderr,
                    "Error: memory allocation failed for new hash table\n");
            return;
        }

        // Initialize new table
        newTable->capacity = table->capacity + 10;
        newTable->size = 0;  // Reset size for new table
        newTable->pairs =
            (keyValue *)(newTable + 1);  // Adjust to point to pairs array

        // Initialize new pairs array
        for (size_t i = 0; i < newTable->capacity; i++) {
            newTable->pairs[i].key = NULL;  // Initialize keys to NULL
            newTable->pairs[i].value = 0;   // Initialize values to 0
        }

        // Rehash existing keys
        for (size_t i = 0; i < table->capacity; i++) {
            if (table->pairs[i].key) {
                int newHash = simpleHash(table->pairs[i].key, newTable);

                // handle collisions with linear probing
                while (newTable->pairs[newHash].key != NULL) {
                    newHash = (newHash + 1) % newTable->capacity;
                }

                newTable->pairs[newHash].key =
                    my_strdup(table->pairs[i].key);  // Duplicate the key
                newTable->pairs[newHash].value = table->pairs[i].value;
                newTable->size++;
            }
        }

        // free old pairs and table
        for (size_t i = 0; i < table->capacity; i++) {
            free(table->pairs[i].key);
        }

        /* free(table->pairs);  // Free old pairs */
        free(table);       // Free old table
        *dict = newTable;  // Point dict to new table
        table = newTable;  // Update local table reference
    }

    // Calculate hash for new key
    int hash = simpleHash(key, table);
    keyValue *pairs = table->pairs;

    // Insert key-value pair
    if (!pairs[hash].key) {
        pairs[hash].key = my_strdup(key);  // Duplicate the key
        pairs[hash].value = value;
    } else {
        // Handle collision with linear probing
        for (size_t i = (hash + 1) % table->capacity; i != hash;
             i = (i + 1) % table->capacity) {
            if (!pairs[i].key) {
                pairs[i].key = my_strdup(key);  // Duplicate the key
                pairs[i].value = value;
                break;
            }
        }
    }

    table->size++;
}
