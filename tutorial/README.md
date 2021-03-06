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
- a binary called `cmake-example`
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

# CMake Tutorial Chapter 2 - Adding a header file

Now we are adding an `include` folder that holds the header files and tell CMake where these are with the `target_include_directories`.
Here the target is `hello`, that we declared with the `add_executable` command.
Targets can depend on each other and are either executables or libraries.

# CMake Tutorial Chapter 3 - Having multiple source files

If you have multiple source files, you want to keep them in a separate folder, we will call it `src`.
It holds all your source files and helps you keep organized.

For that we split the `Apple.h` file into a header and a `.cpp` file and place `Apple.cpp` into the `src` folder.

Then we also add the information on how to find this to our CMakeLists.txt file.

# CMake Tutorial Chapter 4 - Adding a library

Creating a library from multiple source files allows you to bundle and reuse functions in other projects.

We move the Apple files into a separate folder called `apple` and then create a library by using the `add_library` command.

We tell the library where to find its include files, and since the `apple` library now knows that, the `hello` executable does not need this information anymore.

Then we link the `hello` executable to the `apple` library.

# CMake Tutorial Chapter 5 - Independent library in subdirectory

Now we can also move the information about how to build the library from the main `CMakeLists.txt` file to its subfolder `apple` and include it with `add_subdirectory`.

# CMake Tutorial Chapter 6 - Depending on an external library

Sometimes you just need to link an external library, for that you can use the `find_package` command.
This command has two modes, Module mode and Config mode, that use `FindXXX.cmake` and `XXXConfig.cmake` respectively.
If your library was found successfully you can use variables like `XXX_INCLUDE_DIR` and `XXX_LIBRARIES` for linking and including into your target.
Some packages also export targets instead of these variables.
There is no works for all here, you need to read the documentation.

Notes:
- If you add the `REQUIRED` parameter into the `find_package` call cmake will fail and stop if the package is not found.
- You can specify subcomponents and a (minimal) version.
- There are many Modules already included in CMake but you can also write your own `FindXXX.cmake` file for custom packages.
