#include <stdio.h>
#include <stdbool.h>

#define SENTINEL 9999

int main(void)
{
    // Define varibles that will be used throughout the program
    float sum = 0.0f;
    int buffer = 0;
    int number_count = 0;

    // Input loop
    while(true)
    {
        // Ask user for input
        printf("Please enter a number to get the average of: ");
        scanf("%d", &buffer);
        // If sentinel provided exit loop
        if(buffer == SENTINEL) break;
        // Otherwise add number to the sum and incrase number_count
        sum += buffer;
        number_count++;
    }

    // Check that number_count is not 0 as to not devide by 0
    if(number_count == 0) number_count = 1;

    // Calculate average
    sum /= number_count;

    // Show average to user
    printf("The average of the provided numbers is: %.2f\n", sum);
}
