# CMakeLists.txt inside apple folder.
# CMAKE_CURRENT_SOURCE_DIR is now the location of this CMakeLists.txt

# create a static library holding the Apple files
add_library(apple STATIC Apple.cpp)
# include header files from include folder
target_include_directories(apple PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
