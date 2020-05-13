// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

unsigned int numberOfWordsAdded = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hashValue = hash(word);

    node current = *table[hashValue];

    while (current.next != NULL)
    {
        if (strcasecmp(current.word, word) == 0)
        {
            return true;
        }

        current = *current.next;
    }

    if (current.next == NULL)
    {
        if (strcasecmp(current.word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char c = word[0];

    unsigned int result = tolower(c) - (int) 'a' ;

    return result % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    else
    {
        char word[45];

        while (fscanf(file, "%s", word) != EOF)
        {
            unsigned int hashValue = hash(word);

            if (&table[hashValue] == 0x0)
            {
                node *n = malloc(sizeof(node));
                if (n == NULL)
                {
                    return false;
                }
                strcpy(n->word, word);
                n->next = NULL;

                table[hashValue] = n;

                numberOfWordsAdded++;
            }

            else
            {
                node *n = malloc(sizeof(node));

                if (n == NULL)
                {
                    return false;
                }

                strcpy(n->word, word);

                n->next = table[hashValue];

                table[hashValue] = n;

                numberOfWordsAdded++;
            }
        }
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numberOfWordsAdded;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        //logic was taken from here -> https://www.gnu.org/software/libc/manual/html_node/Freeing-after-Malloc.html
        while (table[i] != NULL)
        {
            node *next = table[i]->next;
            free(table[i]->word);
            table[i] = next;
        }
    }

    if (*table == 0)
    {
        return true;
    }

    return false;
}
