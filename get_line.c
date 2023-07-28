#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
* getline_from_scratch - Custom getline function
* @read_line: double pointer which reads the input
* @size_of_buf: The size of the buffer
*
* Return: 0 on success, -1 on failure
*/
ssize_t getline_from_scratch(char **read_line, size_t *size_of_buf)
{
int count = 0, x = 0, fetchar = getchar();
size_t *mem = malloc(1 * (*size_of_buf)), *new_mem;

if (read_line == NULL || size_of_buf == NULL)
{
perror("1: An error has occured\n");
exit(EXIT_FAILURE);
}
if (mem == NULL)
{
perror("Error: malloc: process failed!\n");
return (-1);
}
while (1)
{
if (fetchar == EOF || fetchar == '\n')
{
mem[count] = '\0';
break;
}
mem[count++] = fetchar;
if ((size_t)count >= *size_of_buf)
{
*size_of_buf *= 2;
new_mem = malloc(1 * (*size_of_buf));
if (new_mem == NULL)
{
perror("Error: malloc: process failed\n");
free(mem);
return (-1);
}
for (; mem[x] != '\0'; x++)
new_mem[x] = mem[x];
free(mem);
mem = new_mem;
}
fetchar = getchar();
}
*read_line = (char *)mem;
return (count);
}
