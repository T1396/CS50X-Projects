// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"



// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;



int wordCounter;
// TODO: Choose number of buckets in hash table
const unsigned int N = 199877;

// Hash table
node *table[N];


// Prototype
bool unloader(node* current);



// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    int index = hash(word);
    node *cursor = table[index];

    while(cursor != NULL)
    {
        if(strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int ret = 0;
    int i = 1;
    while(*word) {
        ret= (ret << 2) ^ toupper(*word++);
    }

    // TODO: Improve this hash function
    return ret%N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    wordCounter = 0;
    FILE *infile = fopen(dictionary, "r");
    if (!infile) {
        printf("Error opening dictionary!\n");
        return false;
    }
    char wordBuffer[LENGTH + 1];
    while(fscanf(infile, "%s", wordBuffer) == 1)
    {
        int index = hash(wordBuffer);
        node *new = malloc(sizeof(node));
        if(new == NULL) {
            // memory alloc fail
            return false;
        }
        strcpy(new->word, wordBuffer);
        new->next = NULL;
        if(table[index] == NULL)
        {
            table[index] = new;
        }
        else
        {
            node *current = table[index];
            while(current->next != NULL)
            {
                current = current->next;
            }
            current->next = new;
        }
    }
    fclose(infile);
    return true;
}

void fillWord(char word [], char buffer[]) {
    int index = 0;
    for(int i = 0; i < LENGTH; i++) {
        if(isalpha(buffer[i]) || (buffer[i] == '\'' && index > 0) ) {
            word[i] = buffer[i];
            index++;
        } else {
            index = i;
            break;
        }
    }
    word[index] = '\0';
    wordCounter++;
}



// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        if(!unloader(table[i]))
        {
            return false;
        }
        table[i] = NULL;
    }

    return true;
}

bool unloader(node* current) {
    if(current == NULL) {
        return true;
    }
    if(!unloader(current->next))
    {
        return false;
    }
    free(current);
    return true;
}
