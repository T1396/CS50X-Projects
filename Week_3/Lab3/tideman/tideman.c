#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool creates_cycle(int start, int end);
void print_preferences(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // ranks[i] enthält den Index des Kandidaten, der in der i-ten Präferenz gewählt wurde
            int preferred_candidate = ranks[i];
            int less_preferred_candidate = ranks[j];

            // Erhöhe die Präferenzen des aktuellen Wählers
            preferences[preferred_candidate][less_preferred_candidate]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Durchlaufe alle möglichen Kandidatenpaare
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Wenn der Kandidat i gegenüber j bevorzugt wird, füge das Paar zum Array pairs hinzu
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // Wenn der Kandidat j gegenüber i bevorzugt wird, füge das Paar zum Array pairs hinzu
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // Wenn beide Kandidaten gleich bevorzugt werden, ignoriere das Paar (tue nichts)
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i; j++)
        {
            int strength_1 = preferences[pairs[j].winner][pairs[j].loser];
            int strength_2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            if (strength_1 < strength_2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    for (int k = 0; k < pair_count; k++)
    {
        // printf("Rang %i Winner: %i , Loser: %i\n", k+1, pairs[k].winner, pairs[k].loser);
    }
    // TODO
    return;
}
// Lock pairs into the candidate graph in order, without creating cycles
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        // Lock the pair if it doesn't create a cycle
        if (creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// Helper function to check if locking in a pair would create a cycle
bool creates_cycle(int start, int end)
{
    // Base case: if end is reachable from start, then there is a cycle
    if (locked[end][start])
    {
        return true;
    }

    // Recursive case: check if end is reachable from any of start's neighbors
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][start])
        {
            if (creates_cycle(i, end))
            {
                return true;
            }
        }
    }

    // If no cycle is found, return false
    return false;
}

// Print the winner of the election
void print_winner(void)

{
    int winner = -1; // Anfangswert für den Gewinner

    // Überprüfe jeden Kandidaten, ob er keine eingehenden Kanten hat
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming_edge = false;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                has_incoming_edge = true;
                break;
            }
        }

        // Wenn der Kandidat keine eingehenden Kanten hat, ist er der Gewinner
        if (!has_incoming_edge)
        {
            winner = i;
            break;
        }
    }

    // Gib den Namen des Gewinners aus
    if (winner != -1)
    {
        printf("%s\n", candidates[winner]);
    }

    // TODO
    return;
}

void print_preferences(void)
{
    printf("Preferences Matrix:\n");

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d ", preferences[i][j]);
        }
        printf("\n");
    }
}