#include <stdio.h>

#define INPUT_SIZE 15

int main(void)
{
    // Declaring variables
    int inputs[INPUT_SIZE];
    float average = 0;

    /*
        This loop will take user input,
        and simultaniously get the average of the array
    */
    for(int i = 0; i < INPUT_SIZE; i++)
    {
        printf("Please input value no.%i: ", i + 1);
        scanf("%i", &inputs[i]);
        average += inputs[i];
    }

    /*
        Devide by the number of values to get the average
        Input size is multiplied by 1.0f to ensure the result is a float
    */
    average /= (INPUT_SIZE * 1.0f);

    // Display the numbers that are less than half the everage calculated
    for(int i = 0; i < INPUT_SIZE; i++)
    {
        if(inputs[i] < average / 2)
            printf("The value of %i, in position %i, is less than half of the average (%.2f).\n", inputs[i], i + 1, average);
    }

    return 0;
}