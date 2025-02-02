// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string input);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string output = replace(argv[1]);
        printf("Output : %s\n", output);
        return 0;
    }
    else
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
}

string replace(string input)
{

    for (int i = 0; i < strlen(input); i++)
    {
        switch (tolower(input[i]))
        {
            case 'a':
                input[i] = '6';
                break;

            case 'e':
                input[i] = '3';
                break;

            case 'i':
                input[i] = '1';
                break;

            case 'o':
                input[i] = '0';
                break;

            default:
                break;
        }
    }

    return input;
}
