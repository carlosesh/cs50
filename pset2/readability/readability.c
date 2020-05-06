#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>
#include<math.h>

void readability(string text);
int countLettersOfAnString(string text);
int countWordsOfAnString(string text);
int countSentencesOfAnString(string text);
int calculateIndex(int letters, int words, int sentences);
void printGrade(int index);

int main(void)
{
    readability(get_string("Text:"));
}

void readability(string text)
{
    int letters = countLettersOfAnString(text);
    int words = countWordsOfAnString(text);
    int sentences = countSentencesOfAnString(text);
    int index = calculateIndex(letters, words, sentences);
    
    printGrade(index);

}

int countLettersOfAnString(string text)
{
    int letters = 0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    
    return letters;
}

int countWordsOfAnString(string text)
{
    int spaces = 0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            spaces++;
        }
    }
    
    return spaces + 1;
}

int countSentencesOfAnString(string text)
{
    int sentences = 0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') 
        {
            sentences++;
        }
    }
    
    return sentences;
}

int calculateIndex(int letters, int words, int sentences)
{
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    
    float idx = (0.0588 * L - 0.296 * S - 15.8);

    return (idx - ((int) idx)) > 0.5 ? ceil(idx) : idx;
}

void printGrade(int index)
{
    if (index < 0)
    {
        printf("Before Grade 1\n");
    } 
    else if (index > 16)
    {
        printf("Grade 16+\n");
    } 
    else
    {
        printf("Grade %d\n", index);
    }
}