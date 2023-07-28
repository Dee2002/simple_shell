#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

int handle_variables(char (*args)[1024]);

/**
* handle_comments - remove comments from a string
* @args: command line argument value
* Return: 0 on success, 1 on failure.
*/
int handle_comments(char (*args)[1024])
{
int i;

if ((*args)[0] == '\0')
return (0);
for (i = 0; (*args)[i] != '\0'; i++)
{
char *arg = *args;
while (strchr(arg, '#') != NULL)
*strchr(arg, '#') = '\0';
}
return (0);
}

/**
* handle_variables - replace variables in a string with their values.
* @args: command line argument value
* Return: 0 on success, 1 on failure.
*/
int handle_variables(char (*args)[1024])
{
int i;

if ((*args)[0] == '\0')
return (0);

for (i = 0; (*args)[i] != '\0'; i++)
{
char *arg = *args;
while (strchr(arg, '$') != NULL)
{
char *variable = strchr(arg, '$');
char *value = getenv(variable + 1);
if (value != NULL)
memmove(variable, value, strlen(value) + 1);
}
}
return (0);
}

/**
* handle_command_file - executes the commands in a file
* @filename: name of command file
* Return: 0 on success, 1 on failure.
*/
int handle_command_file(char *filename)
{
FILE *file;
char line[1024];
int ret;

file = fopen(filename, "r");
if (file == NULL)
{
perror("fopen");
return (1);
}

while (fgets(line, sizeof(line), file) != NULL)
{
line[strcspn(line, "\n")] = '\0';
handle_variables(&line);
handle_comments(&line);
ret = system(line);
if (ret != 0)
{
perror("system");
fclose(file);
return (1);
}
}

fclose(file);
return (0);
}
