#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string s);
int count_sentences(string s);
int count_words(string s);

int main(void)
{
    string text;

    // Prompt user for a non-empty string
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) < 2);

    // Count the letters, words and sentences in text
    int letters = count_letters(text);
    int sentences = count_sentences(text);
    int words = count_words(text);

    // Calculate letters & sentences amount per 100 words
    // Casting letters & sentences as a double in case of decimals in calc | THANK YOU CS50 duck
    double calc_letters = ((double) letters / words) * 100;
    double calc_sentences = ((double) sentences / words) * 100;

    // Compute the Coleman-Liau Index & round to nearest int
    int cole_index = round(0.0588 * calc_letters - 0.296 * calc_sentences - 15.8);

    // Print grade level

    if (cole_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cole_index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", cole_index);
    }

    return 0;
}

int count_letters(string s)
{
    int letter_count = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Check if indexed char is alphabetical & add to total
        if (isalpha(s[i]))
        {
            letter_count++;
        }
    }

    return letter_count;
}

int count_sentences(string s)
{
    int sentence_count = 0;

    // Check if indexed char is .!?
    // ispunct ctype function is not viable as it returns more than these three
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentence_count++;
        }
    }

    return sentence_count;
}

int count_words(string s)
{
    // Initialize at 1 to account for first word
    int word_count = 1;

    // Check if indexed char is a space indicating a new word
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isblank(s[i]))
        {
            word_count++;
        }
    }

    return word_count;
}
