// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h> // 馬的check50加上這行就可以compile了，可是實際上在跑的時候根本用不到啊
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
const unsigned int N = 65536;
unsigned int num = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // allocate memory for another string
    char *str = malloc(strlen(word) + 1);
    if (str == NULL)
    {
        return 1;
    }

    // convert word to lowercase
    for(int i = 0, n = strlen(word); i <= n; i++){
        str[i] = tolower(word[i]);
    }

    int p = hash(str);
    free(str);

    for (node *tmp = table[p]; tmp != NULL; tmp = tmp -> next)
    {
        if (strcasecmp(word, tmp -> word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // hash function from http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    //while ((c = *str++) != 0) --> 這個不知道為什麼用他的話就不能free memory
    for (int i = 0; i < strlen(word); i += 1)
    {
        c = word[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // initialize table
    //*table[N] = { NULL };

    // define file
    FILE *fp;
    fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }

    // define word and scan words in file into word; one word at a time
    char word[LENGTH + 1];
    while (fscanf(fp, "%s", word) != EOF)
    {
        // make memory for node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        // get hashcode from hash function
        int code = hash(word);
        strcpy(n -> word, word);

        // check if there are words in table[code] or not
        if (table[code] != NULL)
        {
            n -> next = table[code];
            table[code] = n;
        }
        else
        {
            n -> next = NULL;
            table[code] = n;
        }

        // count the number of words in dictionary
        num += 1;
    }

    // close file
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i += 1)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i] -> next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
