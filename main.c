#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include "main.h"

#define MAX_INPUT_LEN 1024
#define MAX_ARGS 1024

int execute_ls(char *args[]);
int execute_exit(char *args[]);
int execute_cd(char *args[]);
int execute_pwd(void);
int execute_echo(const char **args);
int execute_cat(char *args[]);
int execute_command_wrapper(const char **args);

const char *COMMAND_NAMES[] = {
"cd",
"cat",
"pwd",
"echo",
"ls",
"exit",
};

#define NUM_COMMANDS (sizeof(COMMANDS) / sizeof(CommandExecutor))


/**
* execute_command_wrapper - Wrapper function to execute commands.
* @args: The command arguments.
*
* This function serves as a dispatcher to call the appropriate command
* execution function based on the command name.
*
* Return: The return value of the executed command.
*/
int execute_command_wrapper(const char **args)
{
if (args[0] != NULL)
{
if (strcmp(args[0], COMMAND_NAMES[0]) == 0)
{
return (execute_cd((char **)args));
}
else if (strcmp(args[0], COMMAND_NAMES[1]) == 0)
{
return (execute_cat((char **)args));
}
else if (strcmp(args[0], COMMAND_NAMES[2]) == 0)
{
return (execute_pwd());
}
else if (strcmp(args[0], COMMAND_NAMES[3]) == 0)
{
return (execute_echo((const char **)args));
}
else if (strcmp(args[0], COMMAND_NAMES[4]) == 0)
{
return (execute_ls((char **)args));
}
else if (strcmp(args[0], COMMAND_NAMES[5]) == 0)
{
return (execute_exit((char **)args));
}
}
return (-1);
}

/**
* sigint_handler - Handles the SIGINT (Ctrl+C) signal
*/
void sigint_handler(void)
{
}

/**
* main - Shell entry point.
*
* This function implements the main shell loop, where it reads user input,
* parses it into commands, and executes them accordingly.
*
* Return: The exit status of the shell.
*/
int main(void)
{
char *line;
const char **parsed_line = NULL;
int status = 0;

signal(SIGINT, SIG_IGN);

while (1)
{
char prompt[] = ":) ";
write(STDOUT_FD, prompt, sizeof(prompt) - 1);

line = get_line();

if (!line)
{
/* Handle error for get_line() function*/
perror("Error reading input");
break;
}

parsed_line = (const char **)parse_line(line);

if (!parsed_line)
{
/*Handle error for parse_line() function*/
perror("Error parsing input");
free(line);
break;
}

if (*parsed_line == NULL)
{
/*Check for empty command line*/
free(line);
free_argv((char **)parsed_line);
continue;
}

status = execute_command_wrapper(parsed_line);

free(line);
free_argv((char **)parsed_line);
}

return (status);
}
/**
* execute_cat - displays the contents of a file
* @args: the command arguments
* Return: 0 on success, 1 0n failure.
*/

int execute_cat(char *args[])
{
int fd;
char buffer[1024];
ssize_t n;
if (args[1] == NULL)
{
write(STDERR_FD, args[0], strlen(args[0]));
write(STDERR_FD, ": missing operand\n", 18);
return (1);
}
fd = open(args[1], O_RDONLY);
if (fd == -1)
{
perror(args[0]);
return (1);
}
while ((n = read(fd, buffer, sizeof(buffer))) > 0)
{
write(STDOUT_FD, buffer, n);
}
close(fd);
return (0);
}

/**
* execute_pwd - Prints the current working directory.
*
* Return: 0 on success, 1 on failure.
*/
int execute_pwd(void)
{
char cwd[1024];

if (getcwd(cwd, sizeof(cwd)) != NULL)
{
write(STDOUT_FD, cwd, strlen(cwd));
write(STDOUT_FD, "\n", 1);
return (0);
}
else
{
perror("pwd");
return (1);
}
}
