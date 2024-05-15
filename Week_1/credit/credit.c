#include <cs50.h>
#include <stdio.h>

bool checksum_and_valid(long cardnr);
long read_cardnr();
int sum_second(long cardnr);
int sum_first(long cardnr);
bool is_american(long cardnumber);
bool is_mastercard(long cardnumber);
bool is_visa(long cardnumber);
string what_type_of_card(long cardnr);

int main(void)
{
    long cardnumber = read_cardnr();
    if (checksum_and_valid(cardnumber))
    {
        string cardtype = what_type_of_card(cardnumber);
        printf("%s", cardtype);
    }
    else
    {
        printf("INVALID\n");
    }

}

bool checksum_and_valid(long cardnr)
{
    if( is_visa(cardnr) || is_mastercard(cardnr) || is_american(cardnr))
    {
        if((sum_first(cardnr)+sum_second(cardnr))%10 == 0)
        {
            return true;
        }
    }
    return false;
}

int sum_first(long cardnr)
{
    int sum = 0;
    int temp = 0;
    cardnr /= 10;
    while(cardnr > 9)
    {
        temp = 2* (cardnr % 10);
        if(temp > 9)
        {
            sum += temp % 10;
            temp = temp / 10;
        }
        sum += temp;
        cardnr /= 100;
    }
    if (cardnr > 4)
    {
        temp = cardnr*2;
        sum += temp % 10;
        sum += temp/10;
    }else
    {
    sum += 2*cardnr;
    }
    return sum;
}

int sum_second(long cardnr)
{
    int sum = 0;
    while( cardnr > 9)
    {
        sum += cardnr % 10;
        cardnr /= 100;
    }
    if(cardnr > 0)
    {
        sum += cardnr;
    }
    return sum;
}

long read_cardnr()
{
    long cardnumber = -1;
    do
    {
        cardnumber = get_long("Number: ");
    } while( cardnumber < 0);
    return cardnumber;
}

string what_type_of_card(long cardnr)
{
    if(is_visa(cardnr))
    {
        return "VISA\n";
    }
    else if (is_mastercard(cardnr))
    {
        return "MASTERCARD\n";
    }
    else if (is_american(cardnr))
    {
        return "AMEX\n";
    }
    return "-1";
}

bool is_american(long cardnumber)
{
    if(cardnumber >= 340000000000000 && cardnumber <= 349999999999999)
    {
        return true;
    }
    else if (cardnumber >= 370000000000000 && cardnumber <= 379999999999999)
    {
        return true;
    }
    return false;
}

bool is_visa(long cardnumber)
{
    if (cardnumber >= 4000000000000 && cardnumber <= 4999999999999)
    {
        return true;
    }
    else if (cardnumber >= 4000000000000000 && cardnumber <= 4999999999999999)
    {
        return true;
    }
    return false;
}

bool is_mastercard(long cardnumber)
{
    if(cardnumber >= 5100000000000000 && cardnumber <= 5599999999999999)
    {
        return true;
    }
    return false;
}