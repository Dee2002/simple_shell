#include "main.h"

/**
* interpret - Runs a unix command-line interpreter.
* @cmd_input: The user input.
*
* Return: 0
*/
int interpret(void)
{
size_t buffer_size = 0;
int run = 1;
char *user_input = NULL;
while (run)
{
write(STDOUT_FILENO, "simple_shell > ", strlen("simple_shell > "));
fflush(stdout);
if (getline(&user_input, &buffer_size, stdin) == -1)
{
perror("An error has occurred\n");
exit(EXIT_FAILURE);
}
if (strcmp(user_input, "exit\n") == 0)
{
run = 0;
}
else
{
/*Execute the entered command*/
if (execute_cmd(user_input) == -1)
{
perror("Error executing command\n");
}
}
/* Free the memory allocated for user_input*/
free(user_input);
user_input = NULL;
}
free(user_input);
return (0);
}

/**
* execute_cmd - Executes the entered command using execve.
* @command: The command to execute.
*
* Return: 0 on success, -1 on failure.
*/
int execute_cmd(char *command)
{
pid_t pid;
char *args[64];
int arg_count = 0;

char *token = strtok(command, " \t\n");
while (token != NULL && arg_count < 63)
{
args[arg_count] = token;
arg_count++;
token = strtok(NULL, " \t\n");
}
args[arg_count] = NULL; /* Null-terminate the argument list*/
/*Fork to create a new process*/
pid = fork();
if (pid == -1)
{
perror("Fork failed\n");
return (-1);
}
else if (pid == 0)
{
/*Child process - execute the command*/
if (execve(args[0], args, NULL) == -1)
{
perror("Command execution failed\n");
return (-1);
}
}
else
{
/*Parent process - wait for the child to complete*/
wait(NULL);
}
return (0);
}
