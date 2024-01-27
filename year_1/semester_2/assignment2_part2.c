#include <stdio.h>

int main(void)
{
    // Declare variables
    int sum = 0;

    // Sum loop
    for(int i = 2; i <= 30; i++)
    {
        if(i % 2 == 0) sum += i;
    }

    // Display value to user
    printf("The sum of the even numbers is: %i\n", sum);
}