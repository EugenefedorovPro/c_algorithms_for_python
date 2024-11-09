#include <stdio.h>
#include <stdlib.h>

#include "../declarations.h"

int *copy_array_int(int *original_arr, size_t size) {
    int *new_arr = malloc(sizeof(int) * size);

    if (new_arr == NULL) {
        fprintf(stderr, "memory allocation failed for new_arr");
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        new_arr[i] = original_arr[i];
    }
    return new_arr;

}
