#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

void deleteKey(const char *key, HashTable **table) {
    // case #1 - key or table are empty
    if (key == NULL || table == NULL) {
        fprintf(stderr, "Error: key or table == NULL\n");
        return;
    }

    HashTable *dict = *table;

    // case #2 delete key, which exists,
    // if key does not exist, do nothing
    for (size_t i = 0; i < dict->capacity; i++) {
        if (dict->pairs[i].key != NULL &&
            strcmp(key, dict->pairs[i].key) == 0) {
            free(dict->pairs[i].key);
            dict->pairs[i].key = NULL;
            dict->pairs[i].value = 0;
            dict->size--;
            break;
        }
    }

    // case #3 if size > 10 && size <= (capacity - 10)  / 2
    if (dict->capacity > 10 && dict->size <= (dict->capacity - 10) / 2) {
        // decrease capacity
        HashTable *newDict = malloc(sizeof(HashTable) +
                                    sizeof(keyValue) * (dict->capacity - 10));
        if (newDict == NULL) {
            fprintf(stderr, "Error: memory allocation failed for newDict\n");
            return;
        }

        newDict->capacity = dict->capacity - 10;
        newDict->size = 0;
        newDict->pairs = (keyValue *)(newDict + 1);

        // initialize newDict
        for (size_t i = 0; i < newDict->capacity; i++) {
            newDict->pairs[i].key = NULL;
            newDict->pairs[i].value = 0;
        }

        // rehash
        for (size_t i = 0; i < dict->capacity; i++) {
            if (dict->pairs[i].key != NULL) {
                int newHash = simpleHash(dict->pairs[i].key, newDict);

                // case #4 - handle collision
                while (newDict->pairs[newHash].key != NULL) {
                    newHash = (newHash + 1) % newDict->capacity;
                    printf(
                        "\nCollision while reducing size of hash table "
                        "solved\n");
                }

                newDict->pairs[newHash].key = my_strdup(dict->pairs[i].key);
                newDict->pairs[newHash].value = dict->pairs[i].value;
            }
        }

        // free dict
        for (size_t i = 0; i < dict->capacity; i++) {
            free(dict->pairs[i].key);
        }
        free(dict);

        *table = newDict;
        return;
    }
}
