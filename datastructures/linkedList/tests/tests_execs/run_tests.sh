#!/bin/bash

# Compile and run each test file in the current directory

for test_file in *.c; do
    # Extract the test name without the extension
    test_name="${test_file%.c}"

    # Compile the test
    gcc -o "$test_name" "$test_file" -lcunit

    # Check if the compilation was successful
    if [ $? -eq 0 ]; then
        echo "Running $test_name"
        ./"$test_name"
    else
        echo "Compilation failed for $test_name"
    fi
done

