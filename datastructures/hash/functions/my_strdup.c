#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../declarations.h"

char *my_strdup(const char *str) {
    if (str == NULL) {
        fprintf(stderr, "Error: str = NULL\n");
        return NULL;
    }
    size_t size = strlen(str);

    char *newStr = malloc((size + 1));
    if (newStr == NULL) {
        fprintf(stderr, "Error: memory allocation failed for newStr\n");
        return NULL;
    }
    strcpy(newStr, str);
    return newStr;
}
