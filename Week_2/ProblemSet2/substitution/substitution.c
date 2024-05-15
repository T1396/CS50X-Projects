#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool key_alphanum_check(string key);
bool key_char_check(string key);
bool key_check(string key);
string encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (key_check(argv[1]))
    {
        string plaintext = get_string("Plaintext: ");
        string ciphertext = encrypt(plaintext, argv[1]);
        printf("ciphertext: %s\n", ciphertext);
    }
    else
    {
        printf("Invalid, use only letters(a-z/ A-Z) each letter may occur only once. \n");
        return 1;
    }
}


string encrypt(string plaintext, string key)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))  //check if its a letter
        {
            //to integrate case sensitivity
            if(islower(plaintext[i]))
            {
                // 'a' = 97, Key[0] is correlative for A/a, so we need to subtract 97
                plaintext[i] = tolower(key[plaintext[i]-97]);
            }
            else
            {
                // 'A' = 65, Key[0] is correlative for A/a so we need to subtract 65
                plaintext[i] = toupper(key[(plaintext[i])-65]);
            }

        }
    }
    return plaintext;
}

bool key_check(string key)
{
    bool c = false;
    if (key_alphanum_check(key) && key_char_check(key))
    {
        c = true;
    }
    return c;
}

bool key_alphanum_check(string key)
{
    bool is_valid = true;
    int i = 0;
    while (is_valid && i < strlen(key))
    {
        if (isalpha(key[i]))
        {
            i++;
        }
        else
        {
            is_valid = false;
        }
    }
    return is_valid;
}

bool key_char_check(string key)
{
    bool is_valid = true;
    int i = 1;
    while (is_valid && i < strlen(key))
    {
        for (int j = 0; j < i; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                is_valid = false;
            }
        }
        i++;
    }
    return is_valid;
}
