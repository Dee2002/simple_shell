#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

/**
* main - Shell entry point
*
* Return: 0 on success
*/

/* Function prototypes for functions used in the main function */
void print_prompt(void);
char *get_line(void);
char **parse_line(char *line);
int execute_command(char **argv);
int handle_builtin_command(char **argv);

int main(void)
{
char *line;
char **parsed_line;
int status = 0;
int i;

/* Set the terminal to raw mode */
struct termios old_termios, new_termios;
tcgetattr(0, &old_termios);
new_termios = old_termios;
new_termios.c_lflag &= ~(ICANON | ECHO);
tcsetattr(0, TCSANOW, &new_termios);

while (1)
{
/* Print the prompt */
print_prompt();

/* Get the line from the user */
line = get_line();

/* Check for end of file (Ctrl+D) */
if (!line)
break;

/* Parse the line */
parsed_line = parse_line(line);

/* Execute the command */
status = execute_command(parsed_line);

/* Free the memory */
free(line);
/* Free the dynamically allocated array of strings */
for (i = 0; parsed_line[i] != NULL; i++)
{
free(parsed_line[i]);
}
free(parsed_line);
}

/* Restore the terminal to its original state */
tcsetattr(0, TCSANOW, &old_termios);

return (status);
}
