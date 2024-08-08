#include <cs50.h>
#include <stdio.h>

void print_spaces(int spaces);
void print_row(int length);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int j = 0; j < height; j++)
    {
        print_spaces(height - j - 1);
        print_row(j + 1);
        printf("  ");
        print_row(j + 1);
        printf("\n");
    }
}

void print_spaces(int spaces)
{
    for (int k = spaces; k > 0; k--)
    {
        printf(" ");
    }
}

void print_row(int length) // sempre definir tipo de variavel na função
{
    for (int i = 0; i < length; i++)
    {
        printf("#");
    }
}
