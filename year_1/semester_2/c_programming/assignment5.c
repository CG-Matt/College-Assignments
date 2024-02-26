#include <stdio.h>

#define NO_OF_MONTHS 12

// Displays to the user how to use this program
void DisplayInstructions()
{
    puts("This program takes the sales for each month for 2 years from the user");
    puts("It then calculates during which months the sales were higher than the previous year.");
    puts("Finally, it shows the user for how many months sales were higher in year 2 compared to year 1.");
}

void GetSales(int year, float* buffer)
{
    // Define the names of months for printing
    char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    // Fill the buffer with values from the user
    for(int i = 0; i < NO_OF_MONTHS; i++)
    {
        printf("Please input the sales for %s of year %i: ", months[i], year);
        scanf("%f", &buffer[i]);
    }
}

int HigherSales(float* previous_year_sales, float* current_year_sales)
{
    // Local counter variable which will be returned later
    int counter = 0;
    // Main loop which compares the sales of each month and increments counter is they are greater.
    for(int i = 0; i < NO_OF_MONTHS; i++)
        counter += current_year_sales[i] > previous_year_sales[i];
    return counter;
}

void DisplayAnswer(int month_count)
{
    printf("The sales have been higher for the second year for %i months!\n", month_count);
}

int main(void)
{

    // Declare variables
    float previous_year_sales[NO_OF_MONTHS];
    float current_year_sales[NO_OF_MONTHS];

    // Display the instruction for this program
    DisplayInstructions();

    // Get the sales for year 1 and year 2 from the user
    GetSales(1, previous_year_sales);
    GetSales(2, current_year_sales);

    // Get the number of months that sales were higher from the previous year
    int months_count = HigherSales(previous_year_sales, current_year_sales);

    // Display the number of months that sales were higher in year 2 compared to year 1
    DisplayAnswer(months_count);

    return 0;
}