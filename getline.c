#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
* get_line - Reads a line of input from the standard input.
*
* This function reads a line of input from the standard input (stdin)
* and stores it in a dynamically allocated buffer.
* The buffer is automatically resized as needed to
* accommodate the input line.
*
* Return: A pointer to the dynamically allocated buffer containing the
* input line.
*         If there is an error or the end of the input is reached,
*         it returns NULL.
*         The caller is responsible for freeing the memory allocated
*         for the buffer.
*/

char *get_line(void)
{
char *line = NULL;
size_t line_length = 0;
ssize_t bytes_read;

/* Read the line one character at a time */
do {
bytes_read = getline(&line, &line_length, stdin);
if (bytes_read == -1)
{
if (errno == EINTR)
{
continue;
}
else
{
return (NULL);
}
}
} while (line[bytes_read - 1] == '\n');

/* Remove the newline character from the end of the line */
line[bytes_read - 1] = '\0';

return (line);
}
