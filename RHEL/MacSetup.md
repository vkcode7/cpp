# RHEL Azure VM Setup for C++ Development

## Step 1 — Secure the PEM Key on Your MacBook

The downloaded `.pem` file must have strict permissions or SSH will refuse to use it.

```bash
# Move it to your .ssh folder
mv ~/Downloads/linuxvm_key.pem ~/.ssh/linuxvm_key.pem

# Set correct permissions — SSH requires this
chmod 400 ~/.ssh/linuxvm_key.pem

# Verify permissions (should show -r--------)
ls -la ~/.ssh/linuxvm_key.pem
```

---

## Step 2 — Find Your VM's Public IP

In the Azure Portal:
```
Virtual Machines → your VM → Overview → Public IP address
```

Copy that IP. You'll use it in every SSH command.

---

## Step 3 — SSH Into the VM

```bash
ssh -i ~/.ssh/linuxvm_key.pem azureuser@<YOUR-VM-PUBLIC-IP>

# Example:
ssh -i ~/.ssh/linuxvm_key.pem azureuser@20.123.45.67
```

Type `yes` when prompted to accept the host fingerprint. You should see a RHEL welcome prompt.

---

## Step 4 — Create an SSH Config Entry (Quality of Life)

Instead of typing the full command every time, set up a shortcut:

```bash
# On your MacBook (not the VM), open/create SSH config
vim ~/.ssh/config
```

Add this block:

```
Host rhel-dev
    HostName <YOUR-VM-PUBLIC-IP>
    User azureuser
    IdentityFile ~/.ssh/linuxvm_key.pem
    ServerAliveInterval 60
    ServerAliveCountMax 3
```

Save and close. Now you can connect with just:

```bash
ssh rhel-dev
```

---

## Step 5 — Update the System

Once logged into the VM:

```bash
sudo dnf update -y
```

This may take a few minutes on a fresh VM. RHEL 9 uses `dnf` as its package manager.

---

## Step 6 — Install the C++ Toolchain

```bash
# Core tools — GCC, GDB, Make, CMake, Git
sudo dnf install -y gcc-c++ gdb make cmake git

# Clang + clangd (LSP for editor integration)
sudo dnf install -y clang clang-tools-extra

# Development tools group (useful extras — binutils, autoconf etc.)
sudo dnf groupinstall -y "Development Tools"

# Additional tools you'll use regularly
sudo dnf install -y valgrind perf htop tmux wget curl tree
```

Verify everything installed correctly:

```bash
g++ --version
clang++ --version
cmake --version
gdb --version
git --version
```

---

## Step 7 — Install Vim and Configure It

```bash
# Install vim (full version — not vi)
sudo dnf install -y vim

# Install vim-plug (plugin manager)
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

Create your Vim config:

```bash
cat > ~/.vimrc << 'EOF'
call plug#begin('~/.vim/plugged')
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'preservim/nerdtree'
Plug 'vim-airline/vim-airline'
Plug 'tpope/vim-fugitive'
call plug#end()

set number
set tabstop=4
set shiftwidth=4
set expandtab
set autoindent
set smartindent
set hlsearch
set incsearch
set mouse=a
set background=dark
syntax on
EOF
```

Install plugins:

```bash
# Requires Node.js for coc.nvim
sudo dnf install -y nodejs

# Open vim and install all plugins
vim +PlugInstall +qall
```

---

## Step 8 — Set Up tmux (Essential for Remote Work)

tmux lets you keep sessions alive even if your SSH connection drops.

```bash
# Create tmux config
cat > ~/.tmux.conf << 'EOF'
# Remap prefix to Ctrl+a (easier than Ctrl+b)
unbind C-b
set-option -g prefix C-a
bind-key C-a send-prefix

# Split panes with | and -
bind | split-window -h
bind - split-window -v

# Enable mouse
set -g mouse on

# Start window numbering at 1
set -g base-index 1

# Increase history
set -g history-limit 10000
EOF
```

Basic tmux workflow:

```bash
# Start a named session
tmux new -s dev

