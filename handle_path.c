#include "main.h"

/**
* in_path - Handles the path
* @path: The given path
*
* Return: 0 on success, no-zero on failure
*/
int in_path(char *path)
{
char *element;
pid_t process_ID = fork();

if (path == NULL)
{
perror("1: path: not found");
exit(EXIT_FAILURE);
}

if (process_ID < 0)
{
perror("1: fork: error occured");
return (1);
}
else if (process_ID == 0)
{
element = strtok(path, "/");
while (element != NULL)
{
if (access(element, X_OK) == 0)
{
write(STDOUT_FILENO, "Is an executable\n",
strlen("Is an executable\n"));
;
}
element = strtok(NULL, "/");
}
write(STDOUT_FILENO, "Executable: not found\n",
strlen("Executable: not found\n"));
return (-1);
}
wait(NULL);
return (0);
}
