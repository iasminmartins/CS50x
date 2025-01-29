#include <cs50.h>
#include <stdio.h>

void print_spaces(int spaces);
void print_row(int length);

int main(void)
{
    int height;
    // Prompt the user for a height between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

     // Loop through each row to print the pyramid
    for (int j = 0; j < height; j++)
    {
        print_spaces(height - j - 1); // Print spaces
        print_row(j + 1);             // Print the first half of the row
        printf("  ");                 // Space between halves
        print_row(j + 1);             // Print the second half of the row
        printf("\n");                 
    }
}

// Print spaces in each row
void print_spaces(int spaces)
{
    for (int k = spaces; k > 0; k--)
    {
        printf(" ");
    }
}

// Print hash symbols ('#') for the row
void print_row(int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("#");
    }
}
