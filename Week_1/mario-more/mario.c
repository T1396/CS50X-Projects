#include <cs50.h>
#include <stdio.h>

void printhashtag(int n);
int ask_height();
void sequence(int height);


int main(void)
{
    sequence(ask_height());
}

void sequence(int height)
{
    int start = 1;
    while(start <= height)
    {
        for(int i = start; i < height; i++)
          []
        printhashtag(start);
        printf(" ");
        printhashtag(start);
        printf("\n");
        start++;
    }
}

int ask_height()
{
    int height = 0;
    do
    {
    height = get_int("How tall? : ");
    } while (height < 1 || height > 8);
    return height;
}


void printhashtag(int n)
{
    for(int i = 0; i < n ; i++){
        printf("#");
    }
}