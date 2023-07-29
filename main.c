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

#define STDOUT_FD 1
#define STDERR_FD 2
#define SHELL_NAME "hsh"
#define MAX_ARGS 1024

int execute_cd(char *args[]);
int execute_cat(char *args[]);
int execute_pwd(void);
int execute_echo(char *args[]);

/**
* main - shell entry point
*
* Return: 0 always
*/
int main(void)
{
size_t size = 0;
char *inputComm = NULL, *arg[1024] = {NULL}, *value;
int status, counter = 0, i = 0;

while (getline(&inputComm, &size, stdin) != -1)
{
if (inputComm[strlen(inputComm) - 1] == '\n')
inputComm[strlen(inputComm) - 1] = '\0';

if (strcmp(inputComm, "exit") == 0)
break;
else if (inputComm[0] == '\0')
continue;

counter = 0;
for (value = strtok(inputComm, " "); value != NULL && counter < 1024;
value = strtok(NULL, " "))
arg[counter++] = strdup(value);
arg[counter] = NULL;

if (fork() == 0)
{
status = execvp(arg[0], arg);
if (status != 0)
perror(arg[0]);
exit(EXIT_FAILURE);
}
wait(NULL);

for (i = 0; i < counter; i++)
{
free(arg[i]);
arg[i] = NULL;
}
}

free(inputComm);
return (0);
}

/**
* execute_echo - displays the provided arguments.
* @args: the command arguments.
* The content to be displayed starts from args[1].
* Return: 0 on success, 1 on failure.
*/
int execute_echo(char *args[])
{
int i = 1;

while (args[i] != NULL)
{
write(STDOUT_FD, args[i], strlen(args[i]));
write(STDOUT_FD, " ", 1);
i++;
}

write(STDOUT_FD, "\n", 1);
return (0);
}

/**
* execute_cd - Changes the current working directory.
*
* @args: the command arguments.
* args[1] is the directory path to change to.
* Return: 0 on success, 1 on failure.
*/
int execute_cd(char *args[])
{
if (args[1] == NULL)
{
write(STDERR_FD, args[0], strlen(args[0]));
write(STDERR_FD, ": expected argument to \"cd\"\n", 29);
return (1);
}

if (chdir(args[1]) != 0)
{
perror(args[0]);
return (1);
}
return (0);
}

/**
* execute_pwd - prints the current working directory.
*
* Return: 0 on success, 1 on failure.
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
* execute_cat - displays the contents of a file.
* @args: the command arguments. args[1] is the file to display.
* Return: 0 on success, 1 on failure.
*/
int execute_cat(char *args[])
{
int fd;
char buffer[1024];
ssize_t n;

if (args[1] == NULL)
{
write(STDERR_FD, args[0], strlen(args[0]));
write(STDERR_FD, ": missing operand\n", 18);
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