# Key shortcuts inside tmux (Ctrl+a is your prefix):
# Ctrl+a |     split vertically
# Ctrl+a -     split horizontally
# Ctrl+a d     detach (session keeps running)
# tmux attach -t dev    re-attach later
```

---

## Step 9 — Set Up Your Project Directory Structure

```bash
# Create workspace
mkdir -p ~/projects/tcp-server/{src,tests,build}
cd ~/projects/tcp-server
```

Create CMakeLists.txt:

```bash
cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.16)
project(TcpServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -g
)

add_executable(tcp_server
    src/main.cpp
)

# Google Test
include(FetchContent)
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests/server_test.cpp
)
target_link_libraries(tests gtest_main)
EOF
```

Create a starter `main.cpp` to verify the build works:

```bash
cat > src/main.cpp << 'EOF'
#include <iostream>

int main()
{
    std::cout << "C++ Dev Environment Ready\n";
    return 0;
}
EOF
```

cat > ~/projects/tcp-server/tests/server_test.cpp << 'EOF'
#include <iostream>

int main()
{
    std::cout << "C++ Dev Environment TESTS Ready\n";
    return 0;
}
EOF

Build and run:

```bash
cd build
cmake ..
make -j$(nproc)
./tcp_server
# Output: C++ Dev Environment Ready
```

---

## Step 10 — Connect VS Code on Your MacBook to the VM

This gives you a comfortable editor while keeping everything running on Linux.

On your MacBook:

```
1. Open VS Code
2. Install extension: "Remote - SSH" (by Microsoft)
3. Press Cmd+Shift+P → "Remote-SSH: Connect to Host"
4. Type: rhel-dev  (the alias you set up in Step 4)
5. VS Code connects — opens a new window running on the VM
```

Inside the remote VS Code window, install these extensions:

```
C/C++ (Microsoft)
C/C++ Extension Pack
clangd
CMake Tools
GitLens
```

The `clangd` extension uses the `clangd` binary you installed in Step 6 — gives you autocomplete, go-to-definition, inline errors, all inside VS Code but running on your RHEL VM.

Generate a `compile_commands.json` so clangd understands your project:

```bash
cd ~/projects/tcp-server/build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
# Creates build/compile_commands.json — clangd reads this
```

---

## Step 11 — Enable Core Dumps

Core dumps are critical for GDB debugging — standard practice in banking:

```bash
# Enable core dumps for current session
ulimit -c unlimited

# Make it permanent
echo "* soft core unlimited" | sudo tee -a /etc/security/limits.conf

# Set core dump file location and naming
echo "kernel.core_pattern = /tmp/core-%e-%p-%t" | sudo tee -a /etc/sysctl.conf
sudo sysctl -p

# Verify
ulimit -c
# Should output: unlimited
```

Test it works:

```bash
# Compile a program that crashes
cat > /tmp/crash.cpp << 'EOF'
int main() {
    int* p = nullptr;
    *p = 42;  // deliberate crash
}
EOF

g++ -g -o /tmp/crash /tmp/crash.cpp
/tmp/crash
# Segmentation fault (core dumped)

ls /tmp/core-*   # core file should appear

# Analyze with GDB
gdb /tmp/crash /tmp/core-crash-*
(gdb) backtrace   # see exactly where it crashed
(gdb) quit
```

---

## Step 12 — Set Up Git

```bash
git config --global user.name "Your Name"
git config --global user.email "your@email.com"
git config --global core.editor vim
git config --global init.defaultBranch main

# Verify
git config --list
```

Generate an SSH key for GitHub (optional but useful):

```bash
ssh-keygen -t ed25519 -C "your@email.com"
cat ~/.ssh/id_ed25519.pub
# Copy this output and add to GitHub → Settings → SSH Keys
```

---

## Step 13 — Install spdlog (Logging Library Used in Banking)

```bash
cd ~
git clone https://github.com/gabime/spdlog.git
cd spdlog
mkdir build && cd build
cmake ..
sudo make install

