#include <cs50.h>
#include <stdio.h>

void print_spaces(int spaces);
void print_row(int length);

int main(void)
{
    int height;
    // Prompt user for a positive integer
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // Print each row of the pyramid
    for (int j = 0; j < height; j++)
    {
        print_spaces(height - j - 1); // Print spaces
        print_row(j + 1);             // Print hashes
    }
}

// Print given number of spaces
void print_spaces(int spaces)
{
    for (int k = spaces; k > 0; k--)
    {
        printf(" ");
    }
}

// Print row of hashes of given lenght
void print_row(int length) 
{
    for (int i = 0; i < length; i++)
    {
        printf("#");
    }
    printf("\n");
}
