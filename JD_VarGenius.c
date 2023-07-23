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
// Function to add an alias
void add_alias(char *name, char *value)
{
if (num_aliases >= MAX_ALIASES)
{
fprintf(stderr, "MyShell: Maximum number of aliases reached.\n");
return;
}
// Check if the alias already exists
for (int i = 0; i < num_aliases; i++)
{
if (strcmp(aliases[i].name, name) == 0)
{
strcpy(aliases[i].value, value);
return;
}
}
// Add the new alias
strcpy(aliases[num_aliases].name, name);
strcpy(aliases[num_aliases].value, value);
num_aliases++;
}
// Function to print all aliases
void print_aliases()
{
for (int i = 0; i < num_aliases; i++)
{
printf("%s='%s'\n", aliases[i].name, aliases[i].value);
}
}
// Function to print specific aliases
void print_specific_aliases(char *names[])
{
for (int i = 0; i < num_aliases; i++)
{
for (int j = 0; names[j] != NULL; j++)
{
if (strcmp(aliases[i].name, names[j]) == 0)
{
printf("%s='%s'\n", aliases[i].name, aliases[i].value);
}
}
}
}
// Function to perform variable replacement
void replace_variables(char *command)
{
char result[BUFFER_SIZE] = "";
char *start = command;
char *end;
char variable[BUFFER_SIZE] = "";
while (*start != '\0')
{
// Look for a '$' sign
if (*start == '$')
{
start++;
if (*start == '?')
{
// Replace with the exit status of the last command
sprintf(variable, "%d", WEXITSTATUS(last_exit_status));
start++;
}
else if (*start == '$')
{
// Replace with the process ID of the shell
sprintf(variable, "%d", getpid());
start++;
}
else
{
// Look for the end of the variable name
end = start;
while (*end != '\0' && (*end == '_' || (*end >= 'a' && *end <= 'z') || (*end >= 'A' && *end <= 'Z') || (*end >= '0' && *end <= '9')))
{
end++;
}
// Extract the variable name
strncpy(variable, start, end - start);
variable[end - start] = '\0';
// Look up the variable value in aliases or environment variables
int found = 0;
for (int i = 0; i < num_aliases; i++)
{
if (strcmp(aliases[i].name, variable) == 0)
{
strcat(result, aliases[i].value);
found = 1;
break;
}
}
if (!found)
{
char *env_value = getenv(variable);
if (env_value != NULL)
{
strcat(result, env_value);
}
else
{
// Variable not found, use an empty string
strcat(result, "");
}
}
start = end;
}
}
else
{
// Copy the current character to the result
char c[2] = { *start, '\0' };
strcat(result, c);
start++;
}
}
// Copy the result back to the original command
strcpy(command, result);
}
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
