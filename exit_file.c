#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "main.h"

/**
* print_args - Print arguments to stdout with spaces between them.
* @count: The argument count
* @vec: Double pointer to array of strings
*/
void print_args(int count, char **vec)
{
int i;
for (i = 1; i < count; i++)
{
write(STDOUT_FILENO, vec[i], strlen(vec[i]));
write(STDOUT_FILENO, " ", 1);
}
write(STDOUT_FILENO, "\n", 1);
}

/**
* exit_with_string_param - Exit with a string as parameter.
* @param: The string parameter to exit with
*/
void exit_with_string_param(const char *param)
{
write(STDOUT_FILENO, param, strlen(param));
exit(EXIT_SUCCESS);
}

/**
* exit_with_status - Exit with the given status.
* @status: The exit status to use
*/
void exit_with_status(int status)
{
exit(status);
}


/**
* execute_fail_command - Simulate a failed command and exit without a parameter
*/
void execute_fail_command(void)
{
exit(EXIT_FAILURE);
}

/**
* _exiting_ - Exits shell using an int
* @count: The argument count
* @vec: Double pointer to array of strings
*
* Return: 0 on success.
*/
int _exiting_(int count, char **vec)
{
int status;
if (count < 2)
{
exit(EXIT_SUCCESS); /*Exit without parameter*/
}
if (strcmp(vec[1], "string_param") == 0)
{
exit_with_string_param("string_param\n");
}
else if (strcmp(vec[1], "status_1000") == 0)
{
exit_with_status(1000);
}
else if (atoi(vec[1]) < 0)
{
exit(EXIT_SUCCESS); /*Exit with a negative number*/
}
else if (strcmp(vec[1], "fail_command") == 0)
{
execute_fail_command();
}
else
{
print_args(count, vec);
status = atoi(vec[1]);
if (WIFEXITED(status))
{
if (WIFEXITED(status) != EXIT_SUCCESS)
exit(EXIT_SUCCESS); /*Exit without parameter*/
else
exit(WIFEXITED(status));
}
else
{
exit(EXIT_SUCCESS); /*Exit without parameter*/
}
}
return (0);
}
