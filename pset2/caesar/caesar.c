#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Ensure exactly one command-line argument is provided
    if (argc != 2)
    {
        printf("Error 1: One command-line argument expected.\n");
        return 1;
    }

    string key = argv[1];

    // Validate that the key contains only digits
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isdigit(key[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert key to integer
    int k = atoi(key);

    // Prompt the user for plaintext
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    // Apply Caesar cipher to each character in plaintext
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", rotate(plaintext[i], k));
    }

    printf("\n");

    return 0;
}

// Rotate a character by n positions
char rotate(char c, int n)
{  
    // If character is uppercase, shift and wrap around using modulo 26
    if (isupper(c))
    {
        return ((c - 'A' + n) % 26) + 'A';
    }
    // If character is lowercase, shift and wrap around using modulo 26
    else if (islower(c))
    {
        return ((c - 'a' + n) % 26) + 'a';
    }
    // If character is not a letter, return it unchanged
    else
    {
        return c;
    }
}