# Verify
ls /usr/local/include/spdlog/
```

Add to your CMakeLists.txt when needed:

```cmake
find_package(spdlog REQUIRED)
target_link_libraries(your_target spdlog::spdlog)
```

---

## Step 14 — Configure Sanitizer Build Targets

Add these to your `CMakeLists.txt` for catching bugs during development:

```bash
cat >> ~/projects/tcp-server/CMakeLists.txt << 'EOF'

# AddressSanitizer build
add_executable(tcp_server_asan src/main.cpp)
target_compile_options(tcp_server_asan PRIVATE -fsanitize=address -g -O1)
target_link_options(tcp_server_asan PRIVATE -fsanitize=address)

# ThreadSanitizer build
add_executable(tcp_server_tsan src/main.cpp)
target_compile_options(tcp_server_tsan PRIVATE -fsanitize=thread -g -O1)
target_link_options(tcp_server_tsan PRIVATE -fsanitize=thread)

# UBSanitizer build
add_executable(tcp_server_ubsan src/main.cpp)
target_compile_options(tcp_server_ubsan PRIVATE -fsanitize=undefined -g -O1)
target_link_options(tcp_server_ubsan PRIVATE -fsanitize=undefined)
EOF
```

Usage:

```bash
cd ~/projects/tcp-server/build
cmake .. && make -j$(nproc)
./tcp_server_asan    # run with memory error detection
./tcp_server_tsan    # run with race condition detection
./tcp_server_ubsan   # run with undefined behavior detection
```

---

## Step 15 — Cost Control — Stop VM When Not in Use

Azure charges by the hour when the VM is running. Stop it when done:

```bash
# From your MacBook terminal (install Azure CLI first if needed)
# brew install azure-cli
az login
az vm deallocate --resource-group <YOUR-RESOURCE-GROUP> --name <YOUR-VM-NAME>

# Start it again later
az vm start --resource-group <YOUR-RESOURCE-GROUP> --name <YOUR-VM-NAME>
```

Or simply use the Azure Portal:
```
Virtual Machines → your VM → Stop (to deallocate)
                           → Start (to resume)
```

> ⚠️ Click **Stop** not just **Restart** — only "Stopped (deallocated)" stops billing for compute.

---

## Quick Reference — Daily Workflow

```bash
# 1. Start VM (Azure Portal or az vm start)

# 2. Connect
ssh rhel-dev

# 3. Start tmux session
tmux new -s dev       # first time
tmux attach -t dev    # returning

# 4. Navigate to project
cd ~/projects/tcp-server

# 5. Edit code (pick one)
vim src/main.cpp          # terminal vim
# OR open VS Code on Mac → already connected via Remote SSH

# 6. Build
cd build && make -j$(nproc)

# 7. Run / debug
./tcp_server
gdb ./tcp_server

# 8. When done — stop VM to save cost
az vm deallocate --resource-group <RG> --name <VM>
```

---

## Directory Layout Reference

```
~/ (home on VM)
├── .ssh/
│   └── config              ← SSH shortcuts
├── .vimrc                  ← Vim config
├── .tmux.conf              ← tmux config
└── projects/
    └── tcp-server/
        ├── CMakeLists.txt
        ├── src/
        │   └── main.cpp
        ├── tests/
        │   └── server_test.cpp
        └── build/          ← cmake + make output (never commit this)
