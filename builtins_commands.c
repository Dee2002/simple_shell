#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
* handle_builtin_command - Handles built-in shell commands "exit" and "env".
*
* @argv: Null-terminated array of strings representing the command
* and its arguments.
*
* Return: 0 if the command is not a built-in. Otherwise, the function executes
* the appropriate built-in action and returns the corresponding value.
*/

int handle_builtin_command(char **argv)
{
if (strcmp(argv[0], "exit") == 0)
{
/*Exit the shell*/
return (0);
}
else if (strcmp(argv[0], "env") == 0)
{

/*Print the environment variables*/
print_env();
return (1); /*indicates  "env" command execution*/
}
else
{
/*The command is not a built-in*/
return (0);
}
}
