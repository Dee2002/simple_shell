# Shell Project - Simple UNIX Command Interpreter

## Overview

This project aims to create a simple UNIX command interpreter (shell) similar to `/bin/sh` that allows users to interact with the operating system by executing commands. The shell will read user input, parse it, and execute the corresponding system commands.

## Learning Objectives

By completing this project, you will gain a deeper understanding of the following concepts:

- Who designed and implemented the original Unix operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming language (the direct predecessor to the C programming language)
- Who is Ken Thompson
- How a shell works
- What is a pid and a ppid
- How to manipulate the environment of the current process
- The difference between a function and a system call
- How to create processes
- The three prototypes of main
- How the shell uses the PATH to find programs
- How to execute another program with the execve system call
- How to suspend the execution of a process until one of its children terminates
- What is EOF / “end-of-file”?

## Requirements

- Allowed editors: vi, vim, emacs
- All files will be compiled on Ubuntu 20.04 LTS using gcc with the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All files should end with a new line
- A `README.md` file, at the root of the project folder, is mandatory
- Code should follow the Betty style guidelines
- The shell should not have any memory leaks
- Each file should contain no more than 5 functions
- All header files should be include guarded
- Use system calls only when necessary
- Implement a simple shell with the same output and error output as `/bin/sh`

## Allowed Functions and System Calls

The following functions and system calls are allowed to be used in the project:

- access
- chdir
- close
- closedir
- execve
- exit
- _exit
- fflush
- fork
- free
- getpid
- isatty
- kill
- malloc
- open
- opendir
- perror
- read
- readdir
- signal
- stat (__xstat)
- lstat (__lxstat)
- fstat (__fxstat)
- strtok
- wait
- waitpid
- wait3
- wait4
- write

## Compilation

The shell will be compiled with the following command:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Testing

The shell should work in both interactive and non-interactive modes. Interactive mode allows users to input commands directly to the shell, while non-interactive mode reads commands from a file.

Example of interactive mode:

$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
$

Example of non-interactive mode:

$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
