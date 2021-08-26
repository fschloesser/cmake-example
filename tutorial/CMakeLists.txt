# set the minimum required version of cmake that you need
cmake_minimum_required(VERSION 3.10)

# set the cmake standard and requires it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the name and version of your project
project(cmake-example VERSION 1.0)

# add the subdirectory apple to the project
add_subdirectory(apple)
<<<<<<< Updated upstream
# add the subdirectory pear to the project
add_subdirectory(pear)
# add the subdirectory orange to the project
add_subdirectory(orange)

# find package Boost version 1.72 and the asio component
find_package(Boost 1.72 REQUIRED COMPONENTS chrono)
# Caveat: Boost needs Threads, so add this as well
find_package(Threads REQUIRED)

# explicitly finding your nonstandard package, giving the name of the library with the lib prefix removed; by default it searches in standard paths, but you can give more locations if you want or need
find_library(ZLIB z REQUIRED PATHS /usr/lib/)
# manually set include dir
set(ZLIB_INCLUDE_DIR /usr/include)

# add an executable with name and all required source files
add_executable(hello main.cpp)
# link the to the hello executable
# - the apple library
# - the boost libraries and dependencies
# - the zlib library
target_link_libraries(hello PUBLIC apple Boost::chrono ${CMAKE_THREAD_LIBS_INIT} ${ZLIB})
# include the boost headers for target hello
target_include_directories(hello PUBLIC ${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR})
