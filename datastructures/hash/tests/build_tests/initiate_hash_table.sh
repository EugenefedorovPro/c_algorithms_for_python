#!/bin/bash

FUNCTIONS_DIR="../../functions"
TEST_COMPILATION_PATH="../execs/test_initiate_hash_table"
TEST_SOURCE="../test_initialize_hash_table.c"

# Compile the individual C files in the functions directory
gcc -c \
    "$FUNCTIONS_DIR/initialize_hash_table.c" \
    "$FUNCTIONS_DIR/traverse.c" \

# link the object files with the test file and cunit library
gcc -o "$TEST_COMPILATION_PATH" "$TEST_SOURCE" \
    initialize_hash_table.o traverse.o \
    -lcunit

# Clean up object files after linking (optional)
rm *.o

# Run the test (optional, you can comment this out if you prefer not to run automatically)
"$TEST_COMPILATION_PATH"
