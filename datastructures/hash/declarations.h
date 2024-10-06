#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdlib.h>

typedef struct keyValue {
    char *key;
    int value;
} keyValue;

typedef struct HashTable {
    keyValue *pairs;
    size_t size;
    size_t capacity;
} HashTable;

HashTable *initialize_hash_table();
void traverse(HashTable *table);
int simpleHash(char *key, HashTable *table);
int search(char *key, HashTable *table);
void add(char *key, int value, HashTable **table);
char *my_strdup(const char *str);
void deleteKey(const char *key, HashTable **table);

#endif
