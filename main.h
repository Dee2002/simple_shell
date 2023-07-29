#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>

/* Constant definitions */
#define TOKEN_SIZE 64
#define STDOUT_FD 1
#define SHELL_NAME "hsh"
#define MAX_ARGS 1024
#define MAX_LINE_SIZE 1024
#define STDERR_FD 2

extern char **environ;

/**
* struct CommandExecutor - This struct defines a set
* of functions that can be used to execute
* common shell commands.
*
* @execute_cd: see in file
* @execute_cat: see in file
* @execute_pwd: see in file
* @execute_echo: see in file
* @execute_ls: see in file
* @execute_exit: see in file
* @execute_command: see in file
*/
struct CommandExecutor
{
int (*execute_cd)(char *args[]);
int (*execute_cat)(char *args[]);
int (*execute_pwd)(void);
int (*execute_echo)(char *args[]);
int (*execute_ls)(char *args[]);
int (*execute_exit)();
int (*execute_command)();
} CommandExecutor;

/* Function prototypes */
int main(void);

int _exiting_(int count, char **vec);
void execute_exit_builtin(void);
int my_setenv(const char *variable, const char *value, int overwrite);
int my_unsetenv(const char *variable);
int cd(char **args);
int pwd(void);
int echo(char **args);
int print_env(void);
void print_prompt(void);
void execute_command(char **args);
ssize_t getline_from_scratch(char **read_line, size_t *size_of_buf);
int handle_variables(char (*args)[1024]);
int handle_comments(char (*args)[1024]);
int handle_command_file(char *filename);
int execute_ls(void);
int execute_cd(char *args[]);
int execute_cat(char *args[]);
int execute_pwd(void);
int execute_echo(char *args[]);
int handle_args(int count, char **vec);
int alias(char **args);
char split_str(char *str, char delim);
int interpret(void);
int execute_cmd(char *command);

#endif
