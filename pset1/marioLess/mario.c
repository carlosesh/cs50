#include <cs50.h>
#include <stdio.h>

void pyramid_left_to_right(int n);
void pyramid_right_to_left(int n);

int main(void)
{
    pyramid_right_to_left(get_int("What's Marios Tower Height?\n"));
}

void pyramid_left_to_right(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

void pyramid_right_to_left(int n)
{
    if (n <= 0 || n >= 9)
    {
        pyramid_right_to_left(get_int("What's Marios Tower Height?\n"));
    }

    else
    {
        for (int i = 0; i < n; i++)
        {
            int temp = n - 1 - i;

            while (temp > 0)
            {
                printf(" ");
                temp--;
            }

            for (int j = 0; j <= i; j++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
}