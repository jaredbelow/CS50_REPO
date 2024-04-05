#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int error_check(int c, string file, string key);

int main(int argc, string argv[])
{
    // Helper function for error check
    if (error_check(argc, argv[0], argv[1]) != 0)
    {
        return 1;
    }

    // Convert key to uppercase for easier indexing
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        argv[1][i] = toupper(argv[1][i]);
    }

    // Prompt user for a valid string to be converted
    string text;

    do
    {
        text = get_string("plaintext: ");
    }
    while (strlen(text) < 1);

    // Convert to cipher text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Check for uppercase chars
        if (isupper(text[i]) != 0)
        {
            // Convert for indexing into key array
            text[i] -= 65;

            // Replace with key char
            text[i] = argv[1][(int) text[i]];
        }
        else if (islower(text[i]) != 0)
        {
            // Convert for indexing into key array
            text[(int) i] -= 97;

            // Replace with key char
            text[i] = argv[1][(int) text[i]];

            // Convert to lowercase
            text[i] = tolower((int) text[i]);
        }
    }

    // Print cipher text
    printf("ciphertext: %s\n", text);

    return 0;
}

int error_check(int c, string file, string key)
{
    // Return error if arguemnt count is not what expected
    if (c != 2)
    {
        printf("Usage: %s KEY\n", file);
        return 1;
    }

    // Return error if key is less than 26 chars
    if (strlen(key) < 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // Return error if key contains numbers, or punctuation
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isdigit(key[i]) != 0 || ispunct(key[i]) != 0)
        {
            printf("Key must only contain alphabetical characters\n");
            return 1;
        }
    }

    // Return error if key contains repeating chars
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters\n");
                return 1;
            }
        }
    }

    return 0;
}
