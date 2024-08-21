#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool unique(string key);
char encrypt(char c, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if(strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }

    }

    if (unique(key) == false)
    {
          printf("Key is not unique.\n");
          return 1;
    }

    string plaintext = get_string("Plaintext: ");
    printf ("Ciphertext: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", encrypt(plaintext[i], key));
    }

    printf("\n");

    return 0;
}

bool unique(string key)
{
    bool lower_used[26] = {false};
    bool upper_used[26] = {false};

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        char c = key[i];

        if (c >= 'a' && c <= 'z')
        {
            int index = c - 'a';

            if(lower_used[index])
            {
                return false;
            }

            lower_used[index] = true;
        }

        else if ( c >= 'A' && c <= 'Z')
        {
            int index = c - 'A';

            if(upper_used[index])
            {
                return false;
            }
            upper_used[index] = true;
        }
    }
    return true;
}

char encrypt(char c, string key)
{

    if (isupper(c))
    {
        return key[c - 'A'];
    }
    else if (islower(c))
    {
        return key[c - 'a'];
    }
    else
    {
        return c;
    }
}
