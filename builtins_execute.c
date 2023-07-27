#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "main.h"

/**
* execute_cd - changes the current working directory.
* @args: the command arguments.
* args[1] is the directory path to change to.
* Return: 0 on success, 1 on failure.
*/
int execute_cd(char *args[])
{
if (args[1] == NULL)
{
write(STDERR_FD, args[0], strlen(args[0]));
write(STDERR_FD, ": expected argument to \"cd\"\n", 29);
return (1);
}

if (chdir(args[1]) != 0)
{
perror(args[0]);
return (1);
}

return (0);
}

/**
* execute_echo - displays provided arguments
* @args: command arguments
*
* Return: 0 on success, 1 on failure.
*/
int execute_echo(char *args[])
{
int i = 1;
while (args[i] != NULL)
{
write(STDOUT_FD, args[i], strlen(args[i]));
write(STDOUT_FD, " ", 1);
i++;
}
write(STDOUT_FD, "\n", 1);
return (0);
}