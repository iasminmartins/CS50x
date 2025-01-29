#include <cs50.h>
#include <stdio.h>

int calculate_coins(int cents);

int main(void)
{
    int change;
    // Prompt the user for a positive change value
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 1);

    int sum = calculate_coins(change);
    printf("%i\n", sum);
}

// Calculate the total number of coins required for the change
int calculate_coins(int cents)
{
    int quarters = cents / 25;    // Calculate number of quarters
    int remainder = cents % 25;    // Remainder
    int dimes = remainder / 10;    // Calculate number of dimes
    remainder = remainder % 10;
    int nickles = remainder / 5;    // Calculate number of nickles
    remainder = remainder % 5;
    int pennies = remainder;    // Remainder is the number of pennies
    
    int total = quarters + dimes + nickles + pennies;

    return total;
}
