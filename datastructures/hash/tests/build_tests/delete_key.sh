#!/bin/bash

FUNCTIONS_DIR="../../functions"
TEST_COMPILATION_PATH="../execs/test_delete_key"
TEST_SOURCE="../test_delete_key.c"

# Compile the individual C files in the functions directory
gcc -c \
    "$FUNCTIONS_DIR/initialize_hash_table.c" \
    "$FUNCTIONS_DIR/traverse.c" \
    "$FUNCTIONS_DIR/simple_hash.c" \
    "$FUNCTIONS_DIR/add.c" \
    "$FUNCTIONS_DIR/my_strdup.c" \
    "$FUNCTIONS_DIR/delete_key.c" \
    "$FUNCTIONS_DIR/search.c" 


# link the object files with the test file and cunit library
gcc -o "$TEST_COMPILATION_PATH" "$TEST_SOURCE" \
    initialize_hash_table.o traverse.o simple_hash.o my_strdup.o search.o delete_key.o add.o\
    -lcunit

# Clean up object files after linking (optional)
rm *.o

# Run the test (optional, you can comment this out if you prefer not to run automatically)
"$TEST_COMPILATION_PATH"
    


