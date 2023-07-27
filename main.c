#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "main.h"

/**
* main - Shell entry point.
*
* Return: 0 always.
*/

int main(void)
{
char *line;
char **parsed_line;
int status = 0;

while (1)
{
print_prompt();
line = get_line();

if (!line)
break;

parsed_line = parse_line(line);

status = execute_command(parsed_line);

free(line);
free_argv(parsed_line);
}

return (status);
}

/**
* execute_cd - changes the current working directory.
* @args: the command arguments.
* args[1] is the directory path to change to.
* Return: 0 on success,1 on failure.
*/
int execute_cd(char *args[])
{
if (args[1] == NULL)
{
write(STDERR_FD, args[0], strlen(args[0]));
write(STDERR_FD, ": expected argument to \"cd\"\n", 29);
return (1);
}
if (chdir(args[1])  != 0)
{
perror(args[0]);
return (1);
}
return (0);
}

/**
* execute_cat - displays the contents of a file
* @args: the command arguments
* Return: 0 on success, 1 0n failure.
*/

int execute_cat(char *args[])
{
int fd;
char buffer[1024];
ssize_t n;
if (args[1] == NULL)
{
write(STDERR_FD, args[0], strlen(args[0]));
write(STDERR_FD, ": missing operand\n", 18);
return (1);
}
fd = open(args[1], O_RDONLY);
if (fd == -1)
{
perror(args[0]);
return (1);
}
while ((n = read(fd, buffer, sizeof(buffer))) > 0)
{
write(STDOUT_FD, buffer, n);
}
close(fd);
return (0);
}

/**
* execute_pwd - prints current working directory
*
* Return: 0 on success,1 on failure.
*/
int execute_pwd(void)
{
char cwd[1024];
if (getcwd(cwd, sizeof(cwd)) != NULL)
{
write(STDOUT_FD, cwd, strlen(cwd));
write(STDOUT_FD, "\n", 1);
}
else
{
perror("pwd");
return (1);
}
return (0);
}

/**
* execute_echo - displays provided arguments
* @args: command arguments
*
* Return: 0 on success,1 on failure.
*/
int execute_echo(char *args[])
{
int i = 1;
while (args[i] != NULL)
{
write(STDOUT_FD, args[i], strlen(args[i]));
write(STDOUT_FD, " ", 1);
i++;
}
write(STDOUT_FD, "\n", 1);
return (0);
}
