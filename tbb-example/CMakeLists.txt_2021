cmake_minimum_required(VERSION 3.10.0)

project(tbb-example CXX)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

add_executable(tbb-example tbb-example.cpp)

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

target_link_libraries(tbb-example
    INTERFACE TBB::tbb Threads::Threads $<$<PLATFORM_ID:Linux>:rt>
    INTERFACE ${Quadmath_IMPORTED_TARGET} ${GMP_LIBRARIES})
target_compile_options(tbb-example
    PRIVATE ${TBB_CXX_STD_FLAG})

