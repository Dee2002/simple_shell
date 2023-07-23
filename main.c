#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "main.h"
#include <termios.h>

/**
 * main - Shell entry point
 *
 * Return: 0 on success, non-zero on failure
 */

/* Function declarations */
void print_prompt(void);
char *get_line(void);
int parse_line(char *line);
int execute_command(char **argv);
int handle_builtin_command(char **argv);

int main(int argc, char *argv[])
{
char *line;
char **argv;
int status;

/*Set the terminal to raw mode*/
struct termios old_termios, new_termios;
tcgetattr(0, &old_termios);
new_termios = old_termios;
new_termios.c_lflag &= ~(ICANON | ECHO);
tcsetattr(0, TCSANOW, &new_termios);

while (1)
{
/*Print the prompt*/
print_prompt();

/*Get the line from the user*/
line = get_line();

/*Parse the line*/
argv = (char **)parse_line(line);

/* Execute the command*/
status = execute_command(argv);

/*Free the memory*/
free(line);
free(argv);
}

/*Restore the terminal to its original state*/
tcsetattr(0, TCSANOW, &old_termios);

return (0);
}

