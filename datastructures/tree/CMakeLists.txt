cmake_minimum_required(VERSION 3.5)

# Set the project name and specify the language as C
project(tree C)

# Find Python3 and include the necessary directories and libraries
find_package(Python3 REQUIRED COMPONENTS Development)

# Add CUnit include directory
include_directories(/usr/include/CUnit)

# Manually specify cJSON include directory and library
include_directories(/usr/local/include/cjson)
link_directories(/usr/local/lib)

# Set the source files for the module and the C executable
set(SOURCE_FILES
 ../../sorting/functions/quick.c
 ./functions/free_tree_debug.c
 ./functions/copy_array_int.c
 ./functions/initiate_tree_debug.c
 ./functions/copy_tree.c
 ./functions/rbt_utils.c
 ./functions/remove_rbt.c
 ./functions/insert_bst.c
 ./functions/create_node.c
 ./functions/create_binary_search_tree.c
 ./functions/queue.c
 ./functions/create_binary_tree.c
 ./functions/free_tree.c
 ./functions/traverse_preorder.c
 ./functions/heapify.c
 ./functions/traverse_level_order.c
 ./functions/tree_to_dot.c
 ./functions/insert_rbt.c
 ./functions/stack.c
)

# Define the shared library for the Python extension
add_library(tree MODULE python_api.c ${SOURCE_FILES})

# Link the necessary libraries for the Python extension
target_include_directories(tree PRIVATE ${Python3_INCLUDE_DIRS} /usr/local/include/cjson)
target_link_libraries(tree PRIVATE ${Python3_LIBRARIES} cjson)

# Set properties for the shared library output
set_target_properties(tree PROPERTIES PREFIX "" SUFFIX ".so")

# Define the executable target (standalone C executable)
add_executable(tree_exe main.c ${SOURCE_FILES})

# Link libraries for the standalone executable
target_include_directories(tree_exe PRIVATE ${Python3_INCLUDE_DIRS} /usr/local/include/cjson)
target_link_libraries(tree_exe PRIVATE ${Python3_LIBRARIES} cjson m) # Add 'm' for math library

# Include CTest module
include(CTest)
enable_testing()

# Function to add test executables with common settings
macro(add_test_executable test_name)
  add_executable(${test_name} tests/${test_name}.c ${SOURCE_FILES})
  target_link_libraries(${test_name} PRIVATE /usr/lib/x86_64-linux-gnu/libcunit.so cjson m) # Add 'm' for math library
  add_test(${test_name} ${test_name}) # Add the test to CTest
endmacro()

# Add test executables
add_test_executable(test_traverse_preorder)
add_test_executable(test_heapify)
add_test_executable(test_traverse_level_order)
add_test_executable(test_queue)
add_test_executable(test_create_binary_search_tree)
add_test_executable(test_insert_rbt)
add_test_executable(test_stack)
add_test_executable(test_insert_bst)
add_test_executable(test_remove_rbt)
add_test_executable(test_rbt_utils)
add_test_executable(test_copy_tree)
add_test_executable(test_copy_array_int)
add_test_executable(test_remove_rand_nodes_from_rbt)
add_test_executable(test_check_removes_in_multiple_trees)
add_test_executable(test_refresh_arr_of_removed_numbers)
