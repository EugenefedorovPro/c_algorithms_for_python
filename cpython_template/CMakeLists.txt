cmake_minimum_required(VERSION 3.5)

# Set the project name and specify the language as C
project(rename C)

# Find Python3 and include the necessary directories and libraries
find_package(Python3 REQUIRED COMPONENTS Development)

# Add CUnit include directory
include_directories(/usr/include/CUnit)

# Set the source files for the module and the C executable
set(SOURCE_FILES rename.c)

# Define the shared library for the Python extension (omit main.c and python_api.c)
add_library(rename MODULE python_api.c ${SOURCE_FILES})

# Link the Python3 include directories and libraries for the Python extension
target_include_directories(rename PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(rename PRIVATE ${Python3_LIBRARIES})

# Rename the output file to match the Python extension format
set_target_properties(rename PROPERTIES PREFIX "" SUFFIX ".so")

# Define the executable target (standalone C executable)
add_executable(rename_exe main.c ${SOURCE_FILES})

# Standard include directories for the standalone executable
target_include_directories(rename_exe PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(rename_exe PRIVATE ${Python3_LIBRARIES})

# Add test executable for CUnit tests
add_executable(test_rename tests/test_rename.c ${SOURCE_FILES})

# Link CUnit library to the test executable
target_link_libraries(test_rename PRIVATE /usr/lib/x86_64-linux-gnu/libcunit.so)
