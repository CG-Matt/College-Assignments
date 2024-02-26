#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(void)
{
    // Define variables
    char input_buffer[BUFFER_SIZE];

    // Take in a string from the user
    printf("Please enter a string to reverse: ");
    fgets(input_buffer, BUFFER_SIZE, stdin);

    // Get the length of the inputted string
    int input_length = strlen(input_buffer);

    // Print out the reversed string
    for(int i = input_length; i > 0; i--)
        if(isalpha(input_buffer[i - 1])) putc(input_buffer[i - 1], stdout);
    putc('\n', stdout);

    return 0;
}