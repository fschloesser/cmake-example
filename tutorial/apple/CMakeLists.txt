# CMakeLists.txt inside apple folder.
# CMAKE_CURRENT_SOURCE_DIR is now the location of this CMakeLists.txt

# create a static library holding the Apple files
add_library(apple STATIC Apple.cpp)
# include header files from include folder
# PUBLIC headers are for building the lib and the source using the lib
# PRIVATE headers are for building the lib but _not_ for the source using the lib
# INTERFACE headers are for building the source using the lib but _not_ for the lib itself
target_include_directories(apple PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
