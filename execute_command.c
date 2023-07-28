#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

#define MAX_ARGS 1024

/**
* execute_command - executes the given command with the specified arguments.
*
* @args: An array of strings representing the command and its arguments. The
* last element of the array must be NULL.
*/
void execute_command(char **args)
{
pid_t child_pid, wait_pid;
int status;

child_pid = fork();
if (child_pid == -1)
{
perror("fork");
return;
}
if (child_pid == 0)
{
/* Child process */
if (execvp(args[0], args) == -1)
{
perror("execvp");
exit(1);
}
}
else
{
/* Parent process */
do {
wait_pid = waitpid(child_pid, &status, WUNTRACED);
if (wait_pid == -1)
{
perror("waitpid");
return;
}
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}
