# Basics on Compilation and Linkage

## Quick overview of compilation and execution process

The process is separated into multiple stages
1 Lexing produces tokens
2 Parsing produces an abstract syntax tree
3 Analysis produces a code flow graph
4 Optimization produces a reduced code flow graph
5 Code gen produces object code
6 Linkage produces a complete executable
7 Loader instructs the OS how to start running the executable

Most of these steps can be done easily and more or less automatic by a compiler.
More complicated is the part that brings it all together, which is what we will focus on: 6. linkage to a complete executable.

## Chapter 1 - simplest of all programs

The code is just in one single file.
This file can be compiled and will produce a simple executable.
```
gcc -o hello main.c
```
Run `make` in `chapter1` to see.

## Chapter 2 - Object files

The code is split up into a main source code file and a helper file with a header.
The functions are declared in the header `helper.h` and they are implemented in `helper.c`.
The compiler first translates each source file into object files, that can then be used by the linker to fit everything together.
The header files are assuring the compiler that in the linking step an object with the given signature will be available.
The classes are compiled by
```
gcc -c helper.c main.c
```
This will produce an object file `helper.o`.
In a second step when we compile the file `main.c` we pass the object file `helper.o`.
```
gcc -o hello main.o helper.o
```

Run `make` in `chapter2` to see.

Note: You can also compile everything together at once:
```
gcc -o hello main.c helper.c
```

An *object file* is almost a full executables.
It contains machine code, but that code still requires a relocation step.
It also contains metadata about the addresses of its variables and functions (these are called symbols) in an associative data structure called a symbol table.
The addresses may not be the final address of the symbol in the final executable.
They also contain some information for the loader etc.

Try to compile `main.c` without providing the objects:
```
>> gcc -o hello main.c
/usr/bin/X11/ld: /tmp/ccMuVNBo.o: in function `main':
main.c:(.text+0x16): undefined reference to `helper'
collect2: error: ld returned 1 exit status
```
This is just what we were expecting, there is a reference to `helper` that cannot be resolved.

If you just have an object file and want to know what symbols it contains you cann inspect it with the `nm` tool.
You can run it on an object or executable file:
```
 >> nm helper.o main.o hello

helper.o:
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T helper
                 U puts

main.o:
                 U _GLOBAL_OFFSET_TABLE_
                 U helper
0000000000000000 T main
                 U puts

hello:
...
0000000000001135 T helper
...
0000000000001148 T main
                 U puts@GLIBC_2.2.5
...
```

Checking out `man 1 nm` we see that displayed is a list of address, type, and symbol name.

Type `U` stands for undefined and means that this symbol is referenced/used but no value was defined.
Type `T` stands for text and means that the symbol was defined in the text section.

`puts` is not defined anywhere but is defined in the dynamically linked c runtime library which is implicitly linked to all executables created by the c compiler.
More on dynamic linking later.

What the linker does is combining the relocated object files into a final exectubale by going through placeholders of addresses and filling them in.

You can use `objdump` to see disassembled assembly instructions and their addresses:
```
>> objdump -d helper.o

helper.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <helper>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # b <helper+0xb>
   b:	e8 00 00 00 00       	callq  10 <helper+0x10>
  10:	90                   	nop
  11:	5d                   	pop    %rbp
  12:	c3                   	retq
```

Use `readelf -s helper.o` to get a list of symbols.
`ELF` stands for `Executable and Linkable Format` and is used by linux's loader.

```
>> readelf -s helper.o

Symbol table '.symtab' contains 12 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS helper.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    8
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    6
     9: 0000000000000000    19 FUNC    GLOBAL DEFAULT    1 helper
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
    11: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND puts
```

Note: for static linking the symbols need to be unique, so no overloading.
Some languages (like c++), that support function overloading, have to *mangle* to make their names unique.
To check them out in a human readable format use `nm --demangle <executable>`.
However in a backtrace you can use `c++filt` to manually demangle.

You can use `strip` to remove symbols from a binary to make it smaller and stack traces unreadable.

Compiling with the `-g` flag you create a *debug symbol* which is a different kind of symbol.
You might be able to see a difference by using `nm` here.

## Chapter 3



http://nickdesaulniers.github.io/blog/2015/05/25/interpreter-compiler-jit/
http://nickdesaulniers.github.io/blog/2016/08/13/object-files-and-symbols/
http://nickdesaulniers.github.io/blog/2016/11/20/static-and-dynamic-libraries/
