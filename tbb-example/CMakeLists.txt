cmake_minimum_required(VERSION 3.10.0)

project(tbb-example CXX)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

add_executable(tbb-example tbb-example.cpp)

set(THIS_TBB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/tbb/)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules/)

# find_package will search for available TBBConfig using variables CMAKE_PREFIX_PATH and TBB_DIR.
# if find_package fails, the user can pass TBB_LIBRARY_DIR and TBB_INCLUDE_DIR
find_package(TBB 2021 COMPONENTS tbb)
if(NOT TBB_FOUND)
    option(TBB_TEST OFF)
    option(TBB_EXAMPLES OFF)
    option(TBB4PY_BUILD OFF)
    option(CMAKE_BUILD_SHARED_LIBS OFF)
    set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
    set(BUILD_SHARED_LIBS OFF)
    add_subdirectory(${THIS_TBB_DIR} EXCLUDE_FROM_ALL)
    set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD})
endif()
find_package(Threads REQUIRED)

target_link_libraries(tbb-example
    PRIVATE TBB::tbb Threads::Threads $<$<PLATFORM_ID:Linux>:rt>)
target_compile_options(tbb-example
    PRIVATE ${TBB_CXX_STD_FLAG})

