#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
* alias - define or display aliases
* @args: arguments
* Return: 0 on success, 1 on failure
*/
int alias(char **args)
{
if (args[1] == NULL)
{
/* If not, print a list of all aliases. */
char **alias = environ;
for (; *alias != NULL; alias++)
{
if (strncmp(*alias, "alias=", 6) == 0)
{
puts(*alias);
}
}
}
else
{
/* If the user has provided arguments, define an alias for each argument. */
int i = 1;
for (; args[i] != NULL; i++)
{
/* Check if the alias exists. */
char *alias_name = args[i];
char *alias_value = args[i + 1];
if (getenv(alias_name) != NULL)
{
/* If the alias exists, then replace the value. */
setenv(alias_name, alias_value, 1);
}
else
{
/* If the alias does not exist, define it. */
setenv(alias_name, alias_value, 1);
}
}
}
return (0);
}
