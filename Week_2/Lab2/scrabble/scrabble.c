#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 == score1)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    int number = 0;
    int score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        // check if char is a letter
        if (isalpha(word[i]))
        {
            number = tolower(word[i]) - 97; // defines which index of POINTS. - 'a' = 97, POINTS[0] is starting point for a
            score += POINTS[number];
        }
        else
        {
            score += 0;
        }
    }
    return score;
}
