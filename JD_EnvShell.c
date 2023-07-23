#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define BUFFER_SIZE 1024
int main(void)
{
char *user_input;
size_t bufsize = BUFFER_SIZE;
user_input = (char *)malloc(bufsize * sizeof(char));
while (1)
{
printf("MyShell$ ");
// Read user input
if (getline(&user_input, &bufsize, stdin) == -1)
break; // Handle "end of file" (Ctrl+D) condition
// Remove the newline character at the end of user_input
user_input[strcspn(user_input, "\n")] = 0;
// Check if the command is setenv
if (strncmp(user_input, "setenv", 6) == 0)
{
char *key = strtok(user_input + 7, " ");
char *value = strtok(NULL, " ");
if (key != NULL && value != NULL)
{
if (setenv(key, value, 1) == -1)
{
perror("MyShell");
}
}
else
{
fprintf(stderr, "MyShell: Invalid syntax. Usage: setenv VARNAME VALUE\n");
}
continue;
}
// Check if the command is unsetenv
if (strncmp(user_input, "unsetenv", 8) == 0)
{
char *key = strtok(user_input + 9, " ");
if (key != NULL)
{
if (unsetenv(key) == -1)
{
perror("MyShell");
}
}
else
{
fprintf(stderr, "MyShell: Invalid syntax. Usage: unsetenv VARNAME\n");
}
continue;
}
// Check if the command is cd
if (strncmp(user_input, "cd", 2) == 0)
{
char *path = strtok(user_input + 3, " ");
if (path != NULL)
{
if (chdir(path) == -1)
{
fprintf(stderr, "MyShell: Failed to change directory.\n");
}
}
else
{
fprintf(stderr, "MyShell: Invalid syntax. Usage: cd DIRECTORY\n");
}
continue;
}
// Fork a child process
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
}
else if (pid == 0)
{
// Child process
if (execvp(user_input, &user_input) == -1)
{
perror("MyShell");
}
exit(EXIT_FAILURE);
// This line will be reached only if execvp fails
}
else
{
// Parent process
int status;
waitpid(pid, &status, 0);
}
}
// Free memory and exit
free(user_input);
return 0;
}:wq

