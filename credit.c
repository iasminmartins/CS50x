#include <cs50.h>
#include <stdio.h>

int luhns(long number);
void kind_of_card(long number);

int main(void)
{
    long card_number = get_long("Number: ");
    int sum = luhns(card_number);
    sum %= 10;
    if (sum == 0)
    {
        kind_of_card(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

int luhns(long number)
{
    int counter = 0, sum = 0, sum2 = 0;
    while (number > 0)
    {
        // Para separar o ultimo digito
        int last_digit = number % 10;
        // Para excluir o ultimo digito
        number /= 10;
        if (counter == 1)
        {
            int doubling;
            doubling = last_digit * 2;
            if (doubling > 9)
            {
                sum = sum + 1 + (doubling % 10);
            }
            else
            {
                sum = sum + doubling;
            }
            counter = 0;
        }
        else
        {
            sum2 = sum2 + last_digit;
            counter++;
        }
    }
    sum += sum2;
    return sum;
}

void kind_of_card(long number)
{
    int counter = 0;
    long num;
    num = number;
    while (num > 0)
    {
        int last_digit = num % 10;
        num /= 10;
        counter++;
    }
    int first_digit;
    num = number;
    while (num >= 10)
    {
        num /= 10;
    }
    first_digit = num;
    num = number;
    int first_two_digits;
    while (num >= 100)
    {
        num /= 10;
    }

    first_two_digits = num;

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
