#!/bin/bash

FUNCTIONS_DIR="../functions"
MAIN_COMPILATION_PATH="../execs/main"
MAIN_SOURCE="../main.c"

# Compile the individual C files in the functions directory
gcc -c \
    "$FUNCTIONS_DIR/initialize_hash_table.c" \
    "$FUNCTIONS_DIR/traverse.c" \
    "$FUNCTIONS_DIR/simple_hash.c" \
    "$FUNCTIONS_DIR/my_strdup.c" \
    "$FUNCTIONS_DIR/search.c" \
    "$FUNCTIONS_DIR/add.c" \
    "$FUNCTIONS_DIR/delete_key.c"


# link the object files with the test file and cunit library
gcc -o "$MAIN_COMPILATION_PATH" "$MAIN_SOURCE" \
    initialize_hash_table.o traverse.o simple_hash.o my_strdup.o search.o add.o delete_key.o\
    -lcunit

# Clean up object files after linking (optional)
rm *.o

# Run the test (optional, you can comment this out if you prefer not to run automatically)
"$MAIN_COMPILATION_PATH"
    


