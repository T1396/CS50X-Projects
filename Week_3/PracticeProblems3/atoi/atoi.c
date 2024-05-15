#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int index = strlen(input)-1;
    // TODO
    if (strlen(input) == 0)
    {
        return 0;
    }
    if (strlen(input) > 0)
    {
        int integer = input[index]-48;
        input[index] = input[index+1];
        return integer + 10*convert(input);
    }
    return 0;
}

     //int integer = 0;
        //integer += input[strlen(input)-1]-48;    // (input[]-48)*10^strlen(input)-1
        //input[strlen(input)-1] = input[strlen(input)];
        //convert(input);
        //return integer + 10 * integer;
        //return (input[strlen(input)-1]-48) + (10 * input[strlen(input)-1]-48);