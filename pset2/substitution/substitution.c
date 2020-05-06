#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>

void cypher(int key);
bool checkUsage(string userInput);

int main(int argc, string argv[])
{

    // Check for invalid usage
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        bool flag = checkUsage(argv[1]);

        if (flag == 0)
        {
            cypher(atoi((argv[1])));
        }

        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

    }
}

void cypher(char code[])
{
    int alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


}

bool checkUsage(string userInput)
{
    if(strlen(userInput) < 26 || strlen(userInput) > 26)
    {
        return 0;
    }

    else
    {
        for (int i = 0; i < strlen(userInput); i++)
        {
            if (isalpha(userInput[i]))
            {
                return 1;
            }
        }
    }
}