# CMakeLists.txt inside orange folder.
# CMAKE_CURRENT_SOURCE_DIR is now the location of this CMakeLists.txt

# create a static library holding the Orange files
add_library(orange STATIC Orange.cpp)
# include header files from include folder
# PUBLIC headers are for building the lib and the source using the lib
# PRIVATE headers are for building the lib but _not_ for the source using the lib
# INTERFACE headers are for building the source using the lib but _not_ for the lib itself
target_include_directories(orange PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
