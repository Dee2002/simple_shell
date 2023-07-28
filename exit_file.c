#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
* execute_exit - Exits the shell.
* @args: The command arguments.
*
* Return: Always returns 0.
*/
int execute_exit(char **args)
{
int status = 0;
int i = 2;

if (args[1] == NULL)
{
write(STDERR_FILENO, "Error: Incorrect number of arguments\n",
strlen("Error: Incorrect number of arguments\n"));
_exit(EXIT_FAILURE);
}

status = atoi(args[1]);

while (args[i] != NULL)
{
char *arg = args[i];
while (*arg != '\0')
{
write(STDOUT_FILENO, arg, 1);
arg++;
}
write(STDOUT_FILENO, " ", 1);
i++;
}
write(STDOUT_FILENO, "\n", 1);

if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
{
_exit(EXIT_FAILURE);
}

_exit(WEXITSTATUS(status));
}
