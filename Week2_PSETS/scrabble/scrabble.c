#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculatestringtotals(string player);

int main(void)
{

    // Prompt User for two strings
    string p1;
    string p2;

    do
    {
        p1 = get_string("Player 1: ");
        p2 = get_string("Player 2: ");
    }
    while (strlen(p1) < 2 && strlen(p2) < 2);

    // Loop over both strings adding letter numbers to totals
    int total1 = calculatestringtotals(p1);
    int total2 = calculatestringtotals(p2);

    // Compare the totals for a winner

    if (total1 > total2)
    {
        printf("Player 1 wins!\n");
    }
    else if (total1 < total2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

int calculatestringtotals(string player)
{
    int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int letter_total = 0;

    for (int i = 0, n = strlen(player); i < n; i++)
    {
        // Converting to uppercase
        int num = toupper(player[i]);

        // Check for alphabetical letter, ignoring symbols & numbers
        if (num > 64 && num < 91)
        {
            // Subtracting 65 from uppercase letter to properly index into points array
            num -= 65;
            letter_total += POINTS[num];
        }
    }

    return letter_total;
}
