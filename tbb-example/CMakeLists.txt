cmake_minimum_required(VERSION 3.10.0)

project(tbb-example CXX)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

add_executable(tbb-example tbb-example.cpp)

set(THIS_TBB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/tbb/)
list(APPEND CMAKE_MODULE_PATH ${THIS_TBB_DIR}/common/cmake/modules/)

# find_package will search for available TBBConfig using variables CMAKE_PREFIX_PATH and TBB_DIR.
# if find_package fails, the user can pass TBB_LIBRARY_DIR and TBB_INCLUDE_DIR
#find_package(TBB 2020 QUIET COMPONENTS tbb)
find_package(TBB 2021 QUIET COMPONENTS tbb)
if(TBB_FOUND)
    set(TBB_IMPORTED_TARGET TBB::tbb)
else()
    ## TBB 2020
    #find_library(TBB_LIBRARY
    #    NAMES tbb libtbb.so.2
    #    HINTS ${TBB_LIBRARY_DIR})
    # TBB 2021
    find_library(TBB_LIBRARY
        NAMES libtbb.so.12
        HINTS ${TBB_LIBRARY_DIR})
    set(TBB_IMPORTED_TARGET ${TBB_LIBRARY})

    if(TBB_LIBRARY)
        find_path(TBB_INCLUDE_DIR
            NAMES oneapi/tbb/tick_count.h
            REQUIRED
            HINTS ${THIS_TBB_DIR}/include)
        message(STATUS "HOLA ${TBB_INCLUDE_DIR}")
    else()
        option(TBB_TEST OFF)
        option(TBB_EXAMPLES OFF)
        option(TBB4PY_BUILD OFF)
        set(BUILD_SHARED_LIBS OFF)
        add_subdirectory(${THIS_TBB_DIR} EXCLUDE_FROM_ALL)
        set(TBB_IMPORTED_TARGET TBB::tbb)
    endif()
endif()

target_link_libraries(tbb-example
    ${TBB_IMPORTED_TARGET}          # Link TBB imported targets to the executable; "TBB::tbb" can be used instead of "${TBB_IMPORTED_TARGETS}".
    $<$<PLATFORM_ID:Linux>:rt>)     # Link "rt" library on Linux
target_include_directories(tbb-example
    PUBLIC ${TBB_INCLUDE_DIR})


# #--
# # Path to common headers
# include_directories()
#
# if (NOT TARGET TBB::tbb)
#     list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../common/cmake/modules)
#     find_package(TBB REQUIRED COMPONENTS ${tbb})
# endif()
# find_package(Threads REQUIRED)
#
# # Handle C++ standard version.
# if (NOT MSVC)  # no need to cover MSVC as it uses C++14 by default.
#     if (NOT CMAKE_CXX_STANDARD)
#         set(CMAKE_CXX_STANDARD 11)
#     endif()
#     if (CMAKE_CXX${CMAKE_CXX_STANDARD}_STANDARD_COMPILE_OPTION)  # if standard option was detected by CMake
#         set(CMAKE_CXX_STANDARD_REQUIRED ON)
#     endif()
# endif()
#
# set(CMAKE_CXX_EXTENSIONS OFF) # use -std=c++... instead of -std=gnu++...
# # --------------------------------
#
# add_executable(fibonacci fibonacci.cpp)
# target_link_libraries(fibonacci
#                       TBB::tbb
#                       Threads::Threads
#                       $<$<PLATFORM_ID:Linux>:rt>)  # Link "rt" library on Linux
# target_compile_options(fibonacci PRIVATE ${TBB_CXX_STD_FLAG})
#
# set(EXECUTABLE "$<TARGET_FILE:fibonacci>")
#
# if (WIN32)
#     add_custom_target(run_fibonacci set "PATH=$<TARGET_FILE_DIR:TBB::tbb>\\;$ENV{PATH}" & ${EXECUTABLE} )
# else()
#     add_custom_target(run_fibonacci ${EXECUTABLE})
# endif()
#
# add_dependencies(run_fibonacci fibonacci)
#
#
