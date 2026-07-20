# RHEL Azure VM Setup for C++ Development (Windows)

The Windows guide follows the same 15-step structure as the Mac version but with all the Windows-specific differences handled:

Key differences from the Mac guide:
- Step 1 (PEM permissions) — the biggest difference. Mac uses chmod 400 (one command). Windows requires icacls to strip inherited permissions and grant read-only to your user — SSH will silently fail or warn if you skip this.
- Step 3–4 (SSH) — uses $env:USERPROFILE (PowerShell syntax) instead of ~ for paths. No PuTTY needed — Windows 10/11 has OpenSSH built in.
- Step 10 (VS Code) — includes a Windows-specific note about the IdentityFile path in the SSH config needing forward slashes, which trips people up.

Windows-specific tips section covers three things Mac users never worry about:

- Line endings (\r\n vs \n) — can cause cryptic build errors if you edit files on Windows and push to Linux
- scp syntax — uses PowerShell backtick for line continuation instead of Mac's backslash
- Windows Terminal profile — lets you one-click connect to the VM from a dedicated tab

Everything on the VM itself (Steps 5–14) is identical to the Mac guide since it's all Linux.

## Prerequisites — Install These on Windows First

Before connecting to the VM, install the following on your Windows machine:

```
1. Windows Terminal      — https://aka.ms/terminal (or install from Microsoft Store)
2. VS Code               — https://code.visualstudio.com
3. Azure CLI             — https://aka.ms/installazurecliwindows
4. Git for Windows       — https://git-scm.com/download/win
                           (also installs OpenSSH and Git Bash)
```

> Windows 10 (1809+) and Windows 11 both ship with **OpenSSH client** built in.
> Verify by opening Windows Terminal and typing `ssh -V`.
> If it shows a version, you're good — no PuTTY needed.

---

## Step 1 — Secure the PEM Key on Windows

Move the downloaded `.pem` file to your `.ssh` folder and lock down its permissions.
Windows is stricter than Linux about key file permissions — you must do this or SSH will refuse the key.

Open **Windows Terminal** (as regular user, not admin):

```powershell
# Create .ssh folder if it doesn't exist
mkdir $env:USERPROFILE\.ssh

# Move the PEM key there
move $env:USERPROFILE\Downloads\your-key.pem $env:USERPROFILE\.ssh\your-key.pem
```

Now fix permissions — this is the Windows equivalent of `chmod 400`:

```powershell
# Full path to your key
$keyPath = "$env:USERPROFILE\.ssh\your-key.pem"

# Remove all inherited permissions
icacls $keyPath /inheritance:r

# Grant read-only access to your Windows user only
icacls $keyPath /grant:r "$env:USERNAME:(R)"

# Remove any other users/groups
icacls $keyPath /remove "NT AUTHORITY\Authenticated Users"
icacls $keyPath /remove "BUILTIN\Users"
icacls $keyPath /remove "Everyone"

# Verify — should show only your username with (R)
icacls $keyPath
```

---

## Step 2 — Find Your VM's Public IP

In the Azure Portal:
```
Virtual Machines → your VM → Overview → Public IP address
```

Copy that IP. You will use it in every SSH command.

---

## Step 3 — SSH Into the VM

In Windows Terminal:

```powershell
ssh -i $env:USERPROFILE\.ssh\your-key.pem azureuser@<YOUR-VM-PUBLIC-IP>

# Example:
ssh -i $env:USERPROFILE\.ssh\your-key.pem azureuser@20.123.45.67
```

Type `yes` when prompted to accept the host fingerprint.
You should see a RHEL welcome prompt.

---

## Step 4 — Create an SSH Config Entry (Quality of Life)

Instead of typing the full command every time, create a shortcut:

```powershell
# Open (or create) the SSH config file in Notepad
notepad $env:USERPROFILE\.ssh\config
```

Add this block — replace the IP with your VM's actual public IP:

```
Host rhel-dev
    HostName <YOUR-VM-PUBLIC-IP>
    User azureuser
    IdentityFile ~/.ssh/your-key.pem
    ServerAliveInterval 60
    ServerAliveCountMax 3
```

Save and close. Now connect with just:

```powershell
ssh rhel-dev
```

---

## Step 5 — Update the System

Once logged into the VM:

```bash
sudo dnf update -y
```

This may take a few minutes on a fresh VM.

---

## Step 6 — Install the C++ Toolchain

