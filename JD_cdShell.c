#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
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
// Check if the command is cd
if (strncmp(user_input, "cd", 2) == 0)
{
char *path = strtok(user_input + 3, " ");
char new_path[PATH_MAX];
if (path == NULL || strcmp(path, "") == 0)
{
// If no argument provided, change to HOME directory
path = getenv("HOME");
if (path == NULL)
{
fprintf(stderr, "MyShell: HOME environment variable not set.\n");
continue;
}
}
else if (strcmp(path, "-") == 0)
{
// If "-" is provided, change to the previous directory
path = getenv("OLDPWD");
if (path == NULL)
{
fprintf(stderr, "MyShell: OLDPWD environment variable not set.\n");
continue;
}
}
if (chdir(path) == -1)
{
fprintf(stderr, "MyShell: Failed to change directory.\n");
}
else
{
// Update PWD and OLDPWD environment variables
if (getcwd(new_path, sizeof(new_path)) != NULL)
{
setenv("PWD", new_path, 1);
setenv("OLDPWD", getenv("PWD"), 1);
}
else
{
perror("MyShell");
}
}
continue;
}
// ... (rest of the code remains the same)
}
// Free memory and exit
free(user_input);
return 0;
}
