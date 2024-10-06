#!/bin/bash

FUNCTIONS_DIR="../../functions"
TEST_COMPILATION_PATH="../execs/test_my_strdup"
TEST_SOURCE="../test_my_strdup.c"

# Compile the individual C files in the functions directory
gcc -c \
    "$FUNCTIONS_DIR/my_strdup.c" 


# link the object files with the test file and cunit library
gcc -o "$TEST_COMPILATION_PATH" "$TEST_SOURCE" \
     my_strdup.o\
    -lcunit

# Clean up object files after linking (optional)
rm *.o

# Run the test (optional, you can comment this out if you prefer not to run automatically)
"$TEST_COMPILATION_PATH"
    


