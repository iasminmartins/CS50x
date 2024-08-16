#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error 1: One command-line argument expected.\n");
        return 1;
    }

    string key = argv[1];
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isdigit(key[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(key);
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", rotate(plaintext[i], k));
    }

    printf("\n");

    return 0;
}

char rotate(char c, int n)
{
    // If true, it calculates the new character by shifting c by n positions, wrapping around using
    // modulo 26, and then converting back to a character

    if (isupper(c))
    {
        return ((c - 'A' + n) % 26) + 'A';
    }
    else if (islower(c))
    {
        return ((c - 'a' + n) % 26) + 'a';
    }
    else
    {
        return c;
    }
}