```bash
# Core tools — GCC, GDB, Make, CMake, Git
sudo dnf install -y gcc-c++ gdb make cmake git

# Clang + clangd (LSP for editor integration)
sudo dnf install -y clang clang-tools-extra

# Development tools group
sudo dnf groupinstall -y "Development Tools"

# Additional tools
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
# Install vim
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
# Node.js required for coc.nvim
sudo dnf install -y nodejs

# Install all plugins
vim +PlugInstall +qall
```

---

## Step 8 — Set Up tmux

tmux keeps your session alive even if your Windows machine sleeps or your connection drops — essential for remote development.

```bash
cat > ~/.tmux.conf << 'EOF'
# Remap prefix to Ctrl+a (easier than Ctrl+b)
unbind C-b
set-option -g prefix C-a
bind-key C-a send-prefix

# Split panes
bind | split-window -h
bind - split-window -v

# Enable mouse
set -g mouse on

# Start window numbering at 1
set -g base-index 1

# Increase scrollback history
set -g history-limit 10000
EOF
```

Basic tmux workflow:

```bash
# Start a named session
tmux new -s dev

# Key shortcuts (Ctrl+a is your prefix):
# Ctrl+a |        split vertically
# Ctrl+a -        split horizontally
# Ctrl+a d        detach (session keeps running on VM)
# Ctrl+a [        scroll mode (use arrow keys, q to exit)

# Re-attach after reconnecting SSH
tmux attach -t dev
```

> **Windows Terminal tip:** If `Ctrl+a` conflicts with Windows Terminal shortcuts,
> go to Windows Terminal Settings → Actions and remove or remap conflicting bindings.

---

## Step 9 — Set Up Your Project Directory Structure

```bash
mkdir -p ~/projects/tcp-server/{src,tests,build}
cd ~/projects/tcp-server
```

Create `CMakeLists.txt`:

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

Create a starter `main.cpp`:

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

## Step 10 — Connect VS Code on Windows to the VM

This gives you a full IDE experience on Windows while all code runs on Linux.

On your Windows machine:

```
1. Open VS Code
2. Install extension: "Remote - SSH" (by Microsoft)
3. Press Ctrl+Shift+P → type "Remote-SSH: Connect to Host"
4. Select: rhel-dev   (the alias you set up in Step 4)
5. VS Code opens a new window — everything now runs on the VM
```

Inside the remote VS Code window, install these extensions:

```
C/C++ (Microsoft)
C/C++ Extension Pack
clangd
CMake Tools
GitLens
```

Generate `compile_commands.json` so clangd understands your project:

```bash
cd ~/projects/tcp-server/build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

> **Windows-specific note:** If VS Code Remote SSH fails to connect, check that
> your SSH config file at `C:\Users\YourName\.ssh\config` uses Unix-style
> forward slashes in the `IdentityFile` path, or use `~/.ssh/your-key.pem`.

---

## Step 11 — Enable Core Dumps

Core dumps are essential for post-mortem GDB debugging — standard practice in banking environments.

```bash
# Enable for current session
ulimit -c unlimited

# Make permanent
echo "* soft core unlimited" | sudo tee -a /etc/security/limits.conf

# Set core dump location and naming
echo "kernel.core_pattern = /tmp/core-%e-%p-%t" | sudo tee -a /etc/sysctl.conf
sudo sysctl -p

# Verify
ulimit -c
# Should output: unlimited
```

Test it works:

```bash
cat > /tmp/crash.cpp << 'EOF'
int main() {
    int* p = nullptr;
    *p = 42;  // deliberate crash
}
EOF

g++ -g -o /tmp/crash /tmp/crash.cpp
/tmp/crash
# Segmentation fault (core dumped)

ls /tmp/core-*

# Analyze with GDB
gdb /tmp/crash /tmp/core-crash-*
(gdb) backtrace
(gdb) quit
```

---

## Step 12 — Set Up Git on the VM

```bash
git config --global user.name "Your Name"
git config --global user.email "your@email.com"
git config --global core.editor vim
git config --global init.defaultBranch main

# Verify
git config --list
```

Generate an SSH key on the VM for GitHub (optional):

```bash
ssh-keygen -t ed25519 -C "your@email.com"
cat ~/.ssh/id_ed25519.pub
# Copy this and add to GitHub → Settings → SSH Keys
```

---

## Step 13 — Install spdlog

spdlog is a widely used logging library in C++ banking/finance codebases.

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

---

## Step 14 — Configure Sanitizer Build Targets

```bash
cat >> ~/projects/tcp-server/CMakeLists.txt << 'EOF'

# AddressSanitizer — catches memory corruption and buffer overflows
add_executable(tcp_server_asan src/main.cpp)
target_compile_options(tcp_server_asan PRIVATE -fsanitize=address -g -O1)
target_link_options(tcp_server_asan PRIVATE -fsanitize=address)

