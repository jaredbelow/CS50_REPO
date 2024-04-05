#include <cs50.h>
#include <stdio.h>

void print_full_pyramid(int height);
void print_pyramid_spaces(int spaces);
void print_pyramid_hash(int length);

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 23);

    print_full_pyramid(height);
}

void print_full_pyramid(int height)
{
    int spaces_number = height;

    for (int i = 0; i < height; i++)
    {
        print_pyramid_spaces(spaces_number - 1);
        print_pyramid_hash(i + 1);
        printf("  ");
        print_pyramid_hash(i + 1);
        printf("\n");

        spaces_number--;
    }
}

void print_pyramid_spaces(int spaces)
{
    for (int i = spaces; i > 0; i--)
    {
        printf(" ");
    }
}

void print_pyramid_hash(int length)
{

    for (int i = 0; i < length; i++)
    {
        printf("#");
    }
}
