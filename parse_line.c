#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
* parse_line - Parses a given input line into an array of tokens.
*
* This function tokenizes the input line using spaces as delimiters
* and stores each token in an array (argv).
* The number of tokens (arguments) in the line is
* returned as the function's result (argc).
*
* @line: The input line to be parsed.
*
* Return: The number of tokens (arguments) found in the input line.
*/

int parse_line(char *line)
{
char **argv = NULL;
int argc = 0;
char *token;

/*Tokenize the line*/
token = strtok(line, " ");
while (token != NULL)
{
argv = realloc(argv, sizeof(char *) * (argc + 1));
argv[argc] = token;
argc++;
token = strtok(NULL, " ");
}

/*Return the parsed line*/
return (argc);
}
