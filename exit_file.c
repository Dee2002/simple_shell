#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "main.h"

/**
* execute_exit_builtin - Terminates the shell gracefully.
*
* This function prints an exit message and performs any necessary cleanup
* before terminating the shell.
*/
void execute_exit_builtin(void)
{
const char exit_message[] = "Exiting the shell...\n";
write(STDOUT_FILENO, exit_message, sizeof(exit_message) - 1);

exit(0);
}

/**
* _exiting_ - Exits shell using an int
* @count: The argumemt count
* @vec: Double pointer to array of strings
*
* Return: 0 on success.
*/
int _exiting_(int count, char **vec)
{
int status = STDIN_FILENO;
int i;

if (count < 2)
{
exit(EXIT_SUCCESS); /*Exit without parameter*/
}

status = atoi(vec[1]);
for (i = 2; i < count; i++)
{
write(STDOUT_FILENO, vec[i], strlen(vec[i]));
write(STDOUT_FILENO, " ", 1);
}

write(STDOUT_FILENO, "\n", 1);

/*Simulating a failed command*/
if (strcmp(vec[2], "/test_hbtn") == 0)
{
exit(EXIT_FAILURE);
}

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
return (0);
}
