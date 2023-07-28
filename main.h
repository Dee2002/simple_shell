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
void print_prompt(void);
char *get_line(void);
char **parse_line(char *line);
int execute_command(char **command);
int handle_builtin_command(char **argv);
int waitpid(pid_t pid, int *status, int option);
void print_env(void);

void free_argv(char **argv);
int handle_builtin_command(char **argv);
int builtin_pwd(void);
int builtin_cd(char **args);
int builtin_exit(void);
int builtin_ls(void);
void append_token(char **tokens, int *position, const char *token_start);

int execute_echo(const char **args);
int execute_pwd(void);
int execute_cat(char *args[]);
int execute_cd(char *args[]);
int execute_ls(char *args[]);
int execute_exit(char *args[]);

int handle_comments(char *line);
int handle_variables(char *line);
int execute_command(char **command);
int handle_command_file(char *filename);
int execute_command_wrapper(const char **args);



#endif
