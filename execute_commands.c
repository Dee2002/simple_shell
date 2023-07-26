#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "main.h"

/**
* execute_command - Executes the given command with its arguments.
*
* This function checks if the command is a built-in
* using `handle_builtin_command()`.
* If it is a built-in, the corresponding action is taken.
* Otherwise, it forks a new process and executes the command using `execve()`.
* The parent process waits for the child process to exit before returning.
*
* @argv: Null-terminated array of strings representing the command
*  and its arguments.
*
* Return: 0 on successful execution. If an error occurs during fork or execve,
*  the function returns 1.
*/
int execute_command(char **argv)
{
pid_t pid;
int status = 0;

/* Check if the command is a built-in */
if (handle_builtin_command(argv))
{
return (0);
}

/* Fork and exec the command */
pid = fork();
if (pid == 0)
{
/* Child process */
execve(argv[0], argv, environ);
perror(argv[0]);
_exit(127);
}
else if (pid < 0)
{
/* Error */
perror("fork");
return (1);
}
else
{
/* Parent process */
wait(&status);
}

return (status);
}
