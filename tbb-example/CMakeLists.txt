cmake_minimum_required(VERSION 3.10.0)

project(tbb-example CXX)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

add_executable(tbb-example tbb-example.cpp)

# find_package will search for available TBBConfig using variables CMAKE_PREFIX_PATH and TBB_DIR.
# if find_package fails, the user can pass TBB_LIBRARY_DIR and TBB_INCLUDE_DIR
find_package(TBB 2 QUIET COMPONENTS tbb)
if(TBB_FOUND)
    set(TBB_IMPORTED_TARGET TBB::tbb)
else()
    find_library(TBB_LIBRARY
        NAMES tbb libtbb.so.2
        REQUIRED
        PATHS ${TBB_LIBRARY_DIR})
    set(TBB_IMPORTED_TARGET ${TBB_LIBRARY})
    find_path(TBB_INCLUDE_DIR
        NAMES tbb/tick_count.h
        REQUIRED
        PATHS ${TBB_INCLUDE_DIR})
endif()


target_link_libraries(tbb-example
    ${TBB_IMPORTED_TARGET}          # Link TBB imported targets to the executable; "TBB::tbb" can be used instead of "${TBB_IMPORTED_TARGETS}".
    $<$<PLATFORM_ID:Linux>:rt>)     # Link "rt" library on Linux
target_include_directories(tbb-example
    PUBLIC ${TBB_INCLUDE_DIR})
