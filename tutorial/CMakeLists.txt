# set the minimum required version of cmake that you need
cmake_minimum_required(VERSION 3.10)

# set the cmake standard and requires it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the name and version of your project
project(cmake-example VERSION 1.0)

# add the subdirectory apple to the project
add_subdirectory(apple)

# find package Boost version 1.72 and the asio component
find_package(Boost 1.72 REQUIRED COMPONENTS chrono)
# Caveat: Boost needs Threads, so add this as well
find_package(Threads REQUIRED)

# add an executable with name and all required source files
add_executable(hello main.cpp)
# link the to the hello executable
# - the apple library
# - the boost libraries and dependencies
target_link_libraries(hello PUBLIC apple Boost::chrono ${CMAKE_THREAD_LIBS_INIT})
# include the boost headers for target hello
target_include_directories(hello PUBLIC ${Boost_INCLUDE_DIRS})
