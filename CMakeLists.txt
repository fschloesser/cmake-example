# set the minimum required version of cmake that you need
cmake_minimum_required(VERSION 3.10)

# set the cmake standard and requires it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the name and version of your project
project(cmake-example VERSION 1.0)

# find all files ending in .cpp from the src folder and place them in the SRC_FILES variable
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# add an executable with name and all required source files
add_executable(hello main.cpp ${SRC_FILES})

# include header files from include folder; CMAKE_CURRENT_SOURCE_DIR
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
