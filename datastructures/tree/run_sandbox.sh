#!/bin/bash

# Compile the program
gcc -o./build/sandbox \
    sandbox.c \
    ./functions/free_tree.c \
    ./functions/create_node.c \
    ./functions/traverse_level_order.c \
    ./functions/queue.c \
    ./functions/create_binary_search_tree.c \
    ../../sorting/functions/quick.c \
    ../../utils/print_arr.c \
    -I/usr/local/include/cjson \
    -L/usr/local/lib \
    -lcjson -lm

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Run the executable
./build/sandbox
