#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
* print_env - Prints the environment variables to the standard output.
*
* This function displays the env variables stored in the `environ` array,
* which contains strings in the format "VARIABLE=VALUE".Each env variable
* is printed on a separate line, followed by a newline character.
*
* Return: void
*/

extern char **environ;
void print_env(void)
{
char **env = environ;
while (*env)
{
write(1, *env, strlen(*env));
write(1, "\n", 1);
env++;
}
}
