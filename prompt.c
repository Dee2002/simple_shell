#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
* print_prompt - displays the prompt symbol ('cisfun$') to the user
*/

void print_prompt(void)
{
write(STDOUT_FILENO, "cisfun$", 2);
}