# ThreadSanitizer — catches data races
add_executable(tcp_server_tsan src/main.cpp)
target_compile_options(tcp_server_tsan PRIVATE -fsanitize=thread -g -O1)
target_link_options(tcp_server_tsan PRIVATE -fsanitize=thread)

# UndefinedBehaviorSanitizer — catches UB
add_executable(tcp_server_ubsan src/main.cpp)
target_compile_options(tcp_server_ubsan PRIVATE -fsanitize=undefined -g -O1)
target_link_options(tcp_server_ubsan PRIVATE -fsanitize=undefined)
EOF
```

```bash
cd ~/projects/tcp-server/build
cmake .. && make -j$(nproc)

./tcp_server_asan    # memory error detection
./tcp_server_tsan    # race condition detection
./tcp_server_ubsan   # undefined behavior detection
```

---

## Step 15 — Cost Control — Stop VM When Not in Use

**Option A — Azure CLI (from Windows Terminal):**

```powershell
# Login (opens browser)
az login

# Stop and deallocate VM (stops billing for compute)
az vm deallocate --resource-group <YOUR-RESOURCE-GROUP> --name <YOUR-VM-NAME>

# Start again later
az vm start --resource-group <YOUR-RESOURCE-GROUP> --name <YOUR-VM-NAME>

# Check current state
az vm show --resource-group <YOUR-RESOURCE-GROUP> --name <YOUR-VM-NAME> --query powerState
```

**Option B — Azure Portal:**
```
Virtual Machines → your VM → Stop   (to deallocate)
                           → Start  (to resume)
```

> ⚠️ Always choose **Stop (Deallocate)** not just **Restart**.
> Only "Stopped (deallocated)" stops compute billing.
> A merely "Stopped" VM still incurs charges.

---

## Windows-Specific Tips

### Line endings — important for C++ on Linux
Windows uses `\r\n` line endings; Linux uses `\n`. If you ever edit files
locally on Windows and copy them to the VM, line endings can cause subtle issues.

Configure Git on Windows to handle this:

```powershell
# In Windows Terminal (on your Windows machine, not the VM)
git config --global core.autocrlf input
```

This ensures files committed from Windows don't have `\r\n` injected.

### Copying files from Windows to the VM

Use `scp` (built into Windows 10/11) to copy files up to the VM:

```powershell
# Copy a single file to VM
scp -i $env:USERPROFILE\.ssh\your-key.pem `
    C:\Users\YourName\myfile.cpp `
    azureuser@<VM-IP>:~/projects/tcp-server/src/

# Copy an entire folder
scp -i $env:USERPROFILE\.ssh\your-key.pem -r `
    C:\Users\YourName\my-project `
    azureuser@<VM-IP>:~/projects/

# Or using the SSH alias (after Step 4)
scp myfile.cpp rhel-dev:~/projects/tcp-server/src/
```

### Copying files from the VM to Windows

```powershell
# Download a file from VM to your Windows Downloads folder
scp rhel-dev:~/projects/tcp-server/build/tcp_server `
    $env:USERPROFILE\Downloads\
```

### Windows Terminal profiles (convenience)
Add a dedicated profile for your VM in Windows Terminal:

```
Windows Terminal → Settings → Add a new profile → Empty
  Name:          RHEL Dev VM
  Command line:  ssh rhel-dev
  Icon:          (pick any)
```

Now you get a dedicated tab that connects directly to your VM with one click.

---

## Quick Reference — Daily Workflow

```powershell
# ── On Windows ──────────────────────────────────────────

# 1. Start VM
az vm start --resource-group <RG> --name <VM>

# 2. Connect (Windows Terminal)
ssh rhel-dev

# ── On the VM (inside SSH session) ──────────────────────

# 3. Re-attach tmux session
tmux attach -t dev
# (or start new: tmux new -s dev)

# 4. Navigate and code
cd ~/projects/tcp-server
vim src/main.cpp

# 5. Build
cd build && make -j$(nproc)

# 6. Run / debug
./tcp_server
gdb ./tcp_server

# ── Back on Windows when done ────────────────────────────

# 7. Stop VM to save cost
az vm deallocate --resource-group <RG> --name <VM>
```

---

## Directory Layout Reference

```
VM (~/)
├── .ssh/
│   └── id_ed25519.pub      ← VM's GitHub key
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

Windows (C:\Users\YourName\)
└── .ssh/
    ├── config              ← SSH shortcuts (rhel-dev alias)
    └── your-key.pem        ← Azure VM private key (chmod equivalent done in Step 1)
```
