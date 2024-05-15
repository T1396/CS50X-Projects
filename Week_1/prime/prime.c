#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    int start = 2;
    while(start<number)
    {
        if(number%start == 0)  // Falls Zahl einen Teiler besitzt ist sie keine Primzahl
        {
            return false;
        }
        start++;
    }
    if(number > 1)
    {
    return true;
    }
    return false;
}
