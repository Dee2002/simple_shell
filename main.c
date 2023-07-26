#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * main - Shell entry point.
 *
 * Return: 0 always.
 */

int main(void)
{
char *line;
char **parsed_line;
int status = 0;

while (1)
{
print_prompt();
line = get_line();

if (!line)
break;

parsed_line = parse_line(line);

status = execute_command(parsed_line);

free(line);
free_argv(parsed_line);
}

return (status);
}