```



### Core Tools

**`gcc-c++`** — the actual C++ compiler. Translates your `.cpp` source code into a binary executable the CPU can run. When you type `g++ main.cpp -o myprogram`, this is what does the work. GCC stands for GNU Compiler Collection.

**`gdb`** — GNU Debugger. Lets you pause a running program, inspect variables, step through code line by line, and analyse crash dumps. The tool you use when your program crashes and you need to find out why. In banking you'll use it constantly for analysing core dumps in production.

**`make`** — a build automation tool. Reads a `Makefile` and figures out which files need recompiling based on what changed — so you don't recompile everything from scratch every time. CMake generates Makefiles, then `make` actually does the building.

**`cmake`** — a build system generator. You write a `CMakeLists.txt` describing your project, and CMake generates the actual Makefiles for your platform. It handles things like finding libraries, setting compiler flags, and managing multi-file projects. The standard for modern C++ projects.

**`git`** — version control. Tracks changes to your code over time, lets you create branches, revert mistakes, and collaborate with others. Universal in every software team.

---

### Clang Tools

**`clang`** — an alternative C++ compiler to GCC, developed by LLVM. Produces similar binaries but often gives clearer error messages. Also the foundation for the sanitizers (AddressSanitizer, ThreadSanitizer etc.) and static analysis tools. Many developers compile with GCC for production and Clang for development/debugging.

**`clang-tools-extra`** — a suite of tools built on top of Clang:
- `clangd` — the language server that powers autocomplete, go-to-definition, and inline errors in VS Code. Without this, VS Code's C++ intelligence doesn't work properly on your VM
- `clang-tidy` — static analyser that catches bugs and enforces coding standards without running the code
- `clang-format` — automatically formats your code to a consistent style

---

### Development Tools Group

This is a meta-package that installs a collection of lower-level tools you need indirectly:

**`binutils`** — tools for working with compiled binaries: `objdump` (inspect compiled code), `nm` (list symbols), `strip` (remove debug info for smaller binaries), `ar` (create static libraries). You rarely call these directly but the compiler uses them constantly.

**`autoconf` / `automake`** — older build systems predating CMake. Many open source libraries still use them. You'll need these when compiling third-party dependencies from source.

**`glibc-devel`** — headers and libraries for the C standard library. Required to compile virtually any C or C++ program — things like `printf`, `malloc`, file I/O all live here.

**`kernel-headers`** — header files describing the Linux kernel's interface. Needed for low-level system programming — socket programming, epoll, file descriptors — all the TCP server code you'll write.

---

### Additional Tools

**`valgrind`** — a memory analysis tool. Runs your program in a virtual machine and detects memory errors: leaks (memory you allocated but never freed), reading uninitialised memory, buffer overflows, use-after-free bugs. Much slower than running normally but catches bugs the compiler misses. Used heavily in testing environments in banking.

```bash
valgrind --leak-check=full ./tcp_server
# reports exactly which line leaked memory
```

**`perf`** — Linux performance profiling tool. Measures where your program spends its CPU time, cache miss rates, branch mispredictions, system call overhead. Essential for low-latency work in banking — you use it to find bottlenecks and optimise them.

```bash
perf stat ./tcp_server        # high level CPU stats
perf record ./tcp_server      # record detailed profile
perf report                   # interactive viewer of results
```

**`tmux`** — terminal multiplexer, as discussed in the previous message. Keeps sessions alive across disconnections and lets you split your terminal into multiple panes.

**`wget`** — command-line tool for downloading files from the internet. `wget https://example.com/file.tar.gz` downloads that file to your current directory. Used in scripts to fetch dependencies or datasets.

**`curl`** — similar to wget but more versatile. Can send HTTP requests with custom headers, POST data, authentication — making it useful for testing REST APIs and downloading files. In your TCP server work you'll use it to test HTTP endpoints.

```bash
curl http://localhost:8080/status   # test your server is responding
```

**`tree`** — displays directory structure as a visual tree. Purely a convenience tool:

```bash
tree ~/projects/tcp-server
# tcp-server/
# ├── CMakeLists.txt
# ├── src/
# │   └── main.cpp
# ├── tests/
# │   └── server_test.cpp
# └── build/
```

---

### How they all fit together in your daily workflow

```
You write code
      ↓
cmake — reads CMakeLists.txt, generates Makefiles
      ↓
make — calls g++ (gcc-c++) to compile changed files
      ↓
Program runs — crashes or misbehaves
      ↓
gdb — debug the crash / analyse core dump
      ↓
valgrind — check for memory leaks
      ↓
perf — profile performance bottlenecks
      ↓
clangd — gives you autocomplete and errors while editing in VS Code
clang-tidy — catches bugs statically before you even run anything
```

