# set the minimum required version of cmake that you need
cmake_minimum_required(VERSION 3.10)

# set the cmake standard and requires it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the name and version of your project
project(example VERSION 1.0)

# add an executable with name and all required source files
add_executable(example main.cpp)

