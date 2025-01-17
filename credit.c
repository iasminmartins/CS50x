#include <cs50.h>
#include <stdio.h>

int luhns(long number);
void kind_of_card(long number);

int main(void)
{
    long card_number = get_long("Number: ");    // Prompt for card number
    int sum = luhns(card_number);    // Get sum for Luhn's algorithm
    sum %= 10;    // Get last digit    
    if (sum == 0)    // If valid
    {
        kind_of_card(card_number);    // Identify card type
    }
    else // If invalid
    {
        printf("INVALID\n");
    }
}

// Luhn's algorithm
int luhns(long number)
{
    int counter = 0, sum = 0, sum2 = 0;
    while (number > 0)
    {
        int last_digit = number % 10;    // Get last digit
        number /= 10;    // Remove last digit
        if (counter == 1)    // For every second digit (from second to last)
        {
            int doubling;
            doubling = last_digit * 2;
            if (doubling > 9)
            {
                sum = sum + 1 + (doubling % 10);    // Add sum of digits of doubled value
            }
            else
            {
                sum = sum + doubling;    // Add double value
            }
            counter = 0;
        }
        else    // For other digits
        {
            sum2 = sum2 + last_digit;    // Add digit to sum2
            counter++;
        }
    }
    sum += sum2;    // Final sum
    return sum;
}

// Determine type of card based on first digits and length
void kind_of_card(long number)
{
    int counter = 0;
    long num = number;

    // Count number of digits
    while (num > 0)
    {
        int last_digit = num % 10;
        num /= 10;
        counter++;
    }
    
    int first_digit;
    num = number;

    // Remove first digit
    while (num >= 10)
    {
        num /= 10;
    }
    first_digit = num;
    
    num = number;
    int first_two_digits;

    // Remove first two digits
    while (num >= 100)
    {
        num /= 10;
    }

    first_two_digits = num;

    // Check card type
    if ((first_digit == 4 && counter == 13) || (first_digit == 4 && counter == 16))
    {
        printf("VISA\n");
    }
    else if ((first_two_digits == 34 && counter == 15) || (first_two_digits == 37 && counter == 15))
    {
        printf("AMEX\n");
    }
    else if (first_two_digits >= 51 && first_two_digits <= 55 && counter == 16)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
