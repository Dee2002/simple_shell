#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* in_path - Handles the path.
* @path: The path given.
*
* Return: 0 on success, non-zero on failure.
*/
int in_path(char *path)
{
char *element;
pid_t process_ID = fork();

if (path == NULL)
{
perror("1: path: not found");
_exit(EXIT_FAILURE);
}

if (process_ID < 0)
{
perror("1: fork: error occurred");
return (1);
}
else if (process_ID == 0)
{
element = strtok(path, "/");
while (element != NULL)
{
if (access(element, X_OK) == 0)
{
write(STDOUT_FILENO, "Is an executable\n", strlen("Is an executable\n"));
_exit(0);
}
element = strtok(NULL, "/");
}
write(STDOUT_FILENO, "No executables found in the path\n",
strlen("No executables found in the path\n"));
_exit(-1);
}
wait(NULL);
return (0);
}
