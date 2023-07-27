#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* my_exit - Exits the shell using an int
* @count: The arg count
* @vec: Double pointer to the array of strings
*
* Return: 0 on success
*/
int my_exit(int count, char **vec)
{
int status = 0;
int i;

if (count < 2)
{
write(STDERR_FILENO, "Error: Incorrect number of arguments\n",
strlen("Error: Incorrect number of arguments\n"));
_exit(EXIT_FAILURE);
}

status = atoi(vec[1]);

for (i = 2; i < count; i++)
{
write(STDOUT_FILENO, vec[i], strlen(vec[i]));
write(STDOUT_FILENO, " ", 1);
}
write(STDOUT_FILENO, "\n", 1);

if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
_exit(EXIT_FAILURE);

_exit(WEXITSTATUS(status));
}
