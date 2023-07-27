#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "main.h"

#define MAX_LINE_SIZE 1024

int handle_comments(char *line);
int handle_variables(char *line);
int execute_command(char **command);
int handle_command_file(char *filename);

/**
* handle_comments - Removes comments from a string.
* @line: the input line to be parsed
*
* Return: 0 on success, 1 on failure.
*/
int handle_comments(char *line)
{
char *comment = strchr(line, '#');
if (comment != NULL)
*comment = '\0';
return (0);
}

/**
* handle_variables - Replaces variables in a string with their values.
* @line: input line to be parsed
*
* Return: 0 on success, 1 on failure.
*/
int handle_variables(char *line)
{
char *variable = strchr(line, '$');
char *value;
while (variable != NULL)
{
char *end = strpbrk(variable + 1, " \t\n\"\'$");
if (end != NULL)
*end = '\0';
value = getenv(variable + 1);
if (value != NULL)
{
size_t vlen = strlen(value);
memmove(variable, value, vlen);
memmove(variable + vlen, end, strlen(end) + 1);
}
else
{
memmove(variable, end, strlen(end) + 1);
}
variable = strchr(variable + 1, '$');
}
return (0);
}

/**
* handle_command_file - Processes and executes commands from a file.
* @filename: Name of the command file to be processed.
* Return:
*     The exit status of the last executed command.
*     Returns 0 if all commands were successfully
*     executed, or a non-zero value if an error occurred during
*     command execution or file handling.
*/
int handle_command_file(char *filename)
{
int i;
int ret = 0;
char line[MAX_LINE_SIZE];
char *delimiter = " ";
char *token = strtok(line, delimiter);
size_t read_len;
FILE *file = fopen(filename, "r");
char *command[4];

if (file == NULL)
{
_exit(1);
}

while (1)
{
if (fgets(line, sizeof(line), file) == NULL) /*Use FILE* pointer for fgets*/
{
break; /*Exit the loop when we reach the end of the file*/
}

read_len = strlen(line);
if (line[read_len - 1] == '\n')
{
line[read_len - 1] = '\0'; /*Remove newline character*/
}

while (token != NULL && i < 3)
{
command[i++] = token;
token = strtok(NULL, delimiter);
}

i = 0;
while (command[i] != NULL)
{
puts(command[i]);
i++;
}

if (ret != 0)
{
_exit(1);
}
}

fclose(file); /* Close the FILE* when done*/
return (ret);
}
