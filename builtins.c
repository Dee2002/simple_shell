#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

/**
* my_setenv - initializes new env variable, or modifies an existing one.
* @variable: a named storage location that holds a value
* @value: data stored in a variable
* @overwrite: replacing the existing value of a variable with a new value
* Return: 0 on success, 1 on failure
*/
int my_setenv(const char *variable, const char *value, int overwrite)
{
int result;
/* Check for the correct number of arguments */
if (variable == NULL || value == NULL)
{
write(2, "Usage: setenv VARIABLE VALUE\n", 29);
return (1);
}
/* Check if the variable already exists */
if (getenv(variable) != NULL)
{
if (overwrite == 0)
{
write(2, "The variable '", 14);
write(2, variable, strlen(variable));
write(2, "' already exists.\n", 18);
return (1);
}
}
result = setenv(variable, value, 1);
if (result < 0)
{
perror("setenv: not found");
return (1);
}
return (0);
}

/**
* my_unsetenv - removes an environment variable.
* @variable: a named storage location that holds a value.
* Return: 0 on success, 1 on failure.
*/
int my_unsetenv(const char *variable)
{
int result;
/* Check for the correct number of arguments */
if (variable == NULL)
{
write(2, "Usage: unsetenv VARIABLE\n", 25);
return (1);
}
result = unsetenv(variable);
if (result < 0)
{
perror("unsetenv: not found");
return (1);
}
return (0);
}

/**
* cd - changes the current directory of the process.
* @args: the command-line argument
* Return: 0 on success, 1 on failure.
*/
int cd(char **args)
{
if (args[1] == NULL)
{
write(2, "cd: no directory specified\n", 27);
return (1);
}
else
{
if (chdir(args[1]) != 0)
{
perror("cd");
return (1);
}
}
return (0);
}

/**
* pwd - Prints the current working directory to the standard output
*
* Return: 0 on success
*/
int pwd(void)
{
char *path = malloc(1024);
if (path == NULL)
{
perror("pwd");
return (1);
}
if (getcwd(path, 1024) == NULL)
{
perror("pwd");
free(path);
return (1);
}
write(1, path, strlen(path));
write(1, "\n", 1);
free(path);
return (0);
}

/**
* echo - Prints the specified arguments to the standard output,
* separated by spaces
* @args: argument value
* Return: 0 on success
*/
int echo(char **args)
{
int i;
for (i = 1; args[i]; i++)
{
write(1, args[i], strlen(args[i]));
write(1, " ", 1);
}
write(1, "\n", 1);
return (0);
}
