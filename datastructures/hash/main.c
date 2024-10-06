#include <stdio.h>

#include "declarations.h"

int main() {
    HashTable *table = initialize_hash_table();
    add("time", 10, &table);
    add("being", 20, &table);
    add("Heidegger", 30, &table);
    deleteKey("Heidegger", &table);
    traverse(table);
    printf("\ntime value = %d\n", search("time", table));

    return 0;
}
