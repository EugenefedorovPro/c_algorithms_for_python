cmake_minimum_required(VERSION 3.5)

# Set the project name and specify the language as C
project(coin_change C)

# Find Python3 and include the necessary directories and libraries
find_package(Python3 REQUIRED COMPONENTS Development)

# Set the source files for the module and the C executable
set(SOURCE_FILES merge_sort.c coin_change.c)

# Define the shared library for the Python extension (omit main.c and python_api.c)
add_library(coin_change MODULE python_api.c ${SOURCE_FILES})

# Link the Python3 include directories and libraries for the Python extension
target_include_directories(coin_change PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(coin_change PRIVATE ${Python3_LIBRARIES})

# Rename the output file to match the Python extension format
set_target_properties(coin_change PROPERTIES PREFIX "" SUFFIX ".so")

# Define the executable target (standalone C executable)
add_executable(coin_change_exe main.c ${SOURCE_FILES})

# Standard include directories for the standalone executable
target_include_directories(coin_change_exe PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(coin_change_exe PRIVATE ${Python3_LIBRARIES})
