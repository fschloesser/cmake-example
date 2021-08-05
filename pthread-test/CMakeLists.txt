cmake_minimum_required(VERSION 3.10)

project(test)

# the following checks if threads is there
find_package(Threads REQUIRED)
# Fail if returned library is not pthread
if (NOT CMAKE_USE_PTHREADS_INIT)
        message(STATUS "POSIX threads: not found")
else()
        message(STATUS "POSIX threads: found")
        message(STATUS ${CMAKE_THREADS_LIBS_INIT})
endif()
