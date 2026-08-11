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
