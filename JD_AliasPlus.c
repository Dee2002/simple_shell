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
// Function to execute a command
int execute_command(char *command)
{
// ... (same as before, no changes to this function)
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
// Remove the "alias" keyword
start += 5;
// Remove leading and trailing spaces from the command
while (*start == ' ')
start++;
end = command + strlen(command) - 1;
while (*end == ' ')
end--;
*(end + 1) = '\0';
// Tokenize the arguments based on spaces
char *args[BUFFER_SIZE];
args[0] = strtok(start, " ");
int num_args = 1;
while ((args[num_args] = strtok(NULL, " ")) != NULL)
{
num_args++;
}
// Handle different alias cases
if (num_args == 0)
{
// Print all aliases
print_aliases();
}
else if (num_args == 1)
{
// Print specific aliases
print_specific_aliases(args);
}
else
{
// Define new aliases
for (int i = 0; i < num_args; i++)
{
char *equal_sign = strchr(args[i], '=');
if (equal_sign != NULL)
{
// Split the argument into name and value
*equal_sign = '\0';
add_alias(args[i], equal_sign + 1);
}
}
}
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
