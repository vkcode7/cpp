
## daemons:
They are known as daemons and run
constantly in the background. They are expected to be always available.
Daemons are usually started through the system’s startup scripts and run until
it’s shut down. They usually provide system services and multiple users rely
on them. Therefore, the daemons on startup are usually initiated by the user
with ID 0 (usually root) and might run with root privileges.

## zombie
A zombie process is a process that has been terminated, but is still
recognized through its pid. It has no address space. Zombie processes
continue to exist for as long as their parent processes run. This means that
until we exit the main process, shut down the system, or restart it, the zombie
process will still appear as <defunct> when listed by ps:

## Running services with init and systemd
Let’s use this opportunity to discuss the init and the systemd process
daemons. There are others as well, but we’ve decided to retain our focus on
these two. The first one is the initial process, executed on a Linux system by
the kernel, and its pid is always 1:
```
$ ps -p 1
PID TTY TIME CMD
1 ? 04:53:20 systemd
```
It is known as the parent of all processes on the system as it is used to
initialize, manage, and track other services and daemons. The first init
daemon for Linux is called Init and it defines six system states. All system
services are mapped to those states, respectively. Its script is used to start
processes in a pre-defined order, which is occasionally used by system
programmers. One possible reason to use this is to reduce the startup
duration of the system. To create a service or edit the script, you could
modify /etc/init.d. As this is a directory, we could list it with the ls
command and see all the services that could be run through init.


You can list the status of the available services through the following
command:
```
$ service --status-all
[ + ] acpid
[ - ] alsa-utils
[ - ] anacron
...
[ + ] ufw
[ - ] uuidd
[ - ] x11-common
We could stop the firewall service – ufw:
$ service ufw stop
Now, let’s check its status:
$ service ufw status
● ufw.service - Uncomplicated firewall
```

Now, let’s start it again and check its status once more:
```
$ service ufw start
$ service ufw status
● ufw.service - Uncomplicated firewall
```

## systemd
systemd is an init daemon that represents the modern approach to running
services on Linux systems. It provides a parallel system services startup
feature, which additionally speeds up the initialization procedure. Each
service is stored in a .service file under the /lib/systemd/system or
/etc/systemd/system directory. The services found in /lib are definitions
for system startup services and those in /etc are for the services that start
during system runtime. Let’s list them:
```bash
$ ls /lib/systemd/system
accounts-daemon.service
acpid.path
acpid.service
...
sys-kernel-config.mount
sys-kernel-debug.mount
sys-kernel-tracing.mount
syslog.socket
$ ls /etc/systemd/system
bluetooth.target.wants
display-manager.service
…
timers.target.wants
vmtoolsd.service
```
Before we continue with an example, let’s put one disclaimer here – systemd
has a much more complex interface than init. 


The process daemon and the startup procedures are a large area of expertise
in system administration, programming, monitoring, and obtaining execution
flow information. 

# Portable Operating System Interface (POSIX)
The POSIX standard has the main task of maintaining compatibility between
different OSs.

POSIX defines both the system- and the user-level APIs with one remark:
using POSIX, the programmer doesn’t need to distinguish between system
calls and library functions.

The POSIX API is frequently used in the C programming language. Thus, it is
compilable with C++. Additional functions are provided to the system call
interface in a few important areas of system programming: file operations,
memory management, process and thread control, networking and
communications, and regular expressions – as you can see, it pretty much
covers everything that the already existing system calls do. Just don’t get
confused and think that this is always the case.
As with every standard, POSIX has multiple versions, and you must be
aware of which one is present in your system. It also could be a part of some
environment subsystem, such as the Microsoft POSIX subsystem for
Windows. This is a key remark as it is possible that the environment itself
doesn’t expose the entire interface to you. One reason could be the security
assessment of the system.
With the evolution of POSIX, rules for code quality have been established.
Some of them are related to multithreaded memory access,
synchronization mechanisms and concurrent executions, security and
access restrictions, and type safety. A famous concept in POSIX’s
software requirements is write once, adopt everywhere.


Using POSIX allows software engineers to generalize their OS-related code
and declare it as not-OS-specific. This allows easier and faster reintegration
of the software, thus reducing the time to market. System programmers can
also easily switch from one system to another while still writing the same
type of code.

