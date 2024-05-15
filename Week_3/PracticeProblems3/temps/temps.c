// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 13

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);
void swap(int pos1, int pos2);
void sort_cities_bubble(void);
void sort_cities_insertion(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    temps[10].city = "Kassel";
    temps[10].temp = 93;

    temps[11].city = "Berlin City Bitch";
    temps[11].temp = 420;

    temps[12].city = "Kentucky";
    temps[12].temp = 1337;

    sort_cities_insertion();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
/*void sort_cities(void)
{
    int mem = 0;
    string mem2 = "";
    // speichert index des größtem Element
    int biggest = 0;

    // nach NUM_CITIES - 1 Durchgängen ist das letzte Element was übrig ist das kleinste
    for (int i = 0; i < NUM_CITIES-1; i++)
    {
        // suche nach größtem Element in ganzer Liste
        for( int j = i+1; j < NUM_CITIES; j++)
        {
            // wenn größere temp gefunden, setze biggest/index auf index des gefundenen Elements
            if (temps[biggest].temp < temps[j].temp)
            {
                biggest = j;
            }
        }
        // temporäre Speichervariablen
        mem = temps[biggest].temp;
        mem2 = temps[biggest].city;
        //setze höchstes Element an stelle des aktuellen
        temps[biggest].temp = temps[i].temp;
        temps[biggest].city = temps[i].city;
        temps[i].temp = mem;
        temps[i].city = mem2;
    }
}*/
void sort_cities_insertion(void)
{
    int next_index = 0;
    int next_elem_temp = 0;
    string next_elem_city = "";
    for (int i = 0; i < NUM_CITIES-1; i++)
    {
        next_index = i+1;
        next_elem_temp = temps[next_index].temp;
        next_elem_city = temps[next_index].city;

        while (next_index > 0 && next_elem_temp > temps[next_index-1].temp)
        {
            temps[next_index].temp = temps[next_index-1].temp;
            next_index -=1;
        }
        temps[next_index].temp = next_elem_temp;
        temps[next_index].city = next_elem_city;
    }
}

void sort_cities_bubble(void)
 {
    bool swapped = false;
    int mem = 0;
    string memcity = "";
    for (int i = 0; i < NUM_CITIES; i++)
    {
        for (int j = 0; j < NUM_CITIES-1; j++)
        {
            if(temps[j].temp < temps[j+1].temp)
            {
                swap(j, j+1);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
 }

void swap(int pos1, int pos2)
{
      int mem = temps[pos1].temp;
      string memcity = temps[pos1].city;
      temps[pos1].temp = temps[pos2].temp;
      temps[pos1].city = temps[pos2].city;
      temps[pos2].temp = mem;
      temps[pos2].city = memcity;
}
