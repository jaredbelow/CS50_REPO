#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int change;

    // Prompt user for valid input of change
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 1);

    int total = 0;

    // Divide change by coin amount & add to total, any decimals are lost.
    // Getting the remainder after sum is added to total in order proceed to next coin amount.

    total += change / 25;
    change = change % 25;

    total += change / 10;
    change = change % 10;

    total += change / 5;
    change = change % 5;

    total += change / 1;

    printf("%i\n", total);
}
