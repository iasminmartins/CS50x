#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_liau_index(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int clindex = coleman_liau_index(letters, words, sentences);

    if (clindex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (clindex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", clindex);
    }
}

int count_letters(string text)
{
    int sum = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            sum++;
        }
    }

    return sum;
}

int count_words(string text)
{
    int sum = 0, flag = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
       if (isalpha(text[i]))
       {
            if (flag == 0)
            {
                sum++;
                flag = 1;
            }
       }
       else if (isspace(text[i]))
       {
            flag = 0;
       }
    }
    return sum;
}

int count_sentences(string text)
{
    int sum = 0, flag = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
       if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
       {
            if (flag == 0)
            {
                sum++;
                flag = 1;
            }
       }
       else if (isalpha(text[i]) || isspace(text[i]))
       {
            flag = 0;
       }
    }

    return sum;
}

int coleman_liau_index(int letters, int words, int sentences)
{
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}
