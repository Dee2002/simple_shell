#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define MAX_ALIASES 50

/**
* Simple Shell with Alias Functionality
*
* This program implements a simple shell with alias functionality. It allows users to define and use aliases
* for commands. The shell supports the following built-in commands:
*
*   - void add_alias(const char *name, const char *value);
*     Description: Adds or updates an alias.
*     Parameters:
*       - const char *name: The name of the alias.
*       - const char *value: The value or command associated with the alias.
*
*   - void print_aliases();
*     Description: Prints all defined aliases.
*     No parameters.
*
*   - void print_specific_aliases(const char *names[]);
*     Description: Prints specific aliases based on the provided names.
*     Parameters:
*       - const char *names[]: An array of strings containing the names of aliases to print.
*
* - int execute_command(char *command);
*     Description: Executes a command in the shell.
*     Parameters:
*       - char *command: The command to be executed.
*     Return Value: Returns an integer representing the exit status of the command execution.
*                   The return value may vary depending on the executed command or any encountered errors.
*/

/* Data structure to store aliases*/
struct Alias
{
char name[BUFFER_SIZE];
char value[BUFFER_SIZE];
};

struct Alias aliases[MAX_ALIASES];
int num_aliases = 0;

/*Function to write a string to stdout*/
ssize_t write_string(int fd, const char *str)
{
size_t len = strlen(str);
return write(fd, str, len);
}

/*Function to copy strings*/
char *str_copy(char *dest, const char *src, size_t n)
{
size_t i = 0;
while (i < n - 1 && src[i] != '\0')
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}

/*Function to compare strings*/
int str_compare(const char *str1, const char *str2)
{
while (*str1 && (*str1 == *str2))
{
str1++;
str2++;
}
return (int)(unsigned char)(*str1) - (int)(unsigned char)(*str2);
}

/*Function to add an alias*/
void add_alias(const char *name, const char *value)
{
if (num_aliases >= MAX_ALIASES)
{
const char error_msg[] = "MyShell: Maximum number of aliases reached.\n";
write_string(STDERR_FILENO, error_msg);
return;
}

/*Check if the alias already exists*/
for (int i = 0; i < num_aliases; i++)
{
if (str_compare(aliases[i].name, name) == 0)
{
str_copy(aliases[i].value, value, BUFFER_SIZE);
return;
}
}

/*Function to print all aliases*/
void print_aliases()
{
for (int i = 0; i < num_aliases; i++)
{
char buffer[BUFFER_SIZE];
int len = str_copy(buffer, aliases[i].name, BUFFER_SIZE);
buffer[len] = '=';
len++;
str_copy(buffer + len, aliases[i].value, BUFFER_SIZE - len);
len += strlen(aliases[i].value);
buffer[len] = '\n';
len++;

write_string(STDOUT_FILENO, buffer);
}
}

/*Function to print specific aliases*/
void print_specific_aliases(const char *names[])
{
for (int i = 0; i < num_aliases; i++)
{
for (int j = 0; names[j] != NULL; j++)
{
if (str_compare(aliases[i].name, names[j]) == 0)
{
char buffer[BUFFER_SIZE];
int len = str_copy(buffer, aliases[i].name, BUFFER_SIZE);
buffer[len] = '=';
len++;
str_copy(buffer + len, aliases[i].value, BUFFER_SIZE - len);
len += strlen(aliases[i].value);
buffer[len] = '\n';
len++;

write_string(STDOUT_FILENO, buffer);
}
}
}
}
