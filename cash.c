#include <cs50.h>
#include <stdio.h>

int calculate_coins(int cents);

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 1);

    int sum = calculate_coins(change);
    printf("%i\n", sum);
}

int calculate_coins(int cents)
{
    int quarters = cents / 25;
    int remainder = cents % 25;
    int dimes = remainder / 10;
    remainder = remainder % 10;
    int nickles = remainder / 5;
    remainder = remainder % 5;
    int pennies = remainder;
    int total = quarters + dimes + nickles + pennies;

    return total;
}
