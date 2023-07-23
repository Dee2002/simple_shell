/*
 * Simple Shell 1.0 +
 * Created by Julius Kaboyo in collaboration with Delsa Marasha
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define MAX_ALIASES 50

// Data structure to store aliases
struct Alias
{
    char name[BUFFER_SIZE];
    char value[BUFFER_SIZE];
};

struct Alias aliases[MAX_ALIASES];
int num_aliases = 0;

// Variable to store the exit status of the last command
int last_exit_status = 0;

// Function to add an alias
// ... (same as before, no changes to this function)

// Function to print all aliases
// ... (same as before, no changes to this function)

// Function to print specific aliases
// ... (same as before, no changes to this function)

// Function to perform variable replacement
// ... (same as before, no changes to this function)

// Function to execute a command
int execute_command(char *command)
{
    // Replace variables in the command
    replace_variables(command);

    // ... (rest of the code remains the same)
}
int main(int argc, char *argv[])
{
    if (argc > 1)
{
        // Read commands from the file
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
{
            perror("Error opening file");
            return EXIT_FAILURE;
}
char line[BUFFER_SIZE];
while (fgets(line, BUFFER_SIZE, file) != NULL)
{
            // Remove the newline character at the end of the line
            line[strcspn(line, "\n")] = 0;

            // Execute the command from the file
            execute_command(line);
}
        fclose(file);
        return EXIT_SUCCESS;
}
    // Interactive mode (same as before)
    char *user_input;
    size_t bufsize = BUFFER_SIZE;
    user_input = (char *)malloc(bufsize * sizeof(char));
    while (1)
{
        printf("MyShell$ ");
        // Read user input
        if (getline(&user_input, &bufsize, stdin) == -1)
            break; // Handle "end of file" (Ctrl+D) condition
        // ... (rest of the code remains the same)
}
    // Free memory and exit
    free(user_input);
    return 0;
}
