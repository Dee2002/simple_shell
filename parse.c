#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

/**
* append_token - Appends a parsed token to
* the tokens array and updates the position.
*
* @tokens: Pointer to the array of tokens.
* @position: Pointer to the current position in the tokens array.
* @token_start: Pointer to the start of the token to be appended.
*/

void append_token(char **tokens, int *position, const char *token_start)
{
if (*position >= TOKEN_SIZE)
{
perror("Too many tokens");
_exit(EXIT_FAILURE);
}

tokens[*position] = strdup(token_start);
if (!tokens[*position])
{
perror("strdup");
_exit(EXIT_FAILURE);
}

(*position)++;
}
/**
* parse_line - Parses a line of input into individual command arguments.
*
* @line: The line to be parsed.
*
* Return: Array of pointers to individual command arguments (tokens).
*/
char **parse_line(char *line)
{
const char *special_chars = "\"'`\\*&#";
char **tokens = NULL;
int bufsize = TOKEN_SIZE;
int position = 0;
int in_quotes = 0;
char *token_start = line;
tokens = (char **)malloc(bufsize * sizeof(char *));
if (!tokens)
{
perror("malloc");
_exit(EXIT_FAILURE);
}
while (*line)
{
if (isspace(*line) && !in_quotes)
{
*line = '\0';
append_token(tokens, &position, token_start);
token_start = line + 1;
}
else if (strchr(special_chars, *line))
{
if (!in_quotes)
in_quotes = 1;
else
{
in_quotes = 0;
*line = '\0';
append_token(tokens, &position, token_start);
token_start = line + 1;
}
}
line++;
}
if (token_start != line)
append_token(tokens, &position, token_start);
tokens[position] = NULL;
return (tokens);
}

/**
* free_argv - Frees the memory allocated for an array of strings.
*
* @argv: The array of strings to be freed.
*/
void free_argv(char **argv)
{
char **ptr;
for (ptr = argv; *ptr != NULL; ptr++)
{
free(*ptr);
}
free(argv);
}
