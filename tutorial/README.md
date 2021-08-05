# CMake Tutorial Chapter 0

This is a cmake tutorial where we create the build system for a c++ project.

# CMake Tutorial Chapter 1 - A very basic CMake file

There is a simple c++ program called `main.cpp` that prints a message.

To compile the program with the gnu c compiler simply run
```
g++ -o cmake-example main.cpp
```

or from this folder run
```
g++ -o cmake-example main.cpp
```

This will generate an executable called `cmake-example` that you can run by calling
```
./cmake-example
```

To build the file with cmake you can run
```
cmake .
make
./cmake-example
```

CMake will generate a bunch of files
- a binary again called `cmake-example`
- a `Makefile` that is used to compile
- a folder `CMakeFiles` that holds TODO
- a `CMakeCache.txt` that contains all cached CMake variables
- a file called `cmake_install.cmake` TODO

These files are generated every time and you don't need to keep track of them.
Since you might not want all of them in your main folder you can run CMake from a build folder
```
mkdir build
cd build
cmake ..
make
./cmake-example
```

This build folder can safely be deleted if you want a fresh build and keeps your project folder clean.
Note: The folder does not need to be called `build`, but for this tutorial we will keep that name.

