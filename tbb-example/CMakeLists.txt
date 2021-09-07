cmake_minimum_required(VERSION 3.10.0)

project(tbb-example CXX)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules/)

add_library(tbb-helper INTERFACE)

# Utilities to automatically download missing dependencies
include(cmake/Dependencies.cmake)
find_or_download_package(
    NAME TBB
    VERSION 2021
    URL https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.3.0.tar.gz
    COMPONENTS tbb
    URL_HASH SHA256=8f616561603695bbb83871875d2c6051ea28f8187dbe59299961369904d1d49e
    CONFIGURE_ARGS -DTBB_TEST=OFF -DTBB_EXAMPLES=OFF -DTBB4PY_BUILD=OFF)# -DBUILD_SHARED_LIBS=ON)
find_package(Threads REQUIRED)

target_include_directories(tbb-helper INTERFACE
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/_deps/local/include>)

target_link_libraries(tbb-helper
    INTERFACE TBB::tbb Threads::Threads $<$<PLATFORM_ID:Linux>:rt>)
target_compile_options(tbb-helper
    PRIVATE ${TBB_CXX_STD_FLAG})

add_executable(tbb-example tbb-example.cpp)

target_link_libraries(tbb-example tbb-helper)
