#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_letters(string sentence);
int count_words(string sentence);
int count_sentences(string sentence);
double calc_index(string sentence);

int main(void)
{
    string text = get_string("Text: ");

    //printf("%i Letters\n", count_letters(text));
    //printf("%i Words\n", count_words(text));
    //printf("%i Sentences\n", count_sentences(text));


    double index = calc_index(text);
    //printf("Index: %.1f\n", index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 1 && index < 16)
    {
        printf("Grade %.0f\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string sentence)
{
    int cletter = 0; // counter
    for (int i = 0; i < strlen(sentence); i++)
    {
        if (isalpha(sentence[i]))
        {
            cletter++;
        }
    }
    return cletter;
}

int count_words(string sentence)
{
    int cwords = 0; // counter
    for (int i = 1; i < strlen(sentence); i++)
    {

        // prüfen ob Zeichen davor Buchstabe war, dann ob der aktuelle ein Satz oder Leerzeichen ist, wenn ja = Wort++
        if(isalpha(sentence[i-1]))
        {
            if(sentence[i] == ' ' || sentence[i] == ',' || sentence[i] == '!' || sentence[i] == '.' || sentence[i] == ';' || sentence[i] == '?')
            {
            cwords++;
            }
        }
    }
    return cwords;
}

int count_sentences(string sentence)
{
    int csentences = 0;
    for (int i = 1; i < strlen(sentence); i++)
    {
        if (isalpha(sentence[i-1]))
        {
            if (sentence[i] == '!' || sentence[i] == '.' || sentence[i] == '?')
            {
                csentences++;
            }
        }
    }
    return csentences;
}


double calc_index(string sentence)
{
    //          23.8875   - 7,4

    // index = 0.0588 * L - 0.296 * S - 15.8
            // L = Avrg of letters per 100 Words S = Avrg Sentence per 100 Words
    double avrgletter = ((double)count_letters(sentence)/count_words(sentence))*100;
    //printf("Durchschnittliche Buchstaben pro 100 Wörter: %.2f\n", avrgletter);
    double avrgsentence =  ((double)count_sentences(sentence)/count_words(sentence))*100;
   // printf("Durchschnittliche Sätze pro 100 Wörter: %.2f\n", avrgsentence);
    double index = ((0.0588 * avrgletter) - (0.296 * avrgsentence)) - 15.8;
    //printf("index: %.2f\n", index);
    return index;
}