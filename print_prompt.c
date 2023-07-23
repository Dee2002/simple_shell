#include <stdio.h>
#include "main.h"

/**
* print_prompt - Displays a simple prompt on the standard output,
* indicating the user's position in a simple shell
*
* Return: void
*/

void print_prompt(void)
{
write(1, "simple_shell> ", 14);
}
