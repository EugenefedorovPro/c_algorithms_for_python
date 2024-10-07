cmake_minimum_required(VERSION 3.5)

# Set the project name and specify the language as C
project(sorting C)

# Find Python3 and include the necessary directories and libraries
find_package(Python3 REQUIRED COMPONENTS Development)

# Add CUnit include directory
include_directories(/usr/include/CUnit)

# Set the source files for the module and the C executable
set(SOURCE_FILES ./functions/merge_inplace.c ./functions/quick.c ./functions/merge.c ./functions/insertion.c ./functions/selection.c ./functions/bubble.c ./functions/factory.c)

# Define the shared library for the Python extension
add_library(sorting MODULE python_api.c ${SOURCE_FILES})

# Link the necessary libraries for the Python extension
target_include_directories(sorting PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(sorting PRIVATE ${Python3_LIBRARIES})

# Set properties for the shared library output
set_target_properties(sorting PROPERTIES PREFIX "" SUFFIX ".so")

# Define the executable target (standalone C executable)
add_executable(sorting_exe main.c ${SOURCE_FILES})

# Link libraries for the standalone executable
target_include_directories(sorting_exe PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(sorting_exe PRIVATE ${Python3_LIBRARIES})

# Function to add test executables with common settings
macro(add_test_executable test_name)
    add_executable(${test_name} tests/${test_name}.c ${SOURCE_FILES})
    target_link_libraries(${test_name} PRIVATE /usr/lib/x86_64-linux-gnu/libcunit.so)
endmacro()

# Add test executables for selection and bubble sort
add_test_executable(test_factory)
add_test_executable(test_selection)
add_test_executable(test_bubble)
add_test_executable(test_insertion)
add_test_executable(test_merge)
add_test_executable(test_merge_inplace)
add_test_executable(test_quick)

