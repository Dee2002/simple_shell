#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
* get_line - Reads a line of input from the user.
*
* Return: Pointer to the line read from input (or NULL on error or EOF).
*/
char *get_line(void)
{
char *line = NULL;
size_t bufsize = 0;
ssize_t n_read = getline(&line, &bufsize, stdin);
if (n_read == -1)
{
if (feof(stdin))
{
_exit(EXIT_SUCCESS);
}
perror("getline");
_exit(EXIT_FAILURE);
}
return (line);
}
