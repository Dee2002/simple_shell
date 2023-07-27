#include <unistd.h> /*Header for write function*/
#include <stdio.h>

/**
 * Calculate the factorial of a given number using recursion.
 * Parameters:
 * @n n: The number for which the factorial is calculated.
 * @factorial  Returns; The factorial of the given number.
*/
unsigned int factorial(unsigned int n);
/*
 * @main Entry point of the program. Reads a positive integer from the user,
   calculates its factorial, and displays the result.
*/
int main(void)
{
unsigned int num, result;
char message[50];

/**
 * Using 'write' to display the message
 * write(STDOUT_FILENO, "Enter a positive integer: ", 26);
 * Using 'read' to receive user input
 * read(STDIN_FILENO, message, sizeof(message));
 * sscanf(message, "%u", &num);
 */
 /*
  * Calculate the factorial of the entered number
 */
result = factorial(num);
/**
 *  Using 'write' to display the result
 * write(STDOUT_FILENO, "Factorial of ", 13);
 * sprintf(message, "%u", num);
 * write(STDOUT_FILENO, message, strlen(message));
 * write(STDOUT_FILENO, " is ", 4);
 * sprintf(message, "%u", result);
 * write(STDOUT_FILENO, message, strlen(message));
 * write(STDOUT_FILENO, "\n", 1);
 */
return (0);
}
/* Function to calculate the factorial of a given number using recursion. */
unsigned int factorial(unsigned int n)
{
/* Base case: factorial of 0 is 1 */
if (n == 0)
{
return (1);
}
else
{
/* Recursive call to calculate factorial */
return (n * factorial(n - 1));
}
}
