#include <stdio.h>
#include <cs50.h>
#include <math.h>

int getChange(float n);

int main(void)
{
    float n = get_float("Change owed: \n");
    printf("%d\n", getChange(n));
}

int getChange(float n)
{
    if (n <= 0)
    {
        return getChange(get_float("Change owed: \n"));
    }

    else
    {
        int cents = round(n * 100);
        int coins[] = {25, 10, 5, 1};
        int result = 0;

        while (cents > 0)
        {
            for (int i = 0; i < 4; i++)
            {
                int temp = 0;
                temp = cents / coins[i];
                result += temp;
                cents -= (temp * coins[i]);
            }
        }

        return result;
    }
}