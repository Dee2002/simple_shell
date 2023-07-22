#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <termios.h>

extern char **environ;

int main(int argc, char *argv[]);
void print_prompt(void);
char *get_line(void);
int parse_line(char *line);
int execute_command(char **argv);
int handle_builtin_command(char **argv);
int waitpid(pid_t pid, int *status, int option);
void print_env(void);

#endif
