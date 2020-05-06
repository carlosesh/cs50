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

void cypher(int key)
{
    string plainText = get_string("plaintext:  ");
    
    for (int i = 0; i < strlen(plainText); i++)
    {
        if (isalpha(plainText[i]))
        {
            if (plainText[i] >= 'a' && plainText[i] <= 'z')
            {
                plainText[i] = ((plainText[i] - 'a') +  key) % 26 + 'a';
            } 
            else if (plainText[i] >= 'A' && plainText[i] <= 'z')
            {
                plainText[i] = ((plainText[i] - 'A') +  key) % 26 + 'A';
            }
        }
    }
    
    printf("ciphertext: %s\n", plainText);
}

bool checkUsage(string userInput)
{
    for (int i = 0; i < strlen(userInput); i++)
    {
        if (isalpha(userInput[i]))
        {
            return 1;
        }
    }
    
    return 0;
}