The tools you'll use every single day are `cmake`, `make`, `gdb`, and `clangd` (indirectly via VS Code). The others you reach for when you hit specific problems.


When you connect to your RHEL VM via VS Code Remote SSH, extensions need to be installed **on the remote side** (the VM), not locally on your Mac. VS Code handles this automatically — when you install an extension while connected to the VM, it installs it there.

---

### VSCode Extensions to Install

#### 1. C/C++ Extension Pack (Microsoft)
```
Name:      C/C++ Extension Pack
Publisher: Microsoft
ID:        ms-vscode.cpptools-extension-pack
```
This is a bundle that installs several extensions at once — install this one and it pulls in everything else you need. It includes the core C/C++ extension, CMake Tools, and themes.

---

#### 2. clangd
```
Name:      clangd
Publisher: LLVM
ID:        llvm-vs-code-extensions.vscode-clangd
```
This is the **most important one for IntelliSense**. It uses the `clangd` binary you already installed on the VM to power:
- Autocomplete
- Go-to-definition (F12)
- Find all references
- Inline error squiggles as you type
- Header file navigation
- Automatic `#include` suggestions

> **Important:** After installing clangd extension, VS Code will ask if you want to disable the IntelliSense engine from the Microsoft C/C++ extension. Say **Yes** — clangd and the Microsoft IntelliSense engine conflict with each other. clangd is superior for Linux C++ development.

---

#### 3. CMake Tools
```
Name:      CMake Tools
Publisher: Microsoft
ID:        ms-vscode.cmake-tools
```
Comes included in the Extension Pack but worth knowing what it does:
- Detects your `CMakeLists.txt` automatically
- Adds a toolbar at the bottom of VS Code for build/run/debug
- Lets you switch between Debug/Release build types with one click
- Runs `cmake` and `make` for you without touching the terminal

---

#### 4. CodeLLDB
```
Name:      CodeLLDB
Publisher: Vadim Chugunov
ID:        vadimchugunov.codelldb
```
This is the **debugger extension**. It lets you:
- Set breakpoints by clicking in the gutter (left of line numbers)
- Step through code (F10 step over, F11 step into)
- Inspect variables in a sidebar panel
- See the call stack
- Watch expressions
- Debug core dump files

> Why CodeLLDB over the Microsoft C/C++ debugger? CodeLLDB uses LLDB under the hood, is faster, handles C++ types (STL containers, smart pointers) better, and works more reliably over Remote SSH.

---

#### 5. GitLens
```
Name:      GitLens
Publisher: GitKraken
ID:        eamodio.gitlens
```
Supercharges Git inside VS Code:
- Shows who last changed each line (inline blame)
- File history
- Branch comparison
- Commit explorer

---

### Setting Up the Debugger — `launch.json`

After installing CodeLLDB, you need to tell VS Code how to launch your program for debugging. Create this file on the VM:

```bash
mkdir -p ~/projects/tcp-server/.vscode
```

Create `~/projects/tcp-server/.vscode/launch.json`:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "lldb",
            "request": "launch",
            "name": "Debug tcp_server",
            "program": "${workspaceFolder}/build/tcp_server",
            "args": [],
            "cwd": "${workspaceFolder}",
            "preLaunchTask": "Build"
        },
        {
            "type": "lldb",
            "request": "launch",
            "name": "Debug Tests",
            "program": "${workspaceFolder}/build/tests",
            "args": [],
            "cwd": "${workspaceFolder}",
            "preLaunchTask": "Build"
        },
        {
            "type": "lldb",
            "request": "custom",
            "name": "Analyse Core Dump",
            "targetCreateCommands": [
                "target create ${workspaceFolder}/build/tcp_server",
                "target modules load --file ${workspaceFolder}/build/tcp_server"
            ],
            "processCreateCommands": [
                "core /tmp/core-tcp_server-*"
            ]
        }
    ]
}
```

---

### Setting Up the Build Task — `tasks.json`

This lets VS Code run `cmake` and `make` automatically before debugging:

Create `~/projects/tcp-server/.vscode/tasks.json`:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build",
            "type": "shell",
            "command": "cd ${workspaceFolder}/build && cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && make -j$(nproc)",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "reveal": "always",
                "panel": "shared"
            },
            "problemMatcher": "$gcc"
        }
    ]
}
```

