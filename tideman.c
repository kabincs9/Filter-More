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
// this recursion is not much important ..
// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2]; // sum formula or pair counting formula

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser); // to put function of second last question
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
    // TODO
    /// one or first thing vote , to match the name of the valid candidate,vote, 0 in first and 1 in
    /// second
    // like in second one problem week3
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i; // to check rank also
            return true;
        }
    }
    return false;
}
// as per question record preference
// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++) // to count/compare before we enter the end
    {
        for (int j = i + 1; j < candidate_count; j++) // count after current like 0 first preference
        {
            preferences[ranks[i]][ranks[j]]++; // as question
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) // as question their pair should be stored in pair 0 ... pair count-1
{
    int winningpair; // to check if it adds to winning pair
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            winningpair =
                preferences[i][j] - preferences[j][i]; // if a pair of candidate who are tried one
                                                       // is not preferred over other and
            // should not be in array// positive ij and negative ji
            if (winningpair > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (winningpair < 0)
            {
                pairs[pair_count].winner = j; // just opp j and i
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
// like strongest pair at first  and weak at last as question by comparing
void sort_pairs(void)
{
    // just as question like first strong
    // TODO
    for (int i = 0; i < pair_count - 1; i++)
    {
        int strongpair = preferences[pairs[i].winner][pairs[i].loser] -
                         preferences[pairs[i].loser][pairs[i].winner]; // opp loser winner
        int current_strongpair;
        int strongpair_index = i;

        // like Alice is preferred over Bob by a 7-2 margin
        for (int j = i + 1; j < pair_count; j++)
        {
            current_strongpair = preferences[pairs[j].winner][pairs[j].loser] -
                                 preferences[pairs[j].loser][pairs[j].winner];
            if (strongpair < current_strongpair)
            {
                strongpair = current_strongpair;
                strongpair_index = j;
            }
        }

        if (strongpair_index != i) // not equal to
        {
            pair buffer = pairs[i];
            pairs[i] = pairs[strongpair_index];
            pairs[strongpair_index] = buffer;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) // as question
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (cycle(pairs[i].winner, pairs[i].loser) == false)
        // like continusly alice bob ..david to alice like should go on no end like same winner and
        // loser
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // last to print winner
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_winner = true; // if it is winner
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                has_winner = false; // or false true in first
                break;
            }
        }
        if (has_winner == true)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}
bool cycle(int winner, int loser) // second last one
{
    if (loser == winner)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (cycle(winner, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}
