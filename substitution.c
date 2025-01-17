#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool unique(string key);
char encrypt(char c, string key);

int main(int argc, string argv[])
{
    // Check if the correct number of arguments is provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    // Check if the key has exactly 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if the key contains only alphabetic characters
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Check if the key has all unique characters
    if (!unique(key))
    {
        printf("Key is not unique.\n");
        return 1;
    }

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    // Encrypt each character in the plaintext
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", encrypt(plaintext[i], key));
    }

    printf("\n");

    return 0;
}

// Function to check if key has all unique characters
bool unique(string key)
{
    bool lower_used[26] = {false};
    bool upper_used[26] = {false};

    // Check each character in key
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        char c = key[i];
        int index;

        if (islower(c))
        {
            index = c - 'a';

            // If character has been used before, return false
            if (lower_used[index])
            {
                return false;
            }

            lower_used[index] = true;
        }

        else if (isupper(c))
        {
            index = c - 'A';

            // If the character has been used before, return false
            if (upper_used[index])
            {
                return false;
            }
            upper_used[index] = true;
        }
    }
    return true;
}

// Function to encrypt a character using key
char encrypt(char c, string key)
{
    if (isupper(c))
    {
        // Convert to uppercase and map to the corresponding character in key
        return toupper(key[c - 'A']);
    }
    else if (islower(c))
    {
        // Convert to lowercase and map to the corresponding character in key
        return tolower(key[c - 'a']);
    }
    else
    {
        // If not a letter, return character unchanged
        return c;
    }
}
