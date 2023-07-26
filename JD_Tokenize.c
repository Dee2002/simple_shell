/*
 * Simple Shell 1.0 +
 * Created by Julius Kaboyo in collaboration with Delsa Marasha
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#define BUFFER_SIZE 1024
// Function to execute a command
void execute_command(char *command)
{
pid_t pid;
int status;
pid = fork();
if (pid < 0)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
// Child process
char *argv[3];
argv[0] = "/bin/sh";
argv[1] = "-c";
argv[2] = command;
execv("/bin/sh", argv);
perror("execv"); // This line will be reached if execv fails
exit(EXIT_FAILURE);
}
else
{
// Parent process
do
{
if (waitpid(pid, &status, 0) == -1)
{
perror("waitpid");
exit(EXIT_FAILURE);
}
}
while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}
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
// Tokenize user_input based on the command separator ";"
char *command = strtok(user_input, ";");
while (command != NULL)
{
// Remove leading and trailing spaces from the command
char *start = command;
while (*start == ' ')
start++;
char *end = command + strlen(command) - 1;
while (*end == ' ')
end--;
*(end + 1) = '\0';
// Execute the command
execute_command(start);
// Move to the next command (if any)
command = strtok(NULL, ";");
}
}
// Free memory and exit
free(user_input);
return 0;
}