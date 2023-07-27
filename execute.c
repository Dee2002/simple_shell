#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"

/**
* search_in_path - Searches for an executable command in
* the directories listed in the PATH environment variable.
*
* @command: The name of the command to search for.
*
* Return: Pointer to a dynamically allocated buffer
* containing the full path to the command if found,
*         or NULL if the command is not found in any of the directories
*         or if memory allocation fails.
*         The caller is responsible for freeing the
*         memory allocated for the returned buffer.
*/
char *search_in_path(char *command)
{
char *path = getenv("PATH");
char *dir = strtok(path, ":");
struct stat st;
size_t dir_len, command_len;
char *executable;

command_len = strlen(command);

while (dir)
{
dir_len = strlen(dir);
executable = (char *)malloc(dir_len + command_len + 2);

if (!executable)
{
perror("malloc");
_exit(EXIT_FAILURE);
}

strcpy(executable, dir);
strcat(executable, "/");
strcat(executable, command);

if (stat(executable, &st) == 0 && st.st_mode & S_IXUSR)
{
return (executable);
}

free(executable);
dir = strtok(NULL, ":");
}

return (NULL);
}


/**
* execute_command - Executes the given command with its arguments.
*
* @argv: The array of command arguments.
*
* Return: The exit status of the executed command.
*/
int execute_command(char **argv)
{
char *executable;
pid_t pid;
int status;
char err_msg[] = "execve failed\n";

executable = search_in_path(argv[0]);
if (!executable)
{
char err_msg[] = "command not found\n";
write(STDERR_FILENO, err_msg, sizeof(err_msg) - 1);
return (1);
}

pid = fork();
if (pid == 0)
{
/* Child process */
execve(executable, argv, NULL);
write(STDERR_FILENO, err_msg, sizeof(err_msg) - 1);
_exit(EXIT_FAILURE);
}
else if (pid < 0)
{
/* Forking error */
char err_msg[] = "fork failed\n";
write(STDERR_FILENO, err_msg, sizeof(err_msg) - 1);
}
else
{
/* Parent process */
waitpid(pid, &status, 0);
return (WEXITSTATUS(status));
}
return (1);
}
