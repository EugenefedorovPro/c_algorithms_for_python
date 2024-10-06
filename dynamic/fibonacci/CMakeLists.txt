cmake_minimum_required(VERSION 3.5)

# Set the project name and specify the language as C
project(fibonacci C)

# Find Python3 and include the necessary directories and libraries
find_package(Python3 REQUIRED COMPONENTS Development)

# Set the source files for the module and the C executable
set(SOURCE_FILES fibonacci.c)

# Define the shared library for the Python extension (omit main.c and python_api.c)
add_library(fibonacci MODULE python_api.c ${SOURCE_FILES})

# Link the Python3 include directories and libraries for the Python extension
target_include_directories(fibonacci PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(fibonacci PRIVATE ${Python3_LIBRARIES})

# Rename the output file to match the Python extension format
set_target_properties(fibonacci PROPERTIES PREFIX "" SUFFIX ".so")

# Define the executable target (standalone C executable)
add_executable(fibonacci_exe main.c ${SOURCE_FILES})

# Standard include directories for the standalone executable
target_include_directories(fibonacci_exe PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(fibonacci_exe PRIVATE ${Python3_LIBRARIES})
