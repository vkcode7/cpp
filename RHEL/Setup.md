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
