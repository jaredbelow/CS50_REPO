#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Check card for NULL error
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];

    // Initialize a counter for file name
    int fileDigit = 0;

    // Initialize a writing flag
    // Thank you CS50 duck for help :)
    bool isWriting = false;

    // Initalize current file variable
    FILE *currentFile;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already writing, close current file
            // Add one to fileDigit for next file
            if (isWriting)
            {
                fclose(currentFile);
                fileDigit += 1;
            }
            // Open a new file for writing
            char fileName[8];
            sprintf(fileName, "%03i.jpg", fileDigit);
            currentFile = fopen(fileName, "w");

            // Check file for NULL error
            if (currentFile == NULL)
            {
                printf("Could not open %s\n", fileName);
                fclose(card);
                return 1;
            }

            // Flag isWriting for true
            isWriting = true;
        }

        // Check flag for writing to write file
        if (isWriting)
        {
            fwrite(buffer, 1, 512, currentFile);
        }
    }

    // Close all files
    fclose(currentFile);
    fclose(card);

    return 0;
}
