#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h> 

// Scrabble points for each alphabet letter
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute scores for both players
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print winner or tie result
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Compute score for a word
int compute_score(string word)
{
    int score = 0;

    // Iterate over each character in word
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // Add points for uppercase letters
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        // Add points for lowercase letters
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }

    return score;
}
