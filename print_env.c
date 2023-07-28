#include "main.h"

/**
* print_env - Prints current environment
*
* Return: 0
*/
int print_env(void)
{
size_t count = 0;

while (environ[count] != NULL)
{
write(STDOUT_FILENO, environ[count], strlen(environ[count]));
write(STDOUT_FILENO, "\n", 1);
count++;
}
return (0);
}
