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
#include <errno.h>
#define BUFFER_SIZE 1024
#define MAX_ALIASES 50
// Data structure to store aliases
struct Alias
{
char name[BUFFER_SIZE];
char value[BUFFER_SIZE];
};
struct Alias aliases[MAX_ALIASES];
int num_aliases = 0;

// Variable to store the exit status of the last command
int last_exit_status = 0;

// Function to add an alias
// ... (same as before, no changes to this function)

// Function to print all aliases
// ... (same as before, no changes to this function)

// Function to print specific aliases
// ... (same as before, no changes to this function)

// Function to perform variable replacement
// ... (same as before, no changes to this function)

// Function to execute a command
int execute_command(char *command)
{
// Replace variables in the command
replace_variables(command);
// ... (rest of the code remains the same)
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
// Check for comments (lines starting with '#')
if (user_input[0] == '#')
continue; // Ignore the entire line as a comment
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
// Check if the command is "alias"
if (strncmp(start, "alias", 5) == 0)
{
// ... (rest of the code remains the same)
}
else
{
// Execute regular commands
execute_command(start);
}
// Move to the next command (if any)
command = strtok(NULL, ";");
}
}
// Free memory and exit
free(user_input);
return 0;
}
