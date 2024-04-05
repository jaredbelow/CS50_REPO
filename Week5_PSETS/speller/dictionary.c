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
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Global counter for loaded dictionary words
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Initalize hashed value of word
    // Modulo by N for indexing
    int hashedStr = hash(word) % N;

    // Check if node is NULL
    if (table[hashedStr] != NULL)
    {
        // Check if word at hashed index in table equals word
        if (strcasecmp(table[hashedStr]->word, word) == 0)
        {
            return true;
        }

        // Check for chained words at hashed index in table
        if (table[hashedStr]->next != NULL)
        {
            // Initalize placeholder pointer
            node *currP = table[hashedStr]->next;

            // Check word at current pointer
            if (strcasecmp(currP->word, word) == 0)
            {
                return true;
            }

            // Loop over linked list
            while (currP != NULL)
            {
                // Check if word at current pointer equals word
                if (strcasecmp(currP->word, word) == 0)
                {
                    return true;
                }

                // Point to next node
                currP = currP->next;
            }
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Implementation inspired by DBJ2 by Daniel J. Bernstein
    // Hashed function returns value of sum of chars in word
    // multiplying each char by it's index in word

    // Variable for ending hash value
    unsigned int hash = 0;

    // Variable to hold current indexed char
    int currChar;

    // Variable to keep track of current index in word
    int index = 0;

    // Iterate over word
    while ((currChar = *word++))
    {
        // Add the current char to hash
        // tolower to ensure a larger hash value
        // multiply by index to add variance
        hash += tolower(currChar) * index;
        index += 1;
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file for reading
    FILE *dict = fopen(dictionary, "r");

    // Check for NULL
    if (dict == NULL)
    {
        printf("Could not open file %s.\n", dictionary);
        return 1;
    }

    // Initialize word array
    char word[LENGTH + 1];

    // Read each word in the file
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Malloc new node
        node *newP = malloc(sizeof(node));

        // Check for NULL error
        if (newP == NULL)
        {
            printf("Not enough memory.\n");
            return false;
        }

        // Initalize values of node
        strcpy(newP->word, word);
        newP->next = NULL;

        // Pass word into hash function
        int hashedStr = hash(newP->word);

        // Modulo hashed value for indexing
        hashedStr = hashedStr % N;

        // Insert new node into start of chain
        newP->next = table[hashedStr];
        table[hashedStr] = newP;

        // Add to word counter
        wordCount += 1;
    }

    // Close the dictionary file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over hash table
    for (int i = 0; i < N; i++)
    {
        // Check for NULL at index
        if (table[i] == NULL)
        {
            continue;
        }

        // Check for chained words at index
        if (table[i]->next != NULL)
        {
            // Initalize placeholder pointer
            node *currP = table[i]->next;

            // Check for more nodes
            if (currP->next != NULL)
            {
                // Iterate until end of list
                while (currP->next != NULL)
                {
                    // Initalize another pointer to hold next node
                    node *nextP = currP->next;

                    // Free current pointer
                    free(currP);

                    // Set current pointer to next node
                    currP = nextP;
                }
            }

            // Free final pointer in list
            free(currP);
        }

        // Free node at index
        free(table[i]);
    }

    return true;
}
