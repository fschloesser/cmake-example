# set the minimum required version of cmake that you need
cmake_minimum_required(VERSION 3.10)

# set the cmake standard and requires it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the name and version of your project
project(cmake-example VERSION 1.0)

# create a static library holding the Apple files
add_library(apple STATIC apple/Apple.cpp)
# include header files from apple/include folder; CMAKE_CURRENT_SOURCE_DIR is the location of this CMakeLists.txt
target_include_directories(apple PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/apple/include)

# add an executable with name and all required source files
add_executable(hello main.cpp)
# link the apple library to the hello executable
target_link_libraries(hello PUBLIC apple)
