# CMake
CMake is an source, cross-platform build system generator. It has been used as the primary build system for LLVM since version 3.3, which was released in 2013.

Any build process consists of two steps. The first one is the project configuration and the last one is the build itself. LLVM uses CMake as a project configuration tool. It also can use a wide range of build tools, such as Unix Makefiles, and Ninja. It can also generate project files for popular IDEs such as Visual Studio and XCode. We are going to use Ninja as the build tool because it speeds up the build process, and most LLVM developers use it.

# Ninja
Ninja is a small build system with a focus on speed. It is designed to be used in conjunction with a build generator, such as CMake, which generates a build file that describes the build rules for a project.
One of the main advantages of Ninja is its speed. It is able to execute builds much faster than other build systems, such as Unix Makefiles, by only rebuilding the minimum set of files necessary to complete the build. This is because it keeps track of the dependencies between build targets and only rebuilds targets that are out of date.

# LLVM
LLVM was originally designed to be a next-generation code generation infrastructure that could be used to build optimizing compilers for many programming languages. However, it has since evolved into a full-featured platform that can be used to build a wide variety of tools, including debuggers, profilers, and static analysis tools.

Everything in LLVM is a library, including Clang . It opened the opportunity to create a lot of amazing tools based on Clang and LLVM, such as clang-tidy and clangd”

The GCC is the default set of dev tools on Linux, especially gcc (for C programs) and g++ (for C++ programs) being the default compilers. Clang can also be used to compile source code on Linux. Moreover, it mimics to gcc and supports most of its options. LLVM support might be limited for some GNU tools, however; for instance, GNU Emacs does not support LLDB as a debugger. But despite this, Linux is the most suitable OS for LLVM development and investigation, thus we will mainly use this OS (Fedora 39) for future examples.

## Common LLVM tools
```
lld : The LLVM linker tool. You may want to use it as a replacement for standard linker tools, such as GNU ld
llvm : Common libraries for LLVM projects
lldb: debugger
clang : The clang driver and frontend
clang-tools-extra : These are different clang tools”

Another important folder is clang-tools-extra . It contains some tools based on different Clang libraries. They are as follows:
clang-tools-extra/clangd : A language server that provides navigation info for IDEs such as VSCode
clang-tools-extra/clang-tidy : A powerful lint framework with several hundred different checks
clang-tools-extra/clang-format : A code formatting tool
```

## CMake build
The minimal configuration command looks like this:

$ cmake -DCMAKE_BUILD_TYPE=Debug ../llvm

The command requires the build type to be specified (e.g. Debug in our case) as well as the primary argument that points to a folder with the build configuration file. The configuration file is stored as CMake-Lists.txt and is located in the llvm folder, which explains the ../llvm argument usage. The command generates Makefile located in the build folder, thus you can use the simple make command to start the build process.


We will use more advanced configuration commands in the book. One of the commands looks like this:

cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../install -DLLVM_TARGETS_TO_BUILD="X86" -DLLVM_ENABLE_PROJECTS="lldb;clang;clang-tools-extra" -DLLVM_USE_SPLIT_DWARF=ON ../llvm
 

The are several LLVM/cmake options specified:
```
-G Ninja specifies Ninja as the build generator, otherwise it will use make (which is slow).
-DCMAKE_BUILD_TYPE=Debug sets the build mode. The build with debug info will be created. There is a primary build configuration for Clang internals investigations.
-DCMAKE_INSTALL_PREFIX=../install specifies the installation folder.
-DLLVM_TARGETS_TO_BUILD="X86" sets exact targets to be build. It will avoid building unnecessary targets.
-DLLVM_ENABLE_PROJECTS="lldb;clang;clang-tools-extra" specifies the LLVM projects we want to build.
-DLLVM_USE_SPLIT_DWARF=ON splits debug information into separate files. This option saves disk space as well as memory consumption during the LLVM build.
```

Building LLVM with CMake:

https://llvm.org/docs/CMake.html

## Compiler Process

### Lexer
“The frontend process starts with the Lexer , which converts the input source into a stream of tokens. ”

### Parser
“The Parser is the next component following the Lexer . The primary output produced by the Parser is called an abstract syntax tree (AST). This tree represents the abstract syntactic structure of the source code written in a programming language. The Parser generates the AST by taking the stream of tokens produced by the Lexer as input and organizing them into a tree-like structure. ”

The Parser performs two activities:
- Syntax analysis: the Parser constructs the AST by analyzing the syntax of the program.
- Semantic analysis: the Parser analyzes the program semantically.

“AST is mainly constructed as a result of syntax analysis, but for certain languages, such as C++, semantic analysis is also crucial for constructing the AST, particularly for C++ template instantiation.”

### The codegen
The codegen (it’s worth mentioning that we also have another Codegen component as a part of Backend that generate the target code) or code generator, which is the final component of the compiler’s frontend, has the primary goal of generating the Intermediate Representation (IR). For this purpose, the compiler traverses the AST generated by the parser and converts it into other source code that is called the Intermediate Representation or IR. The IR is a language-independent representation, allowing the same middle-end component to be used for different frontends (FORTRAN vs C++). Another reason for using an Intermediate Representation (IR) is that if we have a new architecture available tomorrow, we can generate the target code specific to that architecture. Since the source language remains unchanged, all the steps leading up to the IR will remain the same. The IR provides this flexibility.

## Clang driver overview
When discussing compilers, we typically refer to a command-line utility that initiates and manages the compilation process. For example, to use the GNU Compiler Collection, one must call gcc to start the compilation process. Similarly, to compile a C++ program using Clang, one must call clang as the compiler. The program that controls the compilation process is known as the driver.

Clang driver: The driver got the input file hello.cpp, which is a C++ file. It starts two processes: clang and ld. The first one does real compilation and starts the integrated assembler. The last one is the linker (ld) that produces the final binary (image) from the result received from the compiler (object file) and the external library (libstdc++) 

