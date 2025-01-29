// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // The word stored in the node
    struct node *next; // Pointer to the next node (for collision handling)
} node;

const unsigned int N = 143107; // Number of buckets in hash table (chosen to reduce collisions)
#define HASH_MULTIPLIER 31 // Multiplier for hash function to reduce collisions

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to find bucket
    node *ptr = table[hash(word)];

    // Traverse linked list at hashed index
    while (ptr != NULL)
    {
        // Compare word case-insensitively
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true; // Word found
        }
        ptr = ptr->next;
    }
    return false; // Word not found
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    unsigned long hash_value = 0;

    // Iterate over each character in the word to compute hash value
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Ensure case insensitivity (tolower) and reduce collisions (prime number)
        hash_value = (hash_value * HASH_MULTIPLIER + tolower(word[i])) % N;
    }

    return hash_value % N; // Ensure table bounds
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    // Initialize hash table with NULL values
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read each word in file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        // Create new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Could not allocate memory.\n");
            fclose(source);
            return false;
        }

        // Add word to hash table
        strcpy(new_node->word, word);
        unsigned int index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    // Traverse bucket
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            count++;
            ptr = ptr->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free each node in the hash table
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }

    return true;
}