---

### Setting Up clangd — `settings.json`

Tell VS Code where to find clangd and the compile commands:

Create `~/projects/tcp-server/.vscode/settings.json`:

```json
{
    "clangd.path": "/usr/bin/clangd",
    "clangd.arguments": [
        "--background-index",
        "--clang-tidy",
        "--completion-style=detailed",
        "--header-insertion=iwyu",
        "--compile-commands-dir=${workspaceFolder}/build"
    ],
    "cmake.buildDirectory": "${workspaceFolder}/build",
    "cmake.installPrefix": "${workspaceFolder}/install",
    "editor.formatOnSave": true,
    "C_Cpp.intelliSenseEngine": "disabled"
}
```

The key line is `"C_Cpp.intelliSenseEngine": "disabled"` — this turns off Microsoft's IntelliSense so clangd takes over exclusively.

---

### Generate `compile_commands.json` — Required for clangd

clangd needs this file to understand your project's include paths and compiler flags:

```bash
cd ~/projects/tcp-server/build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

This creates `build/compile_commands.json`. clangd reads it automatically because of the `--compile-commands-dir` argument in `settings.json`. You only need to rerun this when you add new files or change `CMakeLists.txt`.

---

### Final File Structure

```
~/projects/tcp-server/
├── .vscode/
│   ├── launch.json     ← debugger config
│   ├── tasks.json      ← build task
│   └── settings.json   ← clangd + cmake settings
├── CMakeLists.txt
├── src/
│   └── main.cpp
├── tests/
│   └── server_test.cpp
└── build/
    └── compile_commands.json   ← generated by cmake, read by clangd
```

---

### Daily Debugging Workflow

```
1. Open project in VS Code (already connected to VM via Remote SSH)

2. Build
   Ctrl+Shift+B    runs the Build task from tasks.json

3. Set a breakpoint
   Click in the gutter left of a line number — red dot appears

4. Start debugger
   F5              launches tcp_server with debugger attached

