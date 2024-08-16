#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//void encrypt(int key, string text);
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
        else
        {
            return 0;
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
