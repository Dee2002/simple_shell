#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
* handle_builtin_command - Checks and handles if the command
* is a built-in command.
*
* @argv: The array of command arguments.
*
* Return: 1 if the command is a built-in and handled, 0 otherwise.
*/
int handle_builtin_command(char **argv)
{
if (strcmp(argv[0], "pwd") == 0)
{
return (builtin_pwd());
}
else if (strcmp(argv[0], "cd") == 0)
{
return (builtin_cd(argv));
}
else if (strcmp(argv[0], "exit") == 0)
{
return (builtin_exit());
}
else if (strcmp(argv[0], "ls") == 0)
{
return (builtin_ls());
}
return (0);
}

/**
* builtin_pwd - Implements the 'pwd' built-in command.
*
* Return: 0 on success, 1 on failure.
*/
int builtin_pwd(void)
{
char cwd[1024];
if (getcwd(cwd, sizeof(cwd)) != NULL)
{
write(STDOUT_FILENO, cwd, strlen(cwd));
write(STDOUT_FILENO, "\n", 1);
return (0);
}
perror("getcwd");
return (1);
}

/**
* builtin_cd - Implements the 'cd' built-in command.
*
* @args: The array of command arguments,
* where args[1] is the directory to change to.
*
* Return: 0 on success, 1 on failure.
*/
int builtin_cd(char **args)
{
if (args[1] == NULL)
{
write(STDERR_FILENO, "Expected argument to \"cd\"\n", 26);
return (1);
}

if (chdir(args[1]) != 0)
{
perror("chdir");
return (1);
}
return (0);
}
/**
* builtin_exit - Implements the 'exit' built-in command.
*
* Return: This function does not return; it exits the shell process.
*/
int builtin_exit(void)
{
_exit(EXIT_SUCCESS);
}
/**
* builtin_ls - Implements the 'ls' built-in command.
*
* Return: 0 on success, 1 on failure.
*/
int builtin_ls(void)
{
pid_t pid = fork();

if (pid == 0)
{
char *const ls_args[] = {"ls", NULL};
execve("/bin/ls", ls_args, NULL);
perror("execve");
_exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("fork");
return (1);
}
else
{
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status))
{
if (WEXITSTATUS(status) == 0)
{
return (0); /*Command executed successfully.*/
}
else
{
return (1); /*Command execution failed.*/
}
}
return (1); /*Error in child process execution.*/
}
}
