#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
* print_prompt - Displays the prompt symbol ('$') to the user.
*/
void print_prompt(void)
{
write(STDOUT_FILENO, "$ ", 2);
}
