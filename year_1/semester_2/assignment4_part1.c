#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int is_vowel(char c)
{
    char* vowels = "aeiouAEIOU";
    while(*vowels)
    {
        if(*vowels == c) return 1;
        vowels++;
    }
    return 0;
}

int main(void)
{
    // Define variables
    char string_buffer[BUFFER_SIZE] = {0}; // Zero initialise
    char highlight_buffer[BUFFER_SIZE] = {0}; // Zero initialise
    char has_vowels = 0;

    // Take in a string from the user
    printf("Please enter a string to find all the vowels in: ");
    fgets(string_buffer, BUFFER_SIZE, stdin);

    // Remove the newline character from the end of the string
    int string_length = strlen(string_buffer);
    string_buffer[string_length - 1] = '\0';
    string_length--;

    // Calculate the position of all the vowels
    for(int i = 0; i < string_length; i++)
    {
        if(is_vowel(string_buffer[i]))
        {
            highlight_buffer[i] = '^';
            has_vowels = 1;
        }
        else highlight_buffer[i] = ' ';
    }

    // If the first character is a null byte
    if(!*string_buffer)
        puts("You have not inputted any text");
    // If the program did not find any vowels
    else if(!has_vowels)
        puts("Your string does not contain any vowels");
    // Print out the inputted string and the arrows pointing to them
    else
        printf("These are the vowels in your string:\n%s\n%s\n", string_buffer, highlight_buffer);

    return 0;
}