5. When breakpoint hits:
   F10             step over (next line, don't enter functions)
   F11             step into (enter the function)
   Shift+F11       step out (finish current function)
   F5              continue to next breakpoint

6. Inspect state
   Hover over any variable    — shows its current value
   Left sidebar Variables     — all local variables
   Left sidebar Watch         — expressions you want to monitor
   Left sidebar Call Stack    — how you got to this point
```


Yes — the `launch.json` we created already has a core dump configuration in it. Here's the full walkthrough:

---

### How Core Dump Analysis Works in VS Code

The third configuration in `launch.json` handles this:

```json
{
    "type": "lldb",
    "request": "custom",
    "name": "Analyse Core Dump",
    "targetCreateCommands": [
        "target create ${workspaceFolder}/build/tcp_server",
        "target modules load --file ${workspaceFolder}/build/tcp_server"
    ],
    "processCreateCommands": [
        "core /tmp/core-tcp_server-*"
    ]
}
```

---

### Step by Step

**Step 1 — Make sure your binary is compiled with debug symbols**

```bash
cd ~/projects/tcp-server/build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
```

Without `-DCMAKE_BUILD_TYPE=Debug`, the binary has no debug symbols and the core dump analysis will just show raw memory addresses — useless.

---

**Step 2 — Enable core dumps on the VM**

```bash
# Already done in the setup guide — verify it's still set
ulimit -c
# Should show: unlimited

# If it shows 0, re-enable it
ulimit -c unlimited
```

---

**Step 3 — Crash your program to generate a core dump**

Either your program crashes naturally in production, or you can force one for testing:

```bash
# Run your program
./build/tcp_server

# If it doesn't crash naturally, force a crash from another terminal:
kill -SIGSEGV <pid>        # sends segfault signal
kill -SIGABRT <pid>        # sends abort signal

# Or add a deliberate crash in code for testing:
```

```cpp
// Temporary test crash in main.cpp
int* p = nullptr;
*p = 42;   // segfault — generates core dump
```

---

**Step 4 — Find the core dump file**

```bash
ls /tmp/core-*
# Example output:
# /tmp/core-tcp_server-12345-1690000000
```

---

**Step 5 — Update `launch.json` with the exact core file path**

Open `.vscode/launch.json` and update the core file path:

```json
"processCreateCommands": [
    "core /tmp/core-tcp_server-12345-1690000000"
]
```

Or keep the wildcard `*` if there's only one core file in `/tmp`.

---

**Step 6 — Open the Debug panel in VS Code**

```
Click the bug icon in the left sidebar (or Ctrl+Shift+D)
```

From the dropdown at the top, select **"Analyse Core Dump"** instead of the normal debug configuration:

```
▶ Debug tcp_server          ← normal debugging
▶ Debug Tests               ← run tests with debugger
▶ Analyse Core Dump         ← select this one
```

Press **F5** to start.

---

**Step 7 — What you see in VS Code**

VS Code loads the core dump and immediately shows you:

```
Call Stack panel (left sidebar):
  #0  main() at src/main.cpp:42        ← exact line that crashed
  #1  __libc_start_main()
  #2  _start()

Variables panel:
  p = 0x0                              ← null pointer — cause of crash

Source view:
  src/main.cpp opens automatically
  red arrow points to line 42          ← the crashing line highlighted
```

You can then:
- Click any frame in the call stack to jump to that point in the source
- Hover over variables to see their values at the time of crash
- Inspect the entire call chain that led to the crash

---

### What if the core dump is from a multi-threaded crash

This is the common scenario in a TCP server. In VS Code's Call Stack panel you'll see all threads listed:

```
Call Stack:
  Thread 1 (crashed)
    #0  epoll_wait() at epoll_loop.cpp:87
    #1  EventLoop::run() at epoll_loop.cpp:45
    #2  main() at main.cpp:12

  Thread 2
    #0  pthread_cond_wait()
    #1  ThreadPool::workerLoop()

  Thread 3
    #0  send() at server.cpp:134
    #1  Server::pushToClients()
```

Click any thread to switch to it, then click any frame within that thread to jump to that source location. This is exactly the workflow used in banking for production crash analysis.

---

### Limitations of VS Code Core Dump Analysis vs Raw GDB

| Feature | VS Code (CodeLLDB) | Raw GDB in terminal |
|---|---|---|
| Visual call stack | ✅ | ❌ text only |
| Click to navigate source | ✅ | ❌ manual |
| Variable inspection | ✅ | ✅ |
| Multi-thread inspection | ✅ | ✅ |
| Custom GDB commands | ⚠️ limited | ✅ full |
| Scripting / automation | ❌ | ✅ via GDB Python API |
| Works over slow SSH | ⚠️ can lag | ✅ always fast |

For straightforward crashes VS Code is faster and more comfortable. For complex production crashes — especially in banking where you might be running GDB scripts or analysing very large core files — experienced engineers often drop to the terminal and use raw GDB directly, which is why learning both is worthwhile.

---

### Quick GDB Alternative (Terminal)

If VS Code feels slow with a large core file, the terminal is always there:

```bash
# In VS Code's integrated terminal (Ctrl+`)
gdb ./build/tcp_server /tmp/core-tcp_server-12345

(gdb) bt                    # backtrace — see call stack
(gdb) info threads          # list all threads
(gdb) thread apply all bt   # backtrace every thread at once
(gdb) frame 2               # jump to frame #2 in call stack
(gdb) print myVariable      # inspect a variable
(gdb) list                  # show source code around crash point
(gdb) quit
```

Both approaches work — use VS Code for comfort, raw GDB when you need full power or speed.
